#include "ClUtils.h"
#include "../Common/Utils.h"

#include "../AsyncNotifications/AsyncNotificationsInterface_h.h"


CClient::CClient()
    : m_bNewWaitThreadNeeded( true )
    , m_pWait( nullptr )
    , m_pParams( std::make_unique<CAsyncParams>() )
{
    TRACE_FUNC;

    m_pParams->m_pState = &m_state;
    m_pParams->m_pszResult = m_szResult;

    RPC_WSTR pszBindingString = nullptr;
    HANDLE     hBinding = nullptr;

    RPC_STATUS status = ::RpcStringBindingCompose(
        nullptr,
        (RPC_WSTR)pszDefaultProtocol,
        nullptr,
        (RPC_WSTR)pszDefaultEndpoint,
        nullptr,
        &pszBindingString
    );
    if (status != RPC_S_OK) {
        throw std::runtime_error( FUNC_FAILURE_STR_A( RpcStringBindingCompose ) );
    }

    status = ::RpcBindingFromStringBinding(
        pszBindingString,
        &hBinding
    );
    if (status != RPC_S_OK) {
        throw std::runtime_error( FUNC_FAILURE_STR_A( RpcBindingFromStringBinding ) );
    }

    status = CreateContextHandle( hBinding );
    if (status != RPC_S_OK) {
        throw std::runtime_error(
            FUNC_FAILURE_STR_A( CreateContextHandle ) \
            " Code: " + std::to_string( status )
        );
    }

    //
    // Free some resources
    // 
    ::RpcStringFree( &pszBindingString );
    ::RpcBindingFree( &hBinding );

    status = ::RpcAsyncInitializeHandle(
        m_pParams->m_pState,
        sizeof(RPC_ASYNC_STATE)
    );
    if (status != RPC_S_OK) {
        throw std::runtime_error( FUNC_FAILURE_STR_A( RpcAsyncInitializeHandle ) );
    }

    m_pParams->m_pState->NotificationType = RpcNotificationTypeEvent;
    m_pParams->m_pState->u.hEvent = ::CreateEvent( nullptr, FALSE, FALSE, nullptr );

    if (!m_pParams->m_pState->u.hEvent)
    {
        throw std::runtime_error(
            FUNC_FAILURE_STR_A( CreateEvent ) \
            " : " + std::to_string( GetLastError() )
        );
    }

    DEBUG_TRACE( DL_EXTENDED, L"m_pState = ", m_pParams->m_pState );

    //
    // As parameter fo callback I use pointer to current CClient instance.
    // There's no reasu=on to worry about invalid pointer, because waiting
    // will be cancelled anyway in destructor.
    // 
    m_pWait = CreateThreadpoolWait( WaitCompletedCallback, this, nullptr );
}


CClient::~CClient()
{
    TRACE_FUNC;

    CleanUpWait();

    if (m_pWait)
    {
        CloseThreadpoolWait( m_pWait );
        m_pWait = nullptr;
    }

    RPC_STATUS status = DestroyContextHandle();
    DEBUG_TRACE( DL_EXTENDED, L"DestroyContextHandle == ", status );

    if (m_pParams->m_pState->u.hEvent) ::CloseHandle( m_pParams->m_pState->u.hEvent );
}


_Check_return_
RPC_STATUS CClient::CreateContextHandle( _In_ HANDLE hBinding )
{
    TRACE_FUNC;

    RPC_STATUS status = RPC_S_OK;

    RpcTryExcept
    {
        DWORD dwResult = RpcOpenSession(
            hBinding,
            &m_pParams->m_hContext
        );
        if (dwResult != ERROR_SUCCESS) {
            status = dwResult;
        }
    }
    RpcExcept( EXCEPTION_EXECUTE_HANDLER )
    {
        DEBUG_TRACE( DL_CRITICAL, L"EXCEPTION_EXECUTE_HANDLER" );
        status = RpcExceptionCode();
    }
    RpcEndExcept

    return status;
}


_Check_return_
RPC_STATUS CClient::DestroyContextHandle()
{
    TRACE_FUNC;

    RPC_STATUS status = RPC_S_OK;

    RpcTryExcept
    {
        if (m_pParams->m_hContext)
        {
            DWORD dwResult = RpcCloseSession( &m_pParams->m_hContext );
            if (dwResult != ERROR_SUCCESS) {
                status = dwResult;
            }
        }
    }
    RpcExcept( EXCEPTION_EXECUTE_HANDLER )
    {
        DEBUG_TRACE( DL_CRITICAL, L"EXCEPTION_EXECUTE_HANDLER" );
        status = RpcExceptionCode();
    }
    RpcEndExcept


    if (status != RPC_S_OK)
    {
        DEBUG_TRACE( DL_CRITICAL, L"Calling RpcSsDestroyClientContext" );
        ::RpcSsDestroyClientContext( &m_pParams->m_hContext );
    }

    return status;
}


