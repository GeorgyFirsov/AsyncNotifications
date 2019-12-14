#pragma once

#include <iomanip>


#define as_hex( _num, _width ) \
	std::hex << std::setw( (_width) ) << std::setfill( L'0' ) << (_num)


// ------------------------------------------------------------
// Class: CContextHandle
// Description: encapsulates client-specific information.
//              context_handle_t will be casted to CContextHandle*
// ------------------------------------------------------------
// Parameters (for constructors):
// 
// Comments: 
//       
// ------------------------------------------------------------
// Author: Georgy Firsov
// Date: 
// ------------------------------------------------------------
//
class CContextHandle
{
	// Empty for now
};