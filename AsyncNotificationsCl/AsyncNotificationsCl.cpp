#include "ClIncludes.h"
#include "ClUtils.h"


int wmain()
{
	//
	// Client's registration
	// 
	RPC_WSTR		pszBindingString = nullptr;
	HANDLE			hBinding = nullptr;
	HANDLE			hWaitThread = nullptr;
	CContextHandle* hContext = nullptr;
	wchar_t			pszResult[dwMaxStringLength] = { 0 };
	RPC_ASYNC_STATE state;

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
		ThreadSafePrint( std::wcout, TID, FUNC_FAILURE_STR( RpcStringBindingCompose ) );
		return -1;
	}

	status = ::RpcBindingFromStringBinding(
		pszBindingString,
		&hBinding
	);
	if (status != RPC_S_OK) 
	{
		ThreadSafePrint( std::wcout, TID, FUNC_FAILURE_STR( RpcBindingFromStringBinding ) );
		return -1;
	}

	RpcTryExcept
	{
		DWORD dwResult = RpcOpenSession(
			hBinding,
			reinterpret_cast<context_handle_t*>( &hContext )
		);
		if (dwResult != ERROR_SUCCESS) 
		{
			ThreadSafePrint( std::wcout, TID, FUNC_FAILURE_STR( RpcOpenSession ) );
			return -1;
		}
	}
	RpcExcept ( EXCEPTION_EXECUTE_HANDLER )
	{
		ThreadSafePrint( 
			std::wcout, 
			TID, 
			L"RPC call (RpcOpenSession) fatal error with code: ", 
			RpcExceptionCode() 
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
		ThreadSafePrint( std::wcout, TID, FUNC_FAILURE_STR( RpcAsyncInitializeHandle ) );
		return -1;
	}

	state.NotificationType = RpcNotificationTypeEvent;
	state.u.hEvent = ::CreateEvent( nullptr, FALSE, FALSE, nullptr );

	if (!state.u.hEvent)
	{
		ThreadSafePrint( 
			std::wcout, 
			TID, 
			FUNC_FAILURE_STR( CreateEvent ), 
			L"Code: ", 
			GetLastError() 
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
				ExitProcess( ERROR_CANCELLED );
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
				DWORD dwReply = RpcAddSubscription( 
					reinterpret_cast<context_handle_t*>( &hContext ), 
					string[1] 
				);

				ThreadSafePrint( std::wcout, TID, L"RpcAddSubscription returned ", dwReply );

				if (dwReply == ERROR_SUCCESS)
				{
					StartWaitRoutine( 
						&hWaitThread, 
						&state, 
						reinterpret_cast<context_handle_t*>( &hContext ),
						pszResult 
					);
				}
			}
			RpcExcept ( EXCEPTION_EXECUTE_HANDLER )
			{
				ThreadSafePrint( 
					std::wcout, 
					TID, 
					L"RPC call (RpcAddSubscription) fatal error with code: ", 
					RpcExceptionCode() 
				);
			}
			RpcEndExcept
		}
		else if (*string == L'-') 
		{
			RpcTryExcept
			{
				DWORD dwReply = RpcCancelSubscription( (context_handle_t*)&hContext, string[1] );

				ThreadSafePrint( std::wcout, TID, L"RpcCancelSubscription returned ", dwReply );

				if (dwReply != ERROR_SUCCESS && dwReply != ERROR_NOT_FOUND) {
					ThreadSafePrint( std::wcout, TID, L"Cannot cancel the subscription on '", string[1], L"'" );
				}
			}
			RpcExcept ( EXCEPTION_EXECUTE_HANDLER )
			{
				ThreadSafePrint( 
					std::wcout, 
					TID, 
					L"RPC call (RpcCancelSubscription) fatal error with code: ", 
					RpcExceptionCode() 
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
		if (hContext) RpcCloseSession( reinterpret_cast<context_handle_t*>( &hContext ) );
	}
	RpcExcept ( EXCEPTION_EXECUTE_HANDLER )
	{
		ThreadSafePrint(
			std::wcout,
			TID,
			L"RPC call (RpcCloseSession) fatal error with code: ",
			RpcExceptionCode()
		);
	}
	RpcEndExcept

	if (pszBindingString) ::RpcStringFree( &pszBindingString );
	if (state.u.hEvent) ::CloseHandle( state.u.hEvent );
	if (hBinding) ::CloseHandle( hBinding );
	if (hWaitThread) ::CloseHandle( hWaitThread );

	return 0;

}