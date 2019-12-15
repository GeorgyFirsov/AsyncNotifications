#pragma once

#include "SrvIncludes.h"

// Automatically generated
#include "../AsyncNotifications/AsyncNotificationsInterface_h.h"

// ------------------------------------------------------------
// Class: CAsyncControl
// Description: all arguments of asyncronous calls will be
//              saved in such structures.
// ------------------------------------------------------------
// Parameters (for constructors): none
// 
// Members:
//                  pState : pointer to async state necessary
//                           for MS AsyncRPC
//               pszResult : pointer to output string that 
//                           will be filled with event-string
// 
// Comments: 
//     hContext is abcent, because it will be a key in std::map
//     binded with such structures.
//       
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 15.12.2019
// ------------------------------------------------------------
//
struct CAsyncControl
{
	PRPC_ASYNC_STATE	pState;
//	context_handle_t	hContext;	// Not present
	wchar_t*			pszResult;
};


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
//             m_pInstance : pointer to server instance.
//               m_fCalled : flag used to initialize instance
//                           only once.
//         m_subscriptions : every subscription grouped by symbol
//      m_mtxSubscriptions : corresponding mutex
//                 m_calls : control block and counter for each
//                           client's asynchronous call
//              m_mtxCalls : corresponding mutex
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
	DWORD RpcAddSubscription( _Inout_ context_handle_t* phContext, _In_ wchar_t chToAwait );
	_Check_return_
	DWORD RpcCancelSubscription( _Inout_ context_handle_t* phContext, _In_ wchar_t chToCancel );

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
	subscriptions_t			m_subscriptions;
	std::mutex				m_mtxSubscriptions;

	client_controls_t		m_calls;
	std::mutex				m_mtxCalls;
};


//
// Macro used to obtain server instance
// 
#define g_Server CServer::GetInstance()