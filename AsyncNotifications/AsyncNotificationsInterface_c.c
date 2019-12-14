

/* this ALWAYS GENERATED file contains the RPC client stubs */


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

#if defined(_M_AMD64)


#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/

#include <string.h>

#include "AsyncNotificationsInterface_h.h"

#define TYPE_FORMAT_STRING_SIZE   35                                
#define PROC_FORMAT_STRING_SIZE   237                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _AsyncNotificationsInterface_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } AsyncNotificationsInterface_MIDL_TYPE_FORMAT_STRING;

typedef struct _AsyncNotificationsInterface_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } AsyncNotificationsInterface_MIDL_PROC_FORMAT_STRING;

typedef struct _AsyncNotificationsInterface_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } AsyncNotificationsInterface_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};

static const RPC_SYNTAX_IDENTIFIER  _NDR64_RpcTransferSyntax = 
{{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}};



extern const AsyncNotificationsInterface_MIDL_TYPE_FORMAT_STRING AsyncNotificationsInterface__MIDL_TypeFormatString;
extern const AsyncNotificationsInterface_MIDL_PROC_FORMAT_STRING AsyncNotificationsInterface__MIDL_ProcFormatString;
extern const AsyncNotificationsInterface_MIDL_EXPR_FORMAT_STRING AsyncNotificationsInterface__MIDL_ExprFormatString;

#define GENERIC_BINDING_TABLE_SIZE   0            


/* Standard interface: AsyncNotifications, ver. 1.0,
   GUID={0xB3102C22,0x66E6,0x4B94,{0x88,0xF2,0x7C,0x52,0x91,0xCE,0x22,0xC0}} */

 extern const MIDL_STUBLESS_PROXY_INFO AsyncNotifications_ProxyInfo;


static const RPC_CLIENT_INTERFACE AsyncNotifications___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0xB3102C22,0x66E6,0x4B94,{0x88,0xF2,0x7C,0x52,0x91,0xCE,0x22,0xC0}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    &AsyncNotifications_ProxyInfo,
    0x02000000
    };
RPC_IF_HANDLE AsyncNotifications_v1_0_c_ifspec = (RPC_IF_HANDLE)& AsyncNotifications___RpcClientInterface;

extern const MIDL_STUB_DESC AsyncNotifications_StubDesc;

static RPC_BINDING_HANDLE AsyncNotifications__MIDL_AutoBindHandle;


DWORD RpcOpenSession( 
    /* [in] */ handle_t hFormalParam,
    /* [out] */ context_handle_t *phContext)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall3(
                  ( PMIDL_STUBLESS_PROXY_INFO  )&AsyncNotifications_ProxyInfo,
                  0,
                  0,
                  hFormalParam,
                  phContext);
    return ( DWORD  )_RetVal.Simple;
    
}


DWORD RpcCloseSession( 
    /* [out][in] */ context_handle_t *phContext)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall3(
                  ( PMIDL_STUBLESS_PROXY_INFO  )&AsyncNotifications_ProxyInfo,
                  1,
                  0,
                  phContext);
    return ( DWORD  )_RetVal.Simple;
    
}


DWORD RpcAddSubscription( 
    /* [out][in] */ context_handle_t *phContext,
    /* [in] */ wchar_t chToAwait)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall3(
                  ( PMIDL_STUBLESS_PROXY_INFO  )&AsyncNotifications_ProxyInfo,
                  2,
                  0,
                  phContext,
                  chToAwait);
    return ( DWORD  )_RetVal.Simple;
    
}


DWORD RpcCancelSubscription( 
    /* [out][in] */ context_handle_t *phContext,
    /* [in] */ wchar_t chToCancel)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall3(
                  ( PMIDL_STUBLESS_PROXY_INFO  )&AsyncNotifications_ProxyInfo,
                  3,
                  0,
                  phContext,
                  chToCancel);
    return ( DWORD  )_RetVal.Simple;
    
}


