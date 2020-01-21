#include "ClIncludes.h"
#include "ClUtils.h"


int wmain()
{
    TRACE_FUNC;

    //
    // Client's registration
    // 
    RPC_WSTR         pszBindingString = nullptr;
    HANDLE           hBinding = nullptr;
    HANDLE           hWaitThread = nullptr;
    context_handle_t hContext = nullptr;
    wchar_t          pszResult[dwMaxStringLength] = { 0 };
    RPC_ASYNC_STATE  state;

    RPC_STATUS status = ::RpcStringBindingCompose(
        nullptr,
        (RPC_WSTR)pszDefaultProtocol,
        nullptr,
        (RPC_WSTR)pszDefaultEndpoint,
        nullptr,
        &pszBindingString
    );
    if (status != RPC_S_OK) 
    {
        DEBUG_TRACE( DL_CRITICAL, FUNC_FAILURE_STR( RpcStringBindingCompose) );
        return -1;
    }

    status = ::RpcBindingFromStringBinding(
        pszBindingString,
        &hBinding
    );
    if (status != RPC_S_OK) 
    {
        DEBUG_TRACE( DL_CRITICAL, FUNC_FAILURE_STR( RpcBindingFromStringBinding ) );
        return -1;
    }

    RpcTryExcept
    {
        DWORD dwResult = RpcOpenSession( hBinding, &hContext );
        if (dwResult != ERROR_SUCCESS) 
        {
            DEBUG_TRACE( DL_CRITICAL, FUNC_FAILURE_STR( RpcOpenSession ) );
            return -1;
        }
    }
    RpcExcept ( EXCEPTION_EXECUTE_HANDLER )
    {
        DEBUG_TRACE( 
            DL_CRITICAL, FUNC_FAILURE_STR( RpcOpenSession ), L"Error code: ", RpcExceptionCode()
        );
        return -1;
    }
    RpcEndExcept

    status = ::RpcAsyncInitializeHandle(
        &state,
        sizeof( RPC_ASYNC_STATE )
    );
    if (status != RPC_S_OK)
    {
        DEBUG_TRACE( DL_CRITICAL, FUNC_FAILURE_STR( RpcAsyncInitializeHandle ) );
        return -1;
    }

    state.NotificationType = RpcNotificationTypeEvent;
    state.u.hEvent = ::CreateEvent( nullptr, FALSE, FALSE, nullptr );

    if (!state.u.hEvent)
    {
        DEBUG_TRACE( 
            DL_CRITICAL, FUNC_FAILURE_STR( CreateEvent ), L"Error code: ", GetLastError() 
        );
        return -1;
    }

    //
    // Input loop
    // 
    wchar_t string[dwMaxStringLength];
    while (true)
    {
        memset( string, 0, _countof( string ) * sizeof( wchar_t ) );

        std::wcin.getline( string, _countof( string ) );

        if (*string == L'q')
        {
            if (!_wcsicmp( string, L"quit" )) 
            {
                //
                // Normal exit
                // 
                break;
            }
        }
        else if (*string == L'e')
        {
            if (!_wcsicmp( string, L"exit" )) 
            {
                //
                // Abnormal program termination
                // 
                std::terminate();
            }
        }
        else if (*string != L'+' && *string != L'-' || wcslen( string ) != 2) 
        {
            //
            // It is malformed string - ignore it
            // 
            continue;
        }

        if (*string == L'+') 
        {
            RpcTryExcept
            {                
                DWORD dwReply = RpcAddSubscription( hContext, string[1] );

                TRACE_DATA( L"RpcAddSubscription returned ", dwReply );

                if (dwReply == ERROR_SUCCESS)
                {
                    StartWaitRoutine( 
                        &hWaitThread, 
                        &state, 
                        &hContext,
                        pszResult 
                    );
                }
            }
            RpcExcept ( EXCEPTION_EXECUTE_HANDLER )
            {
                DEBUG_TRACE(
                    DL_CRITICAL, FUNC_FAILURE_STR( RpcAddSubscription ), L"Error code: ", RpcExceptionCode()
                );
            }
            RpcEndExcept
        }
        else if (*string == L'-') 
        {
            RpcTryExcept
            {
                DWORD dwReply = RpcCancelSubscription( hContext, string[1] );

                TRACE_DATA( L"RpcCancelSubscription returned ", dwReply );

                if (dwReply != ERROR_SUCCESS && dwReply != ERROR_NOT_FOUND) {
                    TRACE_DATA( L"Cannot cancel the subscription on '", string[1], L"'" );
                }
            }
            RpcExcept ( EXCEPTION_EXECUTE_HANDLER )
            {
                DEBUG_TRACE(
                    DL_CRITICAL, FUNC_FAILURE_STR( RpcCancelSubscription ), L"Error code: ", RpcExceptionCode()
                );
            }
            RpcEndExcept
        }

    }  // while(true)

    //
    // Cleaning up
    // 
    RpcTryExcept
    {
        if (hContext) RpcCloseSession( &hContext );
    }
    RpcExcept ( EXCEPTION_EXECUTE_HANDLER )
    {
        DEBUG_TRACE(
            DL_CRITICAL, FUNC_FAILURE_STR( RpcCloseSession ), L"Error code: ", RpcExceptionCode()
        );
    }
    RpcEndExcept

    if (pszBindingString) ::RpcStringFree( &pszBindingString );
    if (state.u.hEvent) ::CloseHandle( state.u.hEvent );
    if (hBinding) ::CloseHandle( hBinding );
    if (hWaitThread) ::CloseHandle( hWaitThread );

    return 0;

}