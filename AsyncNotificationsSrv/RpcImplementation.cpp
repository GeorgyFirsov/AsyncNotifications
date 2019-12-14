#include "SrvIncludes.h"
#include "../Common/Utils.h"

// Automatically generated
#include "../AsyncNotifications/AsyncNotificationsInterface_h.h"

// ----------------------------------------------------------------------
// Functions to open and close client-server session
// 

DWORD RpcOpenSession(
	/* [in] */ handle_t hFormalParam,
	/* [out] */ context_handle_t* phContext
)
{
	UNREFERENCED_PARAMETER( hFormalParam );
	UNREFERENCED_PARAMETER( phContext );

	// Empty for now
	return ERROR_CALL_NOT_IMPLEMENTED;
}


DWORD RpcCloseSession(
	/* [out][in] */ context_handle_t* phContext
)
{
	UNREFERENCED_PARAMETER( phContext );

	// Empty for now
	return ERROR_CALL_NOT_IMPLEMENTED;
}



// ----------------------------------------------------------------------
// Functions to add and cancel subscriptions
// 

DWORD RpcAddSubscription(
	/* [out][in] */ context_handle_t* phContext,
	/* [in] */ wchar_t chToAwait
)
{
	UNREFERENCED_PARAMETER( phContext );
	UNREFERENCED_PARAMETER( chToAwait );

	// Empty for now
	return ERROR_CALL_NOT_IMPLEMENTED;
}


DWORD RpcCancelSubscription(
	/* [out][in] */ context_handle_t* phContext,
	/* [in] */ wchar_t chToCancel
)
{
	UNREFERENCED_PARAMETER( phContext );
	UNREFERENCED_PARAMETER( chToCancel );

	// Empty for now
	return ERROR_CALL_NOT_IMPLEMENTED;
}



// ----------------------------------------------------------------------
// Asynchronous function used to notify client about an event
// 

/* [async] */ void  RpcAsyncAwaitForEvent(
	/* [in] */ PRPC_ASYNC_STATE RpcAsyncAwaitForEvent_AsyncHandle,
	/* [in] */ context_handle_t hContext,
	/* [size_is][string][out] */ wchar_t* pszResult)
{
	UNREFERENCED_PARAMETER( hContext );
	UNREFERENCED_PARAMETER( pszResult );

	// Empty for now

#pragma warning(disable: 6031)  // Return value ignored : 'RpcAsyncAbortCall'
	::RpcAsyncAbortCall( 
		RpcAsyncAwaitForEvent_AsyncHandle, 
		ERROR_CALL_NOT_IMPLEMENTED 
	);
#pragma warning(default: 6031)
}




// ----------------------------------------------------------------------
// Utility functions necessary for MS RPC
// 

void __RPC_USER context_handle_t_rundown( context_handle_t hContext )
{
	std::wcout << L"Rundown on handle: " << as_hex( hContext, 8 ) << std::endl;

	RpcCloseSession( &hContext );
}


_Must_inspect_result_
_Ret_maybenull_ _Post_writable_byte_size_( size )
void* __RPC_USER MIDL_user_allocate( _In_ size_t size )
{
	return malloc( size );
}


void __RPC_USER MIDL_user_free( _Pre_maybenull_ _Post_invalid_ void* ptr )
{
	if(ptr) {
		free( ptr );
	}
	ptr = nullptr;
}