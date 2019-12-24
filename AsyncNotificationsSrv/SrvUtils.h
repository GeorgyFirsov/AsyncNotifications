#pragma once
#include "SrvIncludes.h"


// ----------------------------------------------------------------------
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


// ----------------------------------------------------------------------
// Definitions of classes
// 


// ------------------------------------------------------------
// Class: CCriticalSection
// Description: wrapper around WinAPI's CRITICAL_SECTION
// ------------------------------------------------------------
// Parameters (for constructors): none
// 
// Members:
//                        m_cs : internal CRITICAL_SECTION instance
//              
// Member functions:
//                   void lock : locks critical section (EnterCriticalSection)
//                 void unlock : releases critical section (LeaveCriticalSection)
//               bool try_lock : tries to enter critical section (TryEnterCriticalSection)
// 
// Comments: 
//       Wrapper for using CRITICAL_SECTION with std::lock_guard
//       
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 21.12.2019
// ------------------------------------------------------------
//
class CCriticalSection
{
public:
    CCriticalSection() { InitializeCriticalSection( &m_cs ); }
    ~CCriticalSection() { DeleteCriticalSection( &m_cs ); }

    CCriticalSection( const CCriticalSection& ) = delete;
    CCriticalSection& operator=( const CCriticalSection& ) = delete;
    CCriticalSection( CCriticalSection&& ) = delete;
    CCriticalSection& operator=( CCriticalSection&& ) = delete;

    void lock() { EnterCriticalSection( &m_cs ); }
    void unlock() { LeaveCriticalSection( &m_cs ); }
    bool try_lock() { return (bool)TryEnterCriticalSection( &m_cs ); }

private:
    CRITICAL_SECTION m_cs;
};


// ------------------------------------------------------------
// Class: CServer
// Description: it is an abstraction over RPC server. It provides
//              subscriptions' and subscribers' management.
// ------------------------------------------------------------
// Parameters (for constructors): none
// 
// Members:
//             m_subscriptions : every subscription grouped by symbol
//           m_csSubscriptions : corresponding critical section
//                     m_calls : control block and counter for each
//                             : client's asynchronous call
//                   m_csCalls : corresponding critical section
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
    subscriptions_t      m_subscriptions;
    CCriticalSection  m_csSubscriptions;

    client_controls_t m_calls;
    CCriticalSection  m_csCalls;
};


//
// Macro used to obtain server instance
// 
#define g_Server CServer::GetInstance()


// ------------------------------------------------------------
// Function: StartServer
// Return type: RPC_STATUS
// Description: initializes server application and performs
//              necessary for RPC preparations.
// ------------------------------------------------------------
// Parameters: none
// 
// Return values:
//                      RPC_S_OK : function succeeded
//                    error code : in case of any error. See
//                               : output for more information
//                               : about the error.
// 
// Comments: 
//     You shold explicitly call StopServer function at exit
//     from main function.
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 15.12.2019
// ------------------------------------------------------------
// 
RPC_STATUS StartServer();


// ------------------------------------------------------------
// Function: StopServer
// Return type: void
// Description: performs final clean-up at process' exit
// ------------------------------------------------------------
// Parameters: none
// 
// Return values: none
// 
// Comments: 
//     You should explicitly call this function before exiting
//     from main.
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 15.12.2019
// ------------------------------------------------------------
// 
void StopServer();