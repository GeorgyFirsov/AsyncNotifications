#include "ClUtils.h"


void StartWaitRoutine( 
    HANDLE* phWaitThread, 
    PRPC_ASYNC_STATE pState, 
    context_handle_t* phContext, 
    wchar_t* pszResult 
)
{
    ThreadSafePrint( std::wcout, TID, __FUNCTIONW__ );

    RPC_STATUS status = ::RpcAsyncGetCallStatus( pState );
    if (status == RPC_S_CALLPENDING || status == ERROR_IO_PENDING) 
    {
        //
        // If our call is still pending, we don't need to call it again
        // 
        return;
    }
    else
    {
        //
        // If an asynchronous call isn't running, we need to close handle.
        // Actually, waiting thread can be still alive, but here it can be
        // only in terminal state.
        // 
        ::CloseHandle( *phWaitThread );
        *phWaitThread = nullptr;
    }

    //
    // Will be deleted in waiting function
    // 
    auto pParams = new CAsyncControl{ pState, *phContext, pszResult };

    *phWaitThread = ::CreateThread(
        nullptr,
        0,
        CallAndWaitForSignal,
        pParams,
        0,
        nullptr
    );
}


DWORD CallAndWaitForSignal( LPVOID lpParam )
{
    ThreadSafePrint( std::wcout, TID, __FUNCTIONW__ );

    CAsyncControl params = *(CAsyncControl*)lpParam;

    while (true)
    {
        //
        // Here we call asynchronous function and put current
        // thread into waiting state
        // 
        RpcAsyncAwaitForEvent( params.m_pState, params.m_hContext, params.m_pszResult );

        ::WaitForSingleObject( params.m_pState->u.hEvent, INFINITE );

        //
        // Receive result, print it (maybe quit) and make call again
        // 
        ULONG nReply;

#pragma warning(disable: 28193) // 'status' holds a value that must be examined oO
        RPC_STATUS status = ::RpcAsyncCompleteCall( params.m_pState, &nReply );
#pragma warning(default: 28193)

        if (status != RPC_S_OK)
        {
            ThreadSafePrint( std::wcout, TID, L"RpcAsyncAwaitForEvent was terminated by server" );
            break;
        }

        ThreadSafePrint( std::wcout, TID, L"Function returned: ", params.m_pszResult );
    }

    //
    // Normal exit from thread
    // 
    delete (CAsyncControl*)lpParam;

    return ERROR_SUCCESS;
}