/* [async] */ void  RpcAsyncAwaitForEvent( 
    /* [in] */ PRPC_ASYNC_STATE RpcAsyncAwaitForEvent_AsyncHandle,
    /* [in] */ context_handle_t hContext,
    /* [size_is][string][out] */ wchar_t *pszResult)
{

    Ndr64AsyncClientCall(
                        ( PMIDL_STUBLESS_PROXY_INFO  )&AsyncNotifications_ProxyInfo,
                        4,
                        0,
                        RpcAsyncAwaitForEvent_AsyncHandle,
                        hContext,
                        pszResult);
    
}


#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const AsyncNotificationsInterface_MIDL_PROC_FORMAT_STRING AsyncNotificationsInterface__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure RpcOpenSession */

			0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 10 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 12 */	NdrFcShort( 0x0 ),	/* X64 Stack size/offset = 0 */
/* 14 */	NdrFcShort( 0x0 ),	/* 0 */
/* 16 */	NdrFcShort( 0x40 ),	/* 64 */
/* 18 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 20 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */
/* 28 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 30 */	NdrFcShort( 0x110 ),	/* Flags:  out, simple ref, */
/* 32 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 34 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 36 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 38 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 40 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RpcCloseSession */

/* 42 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 44 */	NdrFcLong( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x1 ),	/* 1 */
/* 50 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 52 */	0x30,		/* FC_BIND_CONTEXT */
			0xea,		/* Ctxt flags:  via ptr, in, out, strict, serialize, */
/* 54 */	NdrFcShort( 0x0 ),	/* X64 Stack size/offset = 0 */
/* 56 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 58 */	NdrFcShort( 0x38 ),	/* 56 */
/* 60 */	NdrFcShort( 0x40 ),	/* 64 */
/* 62 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 64 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x0 ),	/* 0 */
/* 70 */	NdrFcShort( 0x0 ),	/* 0 */
/* 72 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 74 */	NdrFcShort( 0x118 ),	/* Flags:  in, out, simple ref, */
/* 76 */	NdrFcShort( 0x0 ),	/* X64 Stack size/offset = 0 */
/* 78 */	NdrFcShort( 0xe ),	/* Type Offset=14 */

	/* Return value */

/* 80 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 82 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 84 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RpcAddSubscription */

/* 86 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 88 */	NdrFcLong( 0x0 ),	/* 0 */
/* 92 */	NdrFcShort( 0x2 ),	/* 2 */
/* 94 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 96 */	0x30,		/* FC_BIND_CONTEXT */
			0xea,		/* Ctxt flags:  via ptr, in, out, strict, serialize, */
/* 98 */	NdrFcShort( 0x0 ),	/* X64 Stack size/offset = 0 */
/* 100 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 102 */	NdrFcShort( 0x3e ),	/* 62 */
/* 104 */	NdrFcShort( 0x40 ),	/* 64 */
/* 106 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 108 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 116 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 118 */	NdrFcShort( 0x118 ),	/* Flags:  in, out, simple ref, */
/* 120 */	NdrFcShort( 0x0 ),	/* X64 Stack size/offset = 0 */
/* 122 */	NdrFcShort( 0xe ),	/* Type Offset=14 */

	/* Parameter chToAwait */

/* 124 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 126 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 128 */	0x5,		/* FC_WCHAR */
			0x0,		/* 0 */

	/* Return value */

/* 130 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 132 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 134 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RpcCancelSubscription */

/* 136 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 138 */	NdrFcLong( 0x0 ),	/* 0 */
/* 142 */	NdrFcShort( 0x3 ),	/* 3 */
/* 144 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 146 */	0x30,		/* FC_BIND_CONTEXT */
			0xea,		/* Ctxt flags:  via ptr, in, out, strict, serialize, */
