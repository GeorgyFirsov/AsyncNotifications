#include "SrvUtils.h"


CServer& CServer::GetInstance()
{
    static CServer instance;
    return instance;
}


_Check_return_
DWORD CServer::RpcOpenSession(
    _In_ handle_t /* hFormalParam */,
    _Out_ context_handle_t* phContext
)
{
    DEBUG_TRACE( DL_EXTENDED, L"phContext = ", phContext );

    if (!phContext) 
    {
        DEBUG_TRACE( DL_CRITICAL, FUNCTION_FAILED_WITH( ERROR_INVALID_PARAMETER ) );
        return ERROR_INVALID_PARAMETER;
    }

    try
    {
        *phContext = new CContextHandle;
    }
    catch (const std::bad_alloc&)
    {
        DEBUG_TRACE( DL_CRITICAL, FUNCTION_FAILED_WITH( ERROR_NOT_ENOUGH_MEMORY ) );
        return ERROR_NOT_ENOUGH_MEMORY;
    }

    return ERROR_SUCCESS;
}


_Check_return_
DWORD CServer::RpcCloseSession(
    _Inout_ context_handle_t* phContext
)
{
    DEBUG_TRACE( DL_EXTENDED, L"phContext = ", phContext );

    if (!phContext) 
    {
        DEBUG_TRACE( DL_CRITICAL, FUNCTION_FAILED_WITH( ERROR_INVALID_PARAMETER ) );
        return ERROR_INVALID_PARAMETER;
    }

    //
    // Need to cancel call and remove from subscriptions
    // 
    critical_section_guard subscriptionsLock( m_csSubscriptions );
    critical_section_guard callsLock( m_csCalls );

    auto call = m_calls.find( *phContext );

    if (call != m_calls.end()) 
    {
#pragma warning(disable: 6031)  // Return value ignored : 'RpcAsyncAbortCall'
        ::RpcAsyncAbortCall( m_calls[*phContext].m_pState, ERROR_CANCELLED );
#pragma warning(default: 6031)
    }

    for(auto& subscription : m_subscriptions) 
    {
        auto subscriber = subscription.second.find( *phContext );
        if (subscriber != subscription.second.end()) {
            subscription.second.erase( *phContext );
        }
    }

    delete static_cast<CContextHandle*>( *phContext );
    *phContext = nullptr;

    return ERROR_SUCCESS;
}


_Check_return_
DWORD CServer::RpcAddSubscription( 
    _In_ context_handle_t hContext, 
    _In_ wchar_t chToAwait 
)
{
    DEBUG_TRACE( DL_EXTENDED, L"hContext = ", hContext );

    //
    // Lock mutex not to currupt data
    // 
    critical_section_guard lock( m_csSubscriptions );

    //
    // Trying to find existing subscriptions for this symbol
    // 
    auto subscription = m_subscriptions.find( chToAwait );

    //
    // If no one found, initialize new empty set
    // 
    if(subscription == m_subscriptions.end()) {
        subscription = m_subscriptions.try_emplace( chToAwait, std::set<context_handle_t>() ).first;
    }

    //
    // Add context handle to set of all subscribers
    // 
    bool bIsInserted = subscription->second.emplace( hContext ).second;

    //
    // Increment subscriptions' counter in context handle
    // 
    if (bIsInserted) {
        GetContext( hContext )->nSubscriptions++;
    }

    return ERROR_SUCCESS;
}


_Check_return_
DWORD CServer::RpcCancelSubscription( 
    _In_ context_handle_t hContext, 
    _In_ wchar_t chToCancel 
)
{
    DEBUG_TRACE( DL_EXTENDED, L"hContext = ", hContext );

    //
    // Lock mutex not to currupt data
    // 
    critical_section_guard subcscriptionsLock( m_csSubscriptions );

    //
    // Trying to find existing subscriptions for this symbol
    // 
    auto subscription = m_subscriptions.find( chToCancel );

    //
    // If none found, just return
    // 
    if (subscription == m_subscriptions.end()){
        return ERROR_NOT_FOUND;
    }

    auto& clients = subscription->second;

    //
    // Remove current client (if exists)
    // 
    size_t nErased = clients.erase( hContext );

    if(clients.empty()) {
        m_subscriptions.erase( subscription );
    }
    
    //
    // Decrement internal client's counter
    // 
    if (nErased > 0) {
        GetContext( hContext )->nSubscriptions--;
    }

    //
    // Return if there are another subscriptions for this client
    // 
    if(GetContext( hContext )->nSubscriptions) {
        return ERROR_SUCCESS;
    }

    //
    // If no more subscriptions for client remains, trying
    // terminate it's asynchronous call
    // 
    critical_section_guard callsLock( m_csCalls );

    auto callControl = m_calls.find( hContext );

    if(callControl == m_calls.end()) 
    {
        //
        // Can not found existing asyncronous call for this client
        // 
        return ERROR_NOT_FOUND;
    }

    PRPC_ASYNC_STATE pState = callControl->second.m_pState;

    //
    // Cancel asynchronous call from server
    // 
    RPC_STATUS status = ::RpcAsyncAbortCall( pState, ERROR_CANCELLED );

    //
    // Remove parameters
    // 
    m_calls.erase( callControl );

    return static_cast<DWORD>( status );
}


