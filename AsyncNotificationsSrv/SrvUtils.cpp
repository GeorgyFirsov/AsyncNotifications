#include "SrvUtils.h"
#include "../Common/Utils.h"

CServer& CServer::GetInstance()
{
	static CServer instance;
	return instance;
}

_Check_return_
DWORD CServer::RpcAddSubscription( _Inout_ context_handle_t* phContext, _In_ wchar_t chToAwait )
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
	subscription->second.emplace( *phContext );

	//
	// Increment subscriptions' counter in context handle
	// 
	InterlockedIncrement64( 
		reinterpret_cast<LONG64*>( &GetContext( *phContext )->nSubsciptions )
	);

	return ERROR_SUCCESS;
}

_Check_return_
DWORD CServer::RpcCancelSubscription( _Inout_ context_handle_t* phContext, _In_ wchar_t chToCancel )
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
	// Trying to find concrete client in subscriptions set
	// 
	auto client = clients.find( *phContext );
	
	//
	// If none found, return again
	// 
	if(client == clients.end()) {
		return ERROR_SUCCESS;
	}

	//
	// Remove current client
	// 
	clients.erase( client );

	if(clients.empty()) {
		m_subscriptions.erase( subscription );
	}

	//
	// Decrement internal client's counter
	// 
	InterlockedDecrement64( 
		reinterpret_cast<LONG64*>( &GetContext( *phContext )->nSubsciptions ) 
	);

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

	PRPC_ASYNC_STATE pState = callControl->second.pState;

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