/* 148 */	NdrFcShort( 0x0 ),	/* X64 Stack size/offset = 0 */
/* 150 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 152 */	NdrFcShort( 0x3e ),	/* 62 */
/* 154 */	NdrFcShort( 0x40 ),	/* 64 */
/* 156 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 158 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 168 */	NdrFcShort( 0x118 ),	/* Flags:  in, out, simple ref, */
/* 170 */	NdrFcShort( 0x0 ),	/* X64 Stack size/offset = 0 */
/* 172 */	NdrFcShort( 0xe ),	/* Type Offset=14 */

	/* Parameter chToCancel */

/* 174 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 176 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 178 */	0x5,		/* FC_WCHAR */
			0x0,		/* 0 */

	/* Return value */

/* 180 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 182 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 184 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RpcAsyncAwaitForEvent */

/* 186 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 188 */	NdrFcLong( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0x4 ),	/* 4 */
/* 194 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 196 */	0x30,		/* FC_BIND_CONTEXT */
			0x4a,		/* Ctxt flags:  in, strict, serialize, */
/* 198 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 200 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 202 */	NdrFcShort( 0x24 ),	/* 36 */
/* 204 */	NdrFcShort( 0x8 ),	/* 8 */
/* 206 */	0xc5,		/* Oi2 Flags:  srv must size, has return, has ext, has async handle */
			0x3,		/* 3 */
/* 208 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 210 */	NdrFcShort( 0x1 ),	/* 1 */
/* 212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 216 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hContext */

/* 218 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 220 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 222 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pszResult */

/* 224 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 226 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 228 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 230 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 232 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 234 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const AsyncNotificationsInterface_MIDL_TYPE_FORMAT_STRING AsyncNotificationsInterface__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	0x30,		/* FC_BIND_CONTEXT */
			0xaa,		/* Ctxt flags:  via ptr, out, strict, serialize, */
/*  8 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 10 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 12 */	NdrFcShort( 0x2 ),	/* Offset= 2 (14) */
/* 14 */	0x30,		/* FC_BIND_CONTEXT */
			0xeb,		/* Ctxt flags:  via ptr, in, out, strict, serialize, can't be null */
/* 16 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 18 */	0x30,		/* FC_BIND_CONTEXT */
			0x4b,		/* Ctxt flags:  in, strict, serialize, can't be null */
/* 20 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 22 */	
			0x11, 0x0,	/* FC_RP */
/* 24 */	NdrFcShort( 0x2 ),	/* Offset= 2 (26) */
/* 26 */	
			0x25,		/* FC_C_WSTRING */
			0x44,		/* FC_STRING_SIZED */
/* 28 */	0x40,		/* Corr desc:  constant, val=255 */
			0x0,		/* 0 */
/* 30 */	NdrFcShort( 0xff ),	/* 255 */
/* 32 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */

			0x0
        }
    };

static const unsigned short AsyncNotifications_FormatStringOffsetTable[] =
    {
    0,
    42,
    86,
    136,
    186
    };



#endif /* defined(_M_AMD64)*/



/* this ALWAYS GENERATED file contains the RPC client stubs */


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

#if defined(_M_AMD64)




#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif


#include "ndr64types.h"
#include "pshpack8.h"


typedef 
NDR64_FORMAT_CHAR
__midl_frag25_t;
extern const __midl_frag25_t __midl_frag25;

typedef 
struct NDR64_SIZED_CONFORMANT_STRING_FORMAT
__midl_frag24_t;
extern const __midl_frag24_t __midl_frag24;

typedef 
struct 
{
    NDR64_FORMAT_UINT32 frag1;
    struct _NDR64_EXPR_NOOP frag2;
    struct _NDR64_EXPR_CONST64 frag3;
}
__midl_frag23_t;
extern const __midl_frag23_t __midl_frag23;

typedef 
struct _NDR64_POINTER_FORMAT
__midl_frag22_t;
extern const __midl_frag22_t __midl_frag22;

