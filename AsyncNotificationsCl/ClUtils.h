#pragma once
#include "ClIncludes.h"


// ----------------------------------------------------------------------
// Declarations of classes
// 


// ------------------------------------------------------------
// Class: CClient
// Description: it is an abstraction over RPC client.
// ------------------------------------------------------------
// Parameters (for constructors): none
// 
// Members:
//                      m_state : state used by MS RPC
//                   m_szResult : string to store result of async call
//                    m_pParams : pointer to parameters passed 
//                              : to async call
//                      m_pWait : this field is used for Windows' thread pool
//              
// Member functions:
//           RpcAddSubscription : adds client's subscription
//        RpcCancelSubscription : cancels client's subscription
//              OnWaitCompleted : callback invoked when async call returns
//          CreateContextHandle : creates context handle for this client
//         DestroyContextHandle : destroys client's context handle
//                 StartWaiting : performs preparations for 
//                              : invocation of async function
//          InvokeAsyncFunction : runs async function
//        GetSubscriptionsCount : retreives client's subscriptions count
//              
// 
// Comments: 
//       
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 21.01.2020
// ------------------------------------------------------------
//
class CClient final
{
public:
    CClient();
    ~CClient();

    //
    // Prevent any way to create another instance
    // 
    CClient( const CClient& ) = delete;
    CClient& operator= ( const CClient& ) = delete;
    CClient( CClient&& ) = delete;
    CClient& operator= ( CClient&& ) = delete;

    _Check_return_
    DWORD RpcAddSubscription( _In_ wchar_t chToAwait );

    _Check_return_
    DWORD RpcCancelSubscription( _In_ wchar_t chToCancel );

    DWORD OnWaitCompleted();

private:
    _Check_return_
    RPC_STATUS CreateContextHandle( _In_ HANDLE hBinding );

    _Check_return_
    RPC_STATUS DestroyContextHandle();

    _Check_return_
    RPC_STATUS StartWaiting();

    _Check_return_
    RPC_STATUS InvokeAsyncFunction();

    _Check_return_
    DWORD GetSubscriptionsCount();

private:
    RPC_ASYNC_STATE m_state;

    wchar_t m_szResult[dwMaxStringLength];

    PTP_WAIT m_pWait = nullptr;

    std::unique_ptr<CAsyncParams> m_pParams;
};


// ----------------------------------------------------------------------
// Declarations of functions
// 


// ------------------------------------------------------------
// Function: StartWaitRoutine
// Return type: void
// Description: starts waiting thread
// ------------------------------------------------------------
// Parameters:
//                  phWaitThread : pointer to thread handle
//                        pState : state, that identifies
//                               : asynchronous call
//                     phContext : context handle
//                     pszResult : output string
// Return values: none
// 
// Comments:
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 21.12.2019
// ------------------------------------------------------------
// 
void StartWaitRoutine(
    HANDLE* phWaitThread,
    PRPC_ASYNC_STATE pState,
    context_handle_t* phContext,
    wchar_t* pszResult
);


// ------------------------------------------------------------
// Function: CallAndWaitForSignal
// Return type: DWORD
// Description: calls an asynchronous function and waits for completion
// ------------------------------------------------------------
// Parameters:
//                       lpParam : pointer to buffer, that contains
//                               : call's data
// Return values:
//                 ERROR_SUCCESS : function completed normally
//                     Undefined : in case of termination
// 
// Comments: 
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 21.12.2019
// ------------------------------------------------------------
// 
DWORD WINAPI CallAndWaitForSignal( LPVOID lpParam );