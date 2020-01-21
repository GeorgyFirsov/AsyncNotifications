#include "SrvIncludes.h"
#include "SrvUtils.h"


int wmain()
{
    TRACE_FUNC;

    //
    // Here I initialize server application
    // 
    RPC_STATUS status = StartServer();
    if (status != RPC_S_OK) {
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
    StopServer();

    return 0;
}