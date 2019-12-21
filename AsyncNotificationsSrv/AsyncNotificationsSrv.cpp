#include "SrvIncludes.h"
#include "SrvUtils.h"


int wmain()
{
    ThreadSafePrint( std::wcout, TID, L"Main" );

    //
    // Here I initialize server application
    // 
    RPC_STATUS status = ::RpcServerUseProtseqEp(
        (RPC_WSTR)pszDefaultProtocol,
        RPC_C_PROTSEQ_MAX_REQS_DEFAULT,
        (RPC_WSTR)pszDefaultEndpoint,
        nullptr
    );
    if (status != RPC_S_OK) 
    {
        std::wcout << FUNC_FAILURE_STR( RpcServerUseProtseqEp ) << std::endl;
        return -1;
    }

    status = ::RpcServerRegisterIfEx(
        AsyncNotifications_v1_0_s_ifspec,
        nullptr,
        nullptr,
        0,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        nullptr
    );
    if (status != RPC_S_OK) 
    {
        std::wcout << FUNC_FAILURE_STR( RpcServerRegisterIfEx ) << std::endl;
        return -1;
    }

    status = ::RpcServerListen(
        1,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        TRUE
    );
    if (status != RPC_S_OK) 
    {
        std::wcout << FUNC_FAILURE_STR( RpcServerListen ) << std::endl;
        return -1;
    }

    //
    // Main event loop
    // 
    wchar_t string[dwMaxStringLength];

    while (true)
    {
        memset( string, 0, dwMaxStringLength * sizeof( wchar_t ) );
        
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
                // Abnormal termination
                // 
                std::terminate();
            }
        }

        //
        // It is a common string - let's analyze it
        // 
        g_Server.AnalyzeStringAndNotify( string, _countof( string ) );
    } // while(true)

    //
    // Тут теперь надо всё почистить
    // 
#pragma warning(disable: 6031)  // Return value ignored
    ::RpcMgmtStopServerListening( nullptr );
    ::RpcServerUnregisterIf( nullptr, nullptr, TRUE );
#pragma warning(default: 6031)

    return 0;
}