_Check_return_
DWORD CClient::RpcAddSubscription( _In_ wchar_t chToAwait )
{
    TRACE_FUNC;

    DWORD dwResult = ERROR_SUCCESS;

    RpcTryExcept
    {
        dwResult = ::RpcAddSubscription( m_pParams->m_hContext, chToAwait );
    }
    RpcExcept( EXCEPTION_EXECUTE_HANDLER )
    {
        DEBUG_TRACE( DL_CRITICAL, L"EXCEPTION_EXECUTE_HANDLER" );
        dwResult = RpcExceptionCode();
    }
    RpcEndExcept

    //
    // In case of success I call async procedure
    // 
    if (dwResult == ERROR_SUCCESS) {
        dwResult = StartWaiting();
    }

    return dwResult;
}


_Check_return_
DWORD CClient::RpcCancelSubscription( _In_ wchar_t chToCancel )
{
    TRACE_FUNC;

    DWORD dwResult = ERROR_SUCCESS;

    RpcTryExcept
    {
        dwResult = ::RpcCancelSubscription( m_pParams->m_hContext, chToCancel );
    }
    RpcExcept( EXCEPTION_EXECUTE_HANDLER )
    {
        DEBUG_TRACE( DL_CRITICAL, L"EXCEPTION_EXECUTE_HANDLER" );
        dwResult = RpcExceptionCode();
    }
    RpcEndExcept

    return dwResult;
}


_Check_return_
RPC_STATUS CClient::StartWaiting()
{
    TRACE_FUNC;

    DEBUG_TRACE( DL_EXTENDED, L"m_bNewWaitThreadNeeded = ", m_bNewWaitThreadNeeded );
    DEBUG_TRACE( DL_EXTENDED, L"m_pState = ", m_pParams->m_pState );

    //
    // Maybe there's no need to call?
    // 
    if (!m_bNewWaitThreadNeeded) {
        return RPC_S_CALLPENDING;
    }

    if (!m_pWait) {
        return ERROR_FUNCTION_NOT_CALLED;
    }

    SetThreadpoolWait( m_pWait, m_pParams->m_pState->u.hEvent, nullptr );

    RPC_STATUS status = InvokeAsyncFunction();
    DEBUG_TRACE( DL_EXTENDED, L"InvokeAsyncFunction == ", status );

    return status;
}


_Check_return_
RPC_STATUS CClient::InvokeAsyncFunction()
{
    TRACE_FUNC;

    DWORD dwResult = RPC_S_OK;

    RpcTryExcept
    {
        RpcAsyncAwaitForEvent( m_pParams->m_pState, m_pParams->m_hContext, m_pParams->m_pszResult );
        m_bNewWaitThreadNeeded = false;
    }
    RpcExcept( EXCEPTION_EXECUTE_HANDLER )
    {
        DEBUG_TRACE( DL_CRITICAL, L"EXCEPTION_EXECUTE_HANDLER" );
        dwResult = RpcExceptionCode();
    }
    RpcEndExcept

    return dwResult;
}


_Check_return_
DWORD CClient::GetSubscriptionsCount()
{
    TRACE_FUNC;

    RpcTryExcept
    {
        return ::RpcGetSubscriptionsCount(m_pParams->m_hContext);
    }
    RpcExcept( EXCEPTION_EXECUTE_HANDLER )
    {
        DEBUG_TRACE( DL_CRITICAL, L"EXCEPTION_EXECUTE_HANDLER" );

        //
        // In case of error I'll return 0, because no waiting
        // will be started.
        // 
        return 0;
    }
    RpcEndExcept
}


void CClient::CleanUpWait()
{
    TRACE_FUNC;

    if (m_pWait) {
        SetThreadpoolWait( m_pWait, nullptr, nullptr );
    }
}


_Check_return_
DWORD CClient::OnWaitCompleted()
{
    TRACE_FUNC;

    //
     // Event received, hense we need to make another call if necessary
    // 
    m_bNewWaitThreadNeeded = true;

    ULONG nReply;
    RPC_STATUS status = ::RpcAsyncCompleteCall(m_pParams->m_pState, &nReply);

    CleanUpWait();

    if (status != RPC_S_OK)
    {
        //
        // Call aborted by server => there's no need to call it again.
        // 
        TRACE_DATA( L"Call aborted by server. Status: ", status );
        return status;
    }

    TRACE_DATA(  L"Function returned: ", m_pParams->m_pszResult, L"\n" );

    //
    // If we need to wait again, let's do it
    // 
    DWORD dwSubscriptions = GetSubscriptionsCount();
    DEBUG_TRACE( DL_EXTENDED, L"dwSubscriptions == ", dwSubscriptions );

    if (dwSubscriptions) {
        status = StartWaiting();
        DEBUG_TRACE( DL_EXTENDED, L"StartWaiting() == ", status );
    }

    return ERROR_SUCCESS;
}


VOID NTAPI WaitCompletedCallback(
    _Inout_ PTP_CALLBACK_INSTANCE /* Instance */,
    _Inout_opt_ PVOID Context,
    _Inout_ PTP_WAIT /* Wait */,
    _In_ TP_WAIT_RESULT /* WaitResult */
)
{
    TRACE_FUNC;

    auto pClient = (CClient*)Context;
    DWORD dwResult = pClient->OnWaitCompleted();

    DEBUG_TRACE( DL_EXTENDED, L"dwResult == ", dwResult );
}
