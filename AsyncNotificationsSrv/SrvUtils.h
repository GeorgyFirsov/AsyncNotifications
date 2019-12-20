#pragma once
#include "SrvIncludes.h"


//
// Here comes aliases for data-types
// 

// Character -----------------------|
// Set of all subscribed clients -- | -----------------|
//                                  V                  V
using subscriptions_t = std::map<wchar_t, std::set<context_handle_t>>;

// Client's identifier -------------------|
// Control block with parameters ---------|----------------|
//                                        V                V
using client_controls_t = std::map<context_handle_t, CAsyncControl>;


// ------------------------------------------------------------
// Class: CServer
// Description: it is an abstraction over RPC server. It provides
//              subscriptions' and subscribers' management.
// ------------------------------------------------------------
// Parameters (for constructors): none
// 
// Members:
//                 m_pInstance : pointer to server instance.
//                   m_fCalled : flag used to initialize instance
//                             : only once.
//             m_subscriptions : every subscription grouped by symbol
//          m_mtxSubscriptions : corresponding mutex
//                     m_calls : control block and counter for each
//                             : client's asynchronous call
//                  m_mtxCalls : corresponding mutex
//              
// Member functions:
//        DWORD RpcOpenSession : opens client's session and initializes
//                             : context handle
//       DWORD RpcCloseSession : closes client's session and deletes 
//                             : context handle
//    DWORD RpcAddSubscription : adds client's subscription
// DWORD RpcCancelSubscription : cancels client's subscription
//  void RpcAsyncAwaitForEvent : registers asyncronous call in m_calls
// void AnalyzeStringAndNotify : receives input string and send it
//                             : to all its' subscribers
// 
// Comments: 
//       
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 15.12.2019
// ------------------------------------------------------------
//
class CServer
{
public:
	static CServer& GetInstance();

	_Check_return_
	DWORD RpcOpenSession(
		_In_ handle_t hFormalParam, 
		_Out_ context_handle_t *phContext
	);

	_Check_return_
	DWORD RpcCloseSession(
		_Inout_ context_handle_t *phContext
	);

	_Check_return_
	DWORD RpcAddSubscription( 
		_Inout_ context_handle_t* phContext, 
		_In_ wchar_t chToAwait 
	);
	
	_Check_return_
	DWORD RpcCancelSubscription( 
		_Inout_ context_handle_t* phContext, 
		_In_ wchar_t chToCancel 
	);

	void RpcAsyncAwaitForEvent( 
		_In_ PRPC_ASYNC_STATE pState, 
		_In_ context_handle_t hContext, 
		_In_ wchar_t* pszResult 
	);

	void AnalyzeStringAndNotify(
		_In_ const wchar_t* pszString,
		_In_ size_t ulSize
	);

private:
	CServer() = default;

	//
	// Prevent any way to create another instance
	// 
	CServer( const CServer& ) = delete;
	CServer& operator=( const CServer& ) = delete;
	CServer( CServer&& ) = delete;
	CServer& operator=( CServer&& ) = delete;

private:
	subscriptions_t	  m_subscriptions;
	std::mutex        m_mtxSubscriptions;

	client_controls_t m_calls;
	std::mutex        m_mtxCalls;
};


//
// Macro used to obtain server instance
// 
#define g_Server CServer::GetInstance()