typedef 
struct _NDR64_CONTEXT_HANDLE_FORMAT
__midl_frag21_t;
extern const __midl_frag21_t __midl_frag21;

typedef 
struct 
{
    struct _NDR64_PROC_FORMAT frag1;
    struct _NDR64_BIND_AND_NOTIFY_EXTENSION frag2;
    struct _NDR64_PARAM_FORMAT frag3;
    struct _NDR64_PARAM_FORMAT frag4;
    struct _NDR64_PARAM_FORMAT frag5;
}
__midl_frag20_t;
extern const __midl_frag20_t __midl_frag20;

typedef 
NDR64_FORMAT_CHAR
__midl_frag18_t;
extern const __midl_frag18_t __midl_frag18;

typedef 
struct _NDR64_CONTEXT_HANDLE_FORMAT
__midl_frag17_t;
extern const __midl_frag17_t __midl_frag17;

typedef 
struct _NDR64_POINTER_FORMAT
__midl_frag16_t;
extern const __midl_frag16_t __midl_frag16;

typedef 
struct 
{
    struct _NDR64_PROC_FORMAT frag1;
    struct _NDR64_BIND_AND_NOTIFY_EXTENSION frag2;
    struct _NDR64_PARAM_FORMAT frag3;
    struct _NDR64_PARAM_FORMAT frag4;
    struct _NDR64_PARAM_FORMAT frag5;
}
__midl_frag15_t;
extern const __midl_frag15_t __midl_frag15;

typedef 
struct 
{
    struct _NDR64_PROC_FORMAT frag1;
    struct _NDR64_BIND_AND_NOTIFY_EXTENSION frag2;
    struct _NDR64_PARAM_FORMAT frag3;
    struct _NDR64_PARAM_FORMAT frag4;
}
__midl_frag6_t;
extern const __midl_frag6_t __midl_frag6;

typedef 
struct _NDR64_CONTEXT_HANDLE_FORMAT
__midl_frag4_t;
extern const __midl_frag4_t __midl_frag4;

typedef 
struct _NDR64_POINTER_FORMAT
__midl_frag3_t;
extern const __midl_frag3_t __midl_frag3;

typedef 
struct 
{
    struct _NDR64_PROC_FORMAT frag1;
    struct _NDR64_BIND_AND_NOTIFY_EXTENSION frag2;
    struct _NDR64_PARAM_FORMAT frag3;
    struct _NDR64_PARAM_FORMAT frag4;
}
__midl_frag2_t;
extern const __midl_frag2_t __midl_frag2;

typedef 
NDR64_FORMAT_UINT32
__midl_frag1_t;
extern const __midl_frag1_t __midl_frag1;

static const __midl_frag25_t __midl_frag25 =
0x5    /* FC64_INT32 */;

static const __midl_frag24_t __midl_frag24 =
{ 
/* *wchar_t */
    { 
    /* *wchar_t */
        0x64,    /* FC64_CONF_WCHAR_STRING */
        { 
        /* *wchar_t */
            1,
            0,
            0,
            0,
            0,
            0,
            0,
            0
        },
        (NDR64_UINT16) 2 /* 0x2 */
    },
    &__midl_frag23
};

static const __midl_frag23_t __midl_frag23 =
{ 
/*  */
    (NDR64_UINT32) 1 /* 0x1 */,
    { 
    /* struct _NDR64_EXPR_NOOP */
        0x5,    /* FC_EXPR_PAD */
        (NDR64_UINT8) 4 /* 0x4 */,
        (NDR64_UINT16) 0 /* 0x0 */
    },
    { 
    /* struct _NDR64_EXPR_CONST64 */
        0x2,    /* FC_EXPR_CONST64 */
        0x7,    /* FC64_INT64 */
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT64) 255 /* 0xff */
    }
};

static const __midl_frag22_t __midl_frag22 =
{ 
/* *wchar_t */
    0x20,    /* FC64_RP */
    (NDR64_UINT8) 0 /* 0x0 */,
    (NDR64_UINT16) 0 /* 0x0 */,
    &__midl_frag24
};

