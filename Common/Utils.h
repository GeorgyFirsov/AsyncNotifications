#pragma once

#include <iomanip>
#include <atomic>
#include <thread>
#include <sstream>
#include <iostream>

#include "../AsyncNotifications/AsyncNotificationsInterface_h.h"

#define FUNC_FAILURE_STR( _func ) TEXT( #_func ) L" failed. "

#define TID L"[", std::this_thread::get_id(), L"] "


// ------------------------------------------------------------
// Class: CAsyncControl
// Description: all arguments of asyncronous calls will be
//              saved in such structures.
// ------------------------------------------------------------
// Parameters (for constructors): none
// 
// Members:
//                m_pState : pointer to async state necessary
//                         : for MS AsyncRPC
//              m_hContext : context handle
//             m_pszResult : pointer to output string that 
//                           will be filled with event-string
// 
// Comments: 
//       
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 15.12.2019
// ------------------------------------------------------------
//
struct CAsyncControl
{
    PRPC_ASYNC_STATE m_pState;
    context_handle_t m_hContext;
    wchar_t*         m_pszResult;
};


// ------------------------------------------------------------
// Class: CContextHandle
// Description: encapsulates client-specific information.
//              context_handle_t will be casted to CContextHandle*
// ------------------------------------------------------------
// Parameters (for constructors): none
// 
// Members:
//           nSubsciptions : number of client's subscriptions
// Comments: 
//     nSubscriptions is atomic counter
//       
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 19.12.2019
// ------------------------------------------------------------
//
struct CContextHandle
{
    //
    // This fiels will be shared between several threads,
    // so it should be atomic
    // 
    std::atomic_size_t nSubsciptions = 0;
};


// ------------------------------------------------------------
// Function: GetContext
// Return type: CContextHandle*
// Description: Retrieves a pointer to context handle class
//              from raw context handle
// ------------------------------------------------------------
// Parameters:
//                      hContext : raw context handle
// Return values:
//        context handle pointer : pointer to CContextHandle instance
// 
// Comments: 
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 20.12.2019
// ------------------------------------------------------------
// 
inline constexpr auto GetContext( context_handle_t hContext ) 
{ 
    return static_cast<CContextHandle*>( hContext ); 
}


namespace
{
    //
    // Iteration "terminator" with zero params
    // 
    inline void ThreadSafePrintImpl( std::wstringstream& out )
    {
        out << std::endl;
    }

    //
    // Main output function with variadic number of arguments
    // 
    template<typename T, typename... Ts>
    void ThreadSafePrintImpl( std::wstringstream& out, T&& first, Ts&&... remaining )
    {
        out << std::forward<T>( first );
        ThreadSafePrintImpl( out, std::forward<Ts>( remaining )... );
    }

} // anonymous namespace


// ------------------------------------------------------------
// Function: ThreadSafePrint
// Return type: void
// Description: prints all parameters into stream without
//              any pain connected with multithreading
// ------------------------------------------------------------
// Parameters:
//                           out : stream to write into
//                        params : variadic number of values
//                               : to print
// Return values:
// 
// Comments: 
//      No locks and hense no context swiching required for 
//      execution.
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 20.12.2019
// ------------------------------------------------------------
// 
template<typename... Ts>
void ThreadSafePrint( std::wostream& out, Ts&&... params )
{
    std::wstringstream stream;
    ThreadSafePrintImpl( stream, std::forward<Ts>( params )... );
    out << stream.str();
}
