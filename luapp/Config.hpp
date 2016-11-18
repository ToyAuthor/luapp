#pragma once


//#define _LUAPP_USING_BOOST_


// if ( it's C++11 )
#if __cplusplus > 201100L

	#define _LUAPP_CPP11_
//	#define _LUAPP_USING_CPP11_     // Optional

#endif


// Check data type before copy variable from lua.
#define _LUAPP_CHECK_DATA_TYPE_

// Spend more time to make sure everything was fine.
#define _LUAPP_CHECK_CAREFUL_

#include "luapp/Log.hpp"
