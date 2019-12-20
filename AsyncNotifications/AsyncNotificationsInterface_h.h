

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for AsyncNotificationsInterface.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __AsyncNotificationsInterface_h_h__
#define __AsyncNotificationsInterface_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "wtypes.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __AsyncNotifications_INTERFACE_DEFINED__
#define __AsyncNotifications_INTERFACE_DEFINED__

/* interface AsyncNotifications */
/* [explicit_handle][strict_context_handle][version][uuid] */ 

#define	pszDefaultProtocol	( L"ncalrpc" )

#define	pszDefaultEndpoint	( L"AsyncNotifications" )

#define	dwMaxStringLength	( 255 )

typedef /* [context_handle_noserialize][context_handle] */ void *context_handle_t;

DWORD RpcOpenSession( 
    /* [in] */ handle_t hFormalParam,
    /* [out] */ context_handle_t *phContext);

DWORD RpcCloseSession( 
    /* [out][in] */ context_handle_t *phContext);

DWORD RpcAddSubscription( 
    /* [out][in] */ context_handle_t *phContext,
    /* [in] */ wchar_t chToAwait);

DWORD RpcCancelSubscription( 
    /* [out][in] */ context_handle_t *phContext,
    /* [in] */ wchar_t chToCancel);

/* [async] */ void  RpcAsyncAwaitForEvent( 
    /* [in] */ PRPC_ASYNC_STATE RpcAsyncAwaitForEvent_AsyncHandle,
    /* [in] */ context_handle_t hContext,
    /* [size_is][string][out] */ wchar_t *pszResult);



extern RPC_IF_HANDLE AsyncNotifications_v1_0_c_ifspec;
extern RPC_IF_HANDLE AsyncNotifications_v1_0_s_ifspec;
#endif /* __AsyncNotifications_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

void __RPC_USER context_handle_t_rundown( context_handle_t );

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


