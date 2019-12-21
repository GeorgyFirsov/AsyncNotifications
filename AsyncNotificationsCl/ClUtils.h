#pragma once
#include "ClIncludes.h"


// ------------------------------------------------------------
// Function: StartWaitRoutine
// Return type: void
// Description: starts waiting thread
// ------------------------------------------------------------
// Parameters:
//                  phWaitThread : pointer to thread handle
//                        pState : state, that identifies
//                               : asynchronous call
//                     phContext : context handle
//                     pszResult : output string
// Return values: none
// 
// Comments:
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 21.12.2019
// ------------------------------------------------------------
// 
void StartWaitRoutine(
	HANDLE* phWaitThread,
	PRPC_ASYNC_STATE pState,
	context_handle_t* phContext,
	wchar_t* pszResult
);


// ------------------------------------------------------------
// Function: CallAndWaitForSignal
// Return type: DWORD
// Description: calls an asynchronous function and waits for completion
// ------------------------------------------------------------
// Parameters:
//                       lpParam : pointer to buffer, that contains
//                               : call's data
// Return values:
//                 ERROR_SUCCESS : function completed normally
//                     Undefined : in case of termination
// 
// Comments: 
// 
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 21.12.2019
// ------------------------------------------------------------
// 
DWORD WINAPI CallAndWaitForSignal( LPVOID lpParam );