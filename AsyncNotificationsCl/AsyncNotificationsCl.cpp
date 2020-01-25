#include "ClIncludes.h"
#include "ClUtils.h"


int wmain()
{
    TRACE_FUNC;

    try
    {
        CClient client;

        //
        // Event loop
        // 
        wchar_t string[dwMaxStringLength];
        while (true)
        {
            memset( 
                string, 
                0, 
                _countof( string ) * sizeof( decltype( string[0] ) ) 
            );

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
            else if (*string != L'+' && *string != L'-' || wcslen( string ) != 2)
            {
                //
                // Just ignore wrong strings
                // 
                continue;
            }

            if (*string == L'+')
            {
                DWORD dwReply = client.RpcAddSubscription( string[1] );
                DEBUG_TRACE( DL_EXTENDED, L"RpcAddSubscription == ", dwReply );
            }
            else if (*string == L'-')
            {
                DWORD dwReply = client.RpcCancelSubscription( string[1] );
                DEBUG_TRACE( DL_EXTENDED, L"RpcCancelSubscription == ", dwReply );
            }
        }  // while(true)
    } // try
    catch (const std::runtime_error& error)
    {
        std::cout << error.what();
    }
}