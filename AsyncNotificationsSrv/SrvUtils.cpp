#include "SrvUtils.h"


CServer& CServer::GetInstance()
{
	static CServer instance;
	return instance;
}


_Check_return_
DWORD CServer::RpcOpenSession(
	_In_ handle_t hFormalParam,
	_Out_ context_handle_t* phContext
)
{
	UNREFERENCED_PARAMETER(hFormalParam);

	if (!phContext) {
		return ERROR_INVALID_PARAMETER;
	}

	try
	{
		*phContext = new CContextHandle;
	}
	catch (const std::bad_alloc&)
	{
		return ERROR_NOT_ENOUGH_MEMORY;
	}

	return ERROR_SUCCESS;
}


_Check_return_
DWORD CServer::RpcCloseSession(
	_Inout_ context_handle_t* phContext
)
{
	if (!phContext) {
		return ERROR_INVALID_PARAMETER;
	}

	//
	// Need to cancel call and remove from subscriptions
	// 
	std::lock_guard<std::mutex> subcscriptionsLock( m_mtxSubscriptions );
	std::lock_guard<std::mutex> callsLock( m_mtxCalls );

	auto call = m_calls.find( *phContext );

	if (call != m_calls.end()) 
	{
#pragma warning(disable: 6031)  // Return value ignored : 'RpcAsyncAbortCall'
		::RpcAsyncAbortCall( m_calls[*phContext].m_pState, ERROR_CANCELLED );
#pragma warning(default: 6031)
	}

	for(auto& subscription : m_subscriptions) {
		subscription.second.erase( *phContext );
	}

	delete static_cast<CContextHandle*>(*phContext);
	*phContext = nullptr;

	return ERROR_SUCCESS;
}


_Check_return_
DWORD CServer::RpcAddSubscription( 
	_Inout_ context_handle_t* phContext, 
	_In_ wchar_t chToAwait 
)
{
	if(!phContext) {
		return ERROR_INVALID_PARAMETER;
	}

	//
	// Lock mutex not to currupt data
	// 
	std::lock_guard<std::mutex> lock( m_mtxSubscriptions );

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
	bool bIsInserted = subscription->second.emplace( *phContext ).second;

	//
	// Increment subscriptions' counter in context handle
	// 
	if (bIsInserted) {
		GetContext( *phContext )->nSubsciptions++;
	}

	return ERROR_SUCCESS;
}


_Check_return_
DWORD CServer::RpcCancelSubscription( 
	_Inout_ context_handle_t* phContext, 
	_In_ wchar_t chToCancel 
)
{
	if (!phContext) {
		return ERROR_INVALID_PARAMETER;
	}

	//
	// Lock mutex not to currupt data
	// 
	std::lock_guard<std::mutex> subcscriptionsLock( m_mtxSubscriptions );

	//
	// Trying to find existing subscriptions for this symbol
	// 
	auto subscription = m_subscriptions.find( chToCancel );

	//
	// If none found, just return
	// 
	if (subscription == m_subscriptions.end()){
		return ERROR_SUCCESS;
	}

	auto& clients = subscription->second;

	//
	// Remove current client (if exists)
	// 
	size_t nErased = clients.erase( *phContext );

	if(clients.empty()) {
		m_subscriptions.erase( subscription );
	}
	
	//
	// Decrement internal client's counter
	// 
	if (nErased > 0) {
		GetContext( *phContext )->nSubsciptions--;
	}

	//
	// Return if there are another subscriptions for this client
	// 
	if(GetContext( *phContext )->nSubsciptions) {
		return ERROR_SUCCESS;
	}

	//
	// If no more subscriptions for client remains, trying
	// terminate it's asynchronous call
	// 
	std::lock_guard<std::mutex> callsLock( m_mtxCalls );

	auto callControl = m_calls.find( *phContext );

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


void CServer::RpcAsyncAwaitForEvent( 
	_In_ PRPC_ASYNC_STATE pState, 
	_In_ context_handle_t hContext, 
	_In_ wchar_t* pszResult 
)
{
	//
	// Here we need only to put call params into container
	// 
	std::lock_guard<std::mutex> lock( m_mtxCalls );
	m_calls[hContext] = CAsyncControl{ pState, hContext, pszResult };
}


void CServer::AnalyzeStringAndNotify( 
	_In_ const wchar_t* pszString, 
	_In_ size_t ulSize 
)
{
	wchar_t ch = *pszString;

	//
	// Trying to find subscriptions for this symbol.
	// If none found, just exit call
	// 
	std::lock_guard<std::mutex> subscriptionsLock( m_mtxSubscriptions );

	auto subscription = m_subscriptions.find( ch );

	if (subscription == m_subscriptions.end()) {
		return;
	}

	//
	// Here we already have subscriptions.
	// Let's send notification to all of them
	// 
	auto& subscribers = subscription->second;

	std::lock_guard<std::mutex> callsLock( m_mtxCalls );

	for (context_handle_t hSubscriber : subscribers) 
	{
		CAsyncControl& control = m_calls[hSubscriber];

		PRPC_ASYNC_STATE pState = control.m_pState;
		wchar_t* pszResult = control.m_pszResult;

		//
		// Writing result and notifying the client
		// 
		wcscpy_s( pszResult, ulSize, pszString );
		DWORD dwResult = ERROR_SUCCESS;

#pragma warning(disable: 6031) // Return value ignored : 'RpcAsyncCompleteCall'
		::RpcAsyncCompleteCall( pState, &dwResult );
#pragma warning(default: 6031)

		//
		// Now it is necessary to erase call
		// from set.
		// 
		m_calls.erase( hSubscriber );
	}
}