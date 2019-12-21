#include "../AsyncNotifications/AsyncNotificationsInterface_h.h"

// ----------------------------------------------------------------------
// Utility functions necessary for MS RPC
// 

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