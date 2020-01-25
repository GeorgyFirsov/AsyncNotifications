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
//       m_bNewWaitThreadNeeded : flag that means that no waiting thread exists
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

    _Check_return_
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

    void CleanUpWait();

private:
    std::atomic_bool m_bNewWaitThreadNeeded;

    RPC_ASYNC_STATE m_state;

    PTP_WAIT m_pWait = nullptr;

    wchar_t m_szResult[dwMaxStringLength];

    std::unique_ptr<CAsyncParams> m_pParams;
};


// ----------------------------------------------------------------------
// Declarations of functions
// 


// ------------------------------------------------------------
// Function: WaitCompletedCallback
// Return type: void
// Description: callback called as async procedure returns
// ------------------------------------------------------------
// Parameters:
//                      Instance : unused
//                       Context : pointer to CClient object 
//                               : corresponding to async call
//                          Wait : unused
//                    WaitResult : unused
// Return values: none
// 
// Comments:
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 25.01.2020
// ------------------------------------------------------------
//
VOID NTAPI WaitCompletedCallback(
    _Inout_ PTP_CALLBACK_INSTANCE /* Instance */,
    _Inout_opt_ PVOID Context,
    _Inout_ PTP_WAIT /* Wait */,
    _In_ TP_WAIT_RESULT /* WaitResult */
);
