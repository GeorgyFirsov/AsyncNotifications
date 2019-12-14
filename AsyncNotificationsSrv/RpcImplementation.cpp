#include "SrvIncludes.h"
#include "../Common/Utils.h"

// Automatically generated
#include "../AsyncNotifications/AsyncNotificationsInterface_h.h"

// ----------------------------------------------------------------------
// Functions to open and close client-server session
// 

// ------------------------------------------------------------
// Function: RpcOpenSession
// Return type: DWORD
// Description: Allocates memory buffer for context handle, 
//              associated with concrete client
// ------------------------------------------------------------
// Parameters:
//                  hFormalParam : binding handle (just formal)
//                     phContext : pointer to buffer, that will
//                               : receive requested handle
// Return values:
//                 ERROR_SUCCESS : function succeeded
//       ERROR_INVALID_PARAMETER : phContext is a null-pointer
//       ERROR_NOT_ENOUGH_MEMORY : memory allocation failed
// 
// Comments: 
//      Do not delete returned handle manually!
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 14.12.2019
// ------------------------------------------------------------
// 
DWORD RpcOpenSession(
	/* [in] */ handle_t hFormalParam,
	/* [out] */ context_handle_t* phContext
)
{
	UNREFERENCED_PARAMETER( hFormalParam );

	if(!phContext) {
		return ERROR_INVALID_PARAMETER;
	}

	try
	{
		*phContext = new CContextHandle;
	}
	catch( const std::bad_alloc& )
	{
		return ERROR_NOT_ENOUGH_MEMORY;
	}

	return ERROR_SUCCESS;
}


// ------------------------------------------------------------
// Function: RpcCloseSession
// Return type: DWORD
// Description: frees space allocated for client's context handle
// ------------------------------------------------------------
// Parameters:
//                     phContext : pointer to buffer, that contains
//                               : context handle
// Return values:
//                 ERROR_SUCCESS : function succeeded
//       ERROR_INVALID_PARAMETER : phContext is a null-pointer
// 
// Comments: 
//      Client should call this function remotely on exit close
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 14.12.2019
// ------------------------------------------------------------
// 
DWORD RpcCloseSession(
	/* [out][in] */ context_handle_t* phContext
)
{
	if(!phContext) {
		return ERROR_INVALID_PARAMETER;
	}

	delete (CContextHandle*)*phContext;

	return ERROR_SUCCESS;
}



// ----------------------------------------------------------------------
// Functions to add and cancel subscriptions
// 

// ------------------------------------------------------------
// Function: RpcAddSubscription
// Return type: DWORD
// Description: adds subscription to server's internal data-base
// ------------------------------------------------------------
// Parameters:
//                     phContext :
//                     chToAwait :
// Return values:
//                               :
//
// Comments: 
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 
// ------------------------------------------------------------
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


// ------------------------------------------------------------
// Function: RpcCancelSubscription
// Return type: DWORD
// Description: removes subscription from server's data-base
// ------------------------------------------------------------
// Parameters:
//                     phContext :
//                    chToCancel :
// Return values:
//                               :
// 
// Comments: 
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 
// ------------------------------------------------------------
// 
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

// ------------------------------------------------------------
// Function: RpcCloseSession
// Return type: void
// Description: frees space allocated for client's context handle
// ------------------------------------------------------------
// Parameters:
//  RpcAsyncAwaitForEvent_AsyncHandle :
//                           hContext :
//                          pszResult :
// Return values: none
// 
// Comments: 
//      This function is asyncronous. To complete its call invoke
//      RpcAsyncCompleteCall with corresponding status value in 
//      second parameter. To transmit pszResult string with result
//      onto client just fill it before calling RpcAsyncCompleteCall.
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 
// ------------------------------------------------------------
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