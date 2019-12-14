#pragma once

#include <iomanip>

#define as_hex( _num, _width ) \
	std::hex << std::setw( (_width) ) << std::setfill( L'0' ) << (_num)


//
// Encapsulates an information about client
// 
class CContextHandle
{
	// Empty for now
};