_Check_return_
DWORD CServer::RpcGetSubscriptionsCount( 
    _In_ context_handle_t hContext 
)
{
    DEBUG_TRACE( DL_EXTENDED, L"hContext = ", hContext );

    //
    // Just look at atomic counter
    // 
    return static_cast<DWORD>( 
        GetContext( hContext )->nSubscriptions 
    );
}


void CServer::RpcAsyncAwaitForEvent( 
    _In_ PRPC_ASYNC_STATE pState, 
    _In_ context_handle_t hContext, 
    _In_ wchar_t* pszResult 
)
{
    DEBUG_TRACE( 
        DL_EXTENDED, 
        ON_NEW_LINE L"pState    = ", pState,
        ON_NEW_LINE L"hContext  = ", hContext,
        ON_NEW_LINE L"pszResult = ", AS_PTR( pszResult )
    );

    //
    // Here we need only to put call params into container
    // 
    critical_section_guard lock( m_csCalls );
    m_calls[hContext] = CAsyncParams{ pState, hContext, pszResult };
}


void CServer::AnalyzeStringAndNotify( 
    _In_ const wchar_t* pszString, 
    _In_ size_t ulSize 
)
{
    TRACE_FUNC;

    wchar_t ch = *pszString;

    //
    // Trying to find subscriptions for this symbol.
    // If none found, just exit call
    // 
    critical_section_guard subscriptionsLock( m_csSubscriptions );

    auto subscription = m_subscriptions.find( ch );

    if (subscription == m_subscriptions.end()) {
        return;
    }

    //
    // Here we already have subscriptions.
    // Let's send notification to all of them
    // 
    auto& subscribers = subscription->second;

    critical_section_guard callsLock( m_csCalls );

    for (context_handle_t hSubscriber : subscribers) 
    {
        CAsyncParams& control = m_calls[hSubscriber];

        PRPC_ASYNC_STATE pState = control.m_pState;
        wchar_t* pszResult = control.m_pszResult;

        //
        // Writing result and notifying the client
        // 
        wcscpy_s( pszResult, ulSize, pszString );
        RPC_STATUS status = SafeCompleteCall( pState, hSubscriber, subscribers );

        if (status != RPC_S_OK){
            continue;
        }

        //
        // Now it is necessary to erase call
        // from set.
        // 
        auto call = m_calls.find( hSubscriber );
        if (call != m_calls.end()) {
            m_calls.erase( hSubscriber );
        }
    }
}


void CServer::AbortAll()
{
    TRACE_FUNC;

    //
    // Lock critical section and clear container with subscriptions
    // 
    critical_section_guard subcriptionsLock( m_csSubscriptions );
    m_subscriptions.clear();

    //
    // Lock critical section and abort all async calls
    // 
    critical_section_guard callsLock( m_csCalls );
    
    for(auto& call : m_calls) 
    {
        DEBUG_TRACE( DL_EXTENDED, L"Cancelling for ", call.first );

#pragma warning(disable: 6031)  // Return value ignored
        ::RpcAsyncAbortCall( call.second.m_pState, ERROR_CANCELLED );
#pragma warning(default: 6031)
    }

    m_calls.clear();
}


_Check_return_
RPC_STATUS CServer::SafeCompleteCall( 
    _In_ PRPC_ASYNC_STATE pState, 
    _In_ context_handle_t hSubscriber,
    _In_ std::set<context_handle_t>& subscribers
)
{
    //
    // Critical section over calls should be locked outside
    // 

    RPC_STATUS status = RPC_S_OK;

    RpcTryExcept
    {
#pragma warning(disable: 6031) // Return value ignored : 'RpcAsyncCompleteCall'
        ::RpcAsyncCompleteCall( pState, &status );
#pragma warning(default: 6031)
    }
    RpcExcept( EXCEPTION_EXECUTE_HANDLER )
    {
        TRACE_LINE( L"Parameters are not valid (dead client). Removing..." );
        subscribers.erase( hSubscriber );
        m_calls.erase( hSubscriber );

        status = RpcExceptionCode();
    }
    RpcEndExcept

    return status;
}


_Check_return_
RPC_STATUS StartServer()
{
    TRACE_FUNC;

    RPC_STATUS status = ::RpcServerUseProtseqEp(
        (RPC_WSTR)pszDefaultProtocol,
        RPC_C_PROTSEQ_MAX_REQS_DEFAULT,
        (RPC_WSTR)pszDefaultEndpoint,
        nullptr
    );
    if (status != RPC_S_OK)
    {
        TRACE_LINE( FUNC_FAILURE_STR( RpcServerUseProtseqEp ) );
        return status;
    }

    status = ::RpcServerRegisterIfEx(
        AsyncNotifications_v1_0_s_ifspec,
        nullptr,
        nullptr,
        0,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        nullptr
    );
    if (status != RPC_S_OK)
    {
        TRACE_LINE( FUNC_FAILURE_STR( RpcServerRegisterIfEx ) );
        return status;
    }

    status = ::RpcServerListen(
        1,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        TRUE
    );
    if (status != RPC_S_OK)
    {
        TRACE_LINE( FUNC_FAILURE_STR( RpcServerListen ) );
        return status;
    }

    return RPC_S_OK;
}


void StopServer()
{
    TRACE_FUNC;

    //
    // Cancel all async calls first
    // 
    g_Server.AbortAll();

#pragma warning(disable: 6031)  // Return value ignored
    ::RpcMgmtStopServerListening( nullptr );
    ::RpcServerUnregisterIf( nullptr, nullptr, FALSE );
#pragma warning(default: 6031)
}