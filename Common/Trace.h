#pragma once

#include <thread>  // std::this_thread

#include "Utils.h"  // ThreadSafePrint

//
// Strings with message of functions failure
// 
#define FUNC_FAILURE_STR( _func ) L#_func L" failed. "
#define FUNC_FAILURE_STR_A( _func ) #_func " failed. "
#define FUNCTION_FAILED_WITH( _code ) __FUNCTIONW__ L"failed. Returning: ", _code 

//
// Macro used in TRACE to print current thread id
// 
#define TID L"[", std::this_thread::get_id(), L"] "

//
// TRACE macro for various printing
// 
#define TRACE_FUNC ThreadSafePrint( std::wcout, TID, __FUNCTIONW__ )
#define TRACE_LINE( line ) ThreadSafePrint( std::wcout, TID, __FUNCTIONW__ L": ", line )
#define TRACE_DATA( ... ) ThreadSafePrint( std::wcout, TID, __FUNCTIONW__ L": ", __VA_ARGS__ )

//
// Macro used to initialize compile-time value that represents debug level
// of whole project. Use only constants listed below!
// 
#define DECLARE_DEBUG_LEVEL( _level ) const DWORD __RESERVED_DEBUG_LEVEL = _level;

//
// Macro that prints some data in case of corresponding debug level.
// 
#define DEBUG_TRACE( _debug_level, ... ) DebugPrintImpl( _debug_level, __RESERVED_DEBUG_LEVEL, __FUNCTIONW__, __VA_ARGS__ )

template<typename... Ts>
void DebugPrintImpl( DWORD dwDebugLevel, DWORD dwProgramDebugLevel, LPCWSTR pszFuncName, Ts&&... Args )
{
    if (dwProgramDebugLevel >= dwDebugLevel) {
        ThreadSafePrint( std::wcout, TID, pszFuncName, L": ", std::forward<Ts>( Args )... );
    }
}

//
// Debug levels
// 
#define DL_NO_DEBUG ((DWORD)0)  // Only used to define debug level.

#define DL_CRITICAL ((DWORD)1)
#define DL_EXTENDED ((DWORD)2)
#define DL_ALL      ((DWORD)3)

//
// Misc utils
// 
#define TRACE_SEPARATOR L"\n"
#define ON_NEW_LINE L"\n", 

#define AS_PTR( _data ) ((void*)_data)