static const __midl_frag21_t __midl_frag21 =
{ 
/* struct _NDR64_CONTEXT_HANDLE_FORMAT */
    0x70,    /* FC64_BIND_CONTEXT */
    (NDR64_UINT8) 75 /* 0x4b */,
    (NDR64_UINT8) 0 /* 0x0 */,
    (NDR64_UINT8) 0 /* 0x0 */
};

static const __midl_frag20_t __midl_frag20 =
{ 
/* RpcAsyncAwaitForEvent */
    { 
    /* RpcAsyncAwaitForEvent */      /* procedure RpcAsyncAwaitForEvent */
        (NDR64_UINT32) 21626944 /* 0x14a0040 */,    /* explicit handle */ /* IsIntrepreted, ServerMustSize, HasReturn, ClientCorrelation, HasExtensions */
        (NDR64_UINT32) 32 /* 0x20 */ ,  /* Stack size */
        (NDR64_UINT32) 36 /* 0x24 */,
        (NDR64_UINT32) 8 /* 0x8 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 3 /* 0x3 */,
        (NDR64_UINT16) 8 /* 0x8 */
    },
    { 
    /* struct _NDR64_BIND_AND_NOTIFY_EXTENSION */
        { 
        /* struct _NDR64_BIND_AND_NOTIFY_EXTENSION */
            0x70,    /* FC64_BIND_CONTEXT */
            (NDR64_UINT8) 74 /* 0x4a */,
            8 /* 0x8 */,   /* Stack offset */
            (NDR64_UINT8) 0 /* 0x0 */,
            (NDR64_UINT8) 0 /* 0x0 */
        },
        (NDR64_UINT16) 0 /* 0x0 */      /* Notify index */
    },
    { 
    /* hContext */      /* parameter hContext */
        &__midl_frag21,
        { 
        /* hContext */
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [in] */
        (NDR64_UINT16) 0 /* 0x0 */,
        8 /* 0x8 */,   /* Stack offset */
    },
    { 
    /* pszResult */      /* parameter pszResult */
        &__midl_frag24,
        { 
        /* pszResult */
            1,
            1,
            0,
            0,
            1,
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* MustSize, MustFree, [out], SimpleRef */
        (NDR64_UINT16) 0 /* 0x0 */,
        16 /* 0x10 */,   /* Stack offset */
    },
    { 
    /* DWORD */      /* parameter DWORD */
        &__midl_frag25,
        { 
        /* DWORD */
            0,
            0,
            0,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [out], IsReturn, Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        24 /* 0x18 */,   /* Stack offset */
    }
};

static const __midl_frag18_t __midl_frag18 =
0x11    /* FC64_WCHAR */;

static const __midl_frag17_t __midl_frag17 =
{ 
/* struct _NDR64_CONTEXT_HANDLE_FORMAT */
    0x70,    /* FC64_BIND_CONTEXT */
    (NDR64_UINT8) 235 /* 0xeb */,
    (NDR64_UINT8) 0 /* 0x0 */,
    (NDR64_UINT8) 0 /* 0x0 */
};

static const __midl_frag16_t __midl_frag16 =
{ 
/* *struct _NDR64_POINTER_FORMAT */
    0x20,    /* FC64_RP */
    (NDR64_UINT8) 4 /* 0x4 */,
    (NDR64_UINT16) 0 /* 0x0 */,
    &__midl_frag17
};

static const __midl_frag15_t __midl_frag15 =
{ 
/* RpcCancelSubscription */
    { 
    /* RpcCancelSubscription */      /* procedure RpcCancelSubscription */
        (NDR64_UINT32) 17301568 /* 0x1080040 */,    /* explicit handle */ /* IsIntrepreted, HasReturn, HasExtensions */
        (NDR64_UINT32) 24 /* 0x18 */ ,  /* Stack size */
        (NDR64_UINT32) 66 /* 0x42 */,
        (NDR64_UINT32) 68 /* 0x44 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 3 /* 0x3 */,
        (NDR64_UINT16) 8 /* 0x8 */
    },
    { 
    /* struct _NDR64_BIND_AND_NOTIFY_EXTENSION */
        { 
        /* struct _NDR64_BIND_AND_NOTIFY_EXTENSION */
            0x70,    /* FC64_BIND_CONTEXT */
            (NDR64_UINT8) 234 /* 0xea */,
            0 /* 0x0 */,   /* Stack offset */
            (NDR64_UINT8) 0 /* 0x0 */,
            (NDR64_UINT8) 0 /* 0x0 */
        },
        (NDR64_UINT16) 0 /* 0x0 */      /* Notify index */
    },
    { 
    /* phContext */      /* parameter phContext */
        &__midl_frag17,
        { 
        /* phContext */
            0,
            0,
            0,
            1,
            1,
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [in], [out], SimpleRef */
        (NDR64_UINT16) 0 /* 0x0 */,
        0 /* 0x0 */,   /* Stack offset */
    },
    { 
    /* chToCancel */      /* parameter chToCancel */
        &__midl_frag18,
        { 
        /* chToCancel */
            0,
            0,
            0,
            1,
            0,
            0,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [in], Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        8 /* 0x8 */,   /* Stack offset */
    },
    { 
    /* DWORD */      /* parameter DWORD */
        &__midl_frag25,
        { 
        /* DWORD */
            0,
            0,
            0,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [out], IsReturn, Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        16 /* 0x10 */,   /* Stack offset */
    }
};

static const __midl_frag6_t __midl_frag6 =
{ 
/* RpcCloseSession */
    { 
    /* RpcCloseSession */      /* procedure RpcCloseSession */
        (NDR64_UINT32) 17301568 /* 0x1080040 */,    /* explicit handle */ /* IsIntrepreted, HasReturn, HasExtensions */
        (NDR64_UINT32) 16 /* 0x10 */ ,  /* Stack size */
        (NDR64_UINT32) 60 /* 0x3c */,
        (NDR64_UINT32) 68 /* 0x44 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 2 /* 0x2 */,
        (NDR64_UINT16) 8 /* 0x8 */
    },
    { 
    /* struct _NDR64_BIND_AND_NOTIFY_EXTENSION */
        { 
        /* struct _NDR64_BIND_AND_NOTIFY_EXTENSION */
            0x70,    /* FC64_BIND_CONTEXT */
            (NDR64_UINT8) 234 /* 0xea */,
            0 /* 0x0 */,   /* Stack offset */
            (NDR64_UINT8) 0 /* 0x0 */,
            (NDR64_UINT8) 0 /* 0x0 */
        },
        (NDR64_UINT16) 0 /* 0x0 */      /* Notify index */
    },
    { 
    /* phContext */      /* parameter phContext */
        &__midl_frag17,
        { 
        /* phContext */
            0,
            0,
            0,
            1,
            1,
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [in], [out], SimpleRef */
        (NDR64_UINT16) 0 /* 0x0 */,
        0 /* 0x0 */,   /* Stack offset */
    },
    { 
    /* DWORD */      /* parameter DWORD */
        &__midl_frag25,
        { 
        /* DWORD */
            0,
            0,
            0,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [out], IsReturn, Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        8 /* 0x8 */,   /* Stack offset */
    }
};

static const __midl_frag4_t __midl_frag4 =
{ 
/* struct _NDR64_CONTEXT_HANDLE_FORMAT */
    0x70,    /* FC64_BIND_CONTEXT */
    (NDR64_UINT8) 170 /* 0xaa */,
    (NDR64_UINT8) 0 /* 0x0 */,
    (NDR64_UINT8) 0 /* 0x0 */
};

static const __midl_frag3_t __midl_frag3 =
{ 
/* *struct _NDR64_POINTER_FORMAT */
    0x20,    /* FC64_RP */
    (NDR64_UINT8) 4 /* 0x4 */,
    (NDR64_UINT16) 0 /* 0x0 */,
    &__midl_frag4
};

static const __midl_frag2_t __midl_frag2 =
{ 
/* RpcOpenSession */
    { 
    /* RpcOpenSession */      /* procedure RpcOpenSession */
        (NDR64_UINT32) 17301568 /* 0x1080040 */,    /* explicit handle */ /* IsIntrepreted, HasReturn, HasExtensions */
        (NDR64_UINT32) 24 /* 0x18 */ ,  /* Stack size */
        (NDR64_UINT32) 0 /* 0x0 */,
        (NDR64_UINT32) 68 /* 0x44 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 2 /* 0x2 */,
        (NDR64_UINT16) 8 /* 0x8 */
    },
    { 
    /* struct _NDR64_BIND_AND_NOTIFY_EXTENSION */
        { 
        /* struct _NDR64_BIND_AND_NOTIFY_EXTENSION */
            0x72,    /* FC64_BIND_PRIMITIVE */
            (NDR64_UINT8) 0 /* 0x0 */,
            0 /* 0x0 */,   /* Stack offset */
            (NDR64_UINT8) 0 /* 0x0 */,
            (NDR64_UINT8) 0 /* 0x0 */
        },
        (NDR64_UINT16) 0 /* 0x0 */      /* Notify index */
    },
    { 
    /* phContext */      /* parameter phContext */
        &__midl_frag4,
        { 
        /* phContext */
            0,
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [out], SimpleRef */
        (NDR64_UINT16) 0 /* 0x0 */,
        8 /* 0x8 */,   /* Stack offset */
    },
    { 
    /* DWORD */      /* parameter DWORD */
        &__midl_frag25,
        { 
        /* DWORD */
            0,
            0,
            0,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [out], IsReturn, Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        16 /* 0x10 */,   /* Stack offset */
    }
};

static const __midl_frag1_t __midl_frag1 =
(NDR64_UINT32) 0 /* 0x0 */;


#include "poppack.h"


static const FormatInfoRef AsyncNotifications_Ndr64ProcTable[] =
    {
    &__midl_frag2,
    &__midl_frag6,
    &__midl_frag15,
    &__midl_frag15,
    &__midl_frag20
    };


static const MIDL_STUB_DESC AsyncNotifications_StubDesc = 
    {
    (void *)& AsyncNotifications___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &AsyncNotifications__MIDL_AutoBindHandle,
    0,
    0,
    0,
    0,
    AsyncNotificationsInterface__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x801026e, /* MIDL Version 8.1.622 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x2000001, /* MIDL flag */
    0, /* cs routines */
    (void *)& AsyncNotifications_ProxyInfo,   /* proxy/server info */
    0
    };

static const MIDL_SYNTAX_INFO AsyncNotifications_SyntaxInfo [  2 ] = 
    {
    {
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    AsyncNotificationsInterface__MIDL_ProcFormatString.Format,
    AsyncNotifications_FormatStringOffsetTable,
    AsyncNotificationsInterface__MIDL_TypeFormatString.Format,
    0,
    0,
    0
    }
    ,{
    {{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}},
    0,
    0 ,
    (unsigned short *) AsyncNotifications_Ndr64ProcTable,
    0,
    0,
    0,
    0
    }
    };

static const MIDL_STUBLESS_PROXY_INFO AsyncNotifications_ProxyInfo =
    {
    &AsyncNotifications_StubDesc,
    AsyncNotificationsInterface__MIDL_ProcFormatString.Format,
    AsyncNotifications_FormatStringOffsetTable,
    (RPC_SYNTAX_IDENTIFIER*)&_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)AsyncNotifications_SyntaxInfo
    
    };

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

