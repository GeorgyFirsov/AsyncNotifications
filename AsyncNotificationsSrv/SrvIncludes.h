#pragma once

// ----------------------------------------------------------------------
// This file is necessary in case of impossibility to use precompiled
// headers file. It is impossible, because automatically generated 
// by MIDL files does not include precompiled headers header and
// it breaks the build process
// 

//
// Disable some rarely used stuff in Windows' headers
// 
#define WIN32_LEAN_AND_MEAN

// Windows header files
#include <Windows.h>

// STL header files
#include <iostream>
#include <map>
#include <set>
#include <mutex>

// Project header files
#include "../Common/Utils.h"
#include "../Common/Trace.h"
#include "../AsyncNotifications/AsyncNotificationsInterface_h.h"

// ----------------------------------------------------------------------
// Project settings
// 
DECLARE_DEBUG_LEVEL( DL_ALL );