#pragma once


//#define _LUAPP_USING_BOOST_

#include "luapp/Environment.hpp"

// if ( version >= C++11 )
#if (__cplusplus > 201100L) || defined(TOY_VC_2013)

	#define _LUAPP_CPP11_
//	#define _LUAPP_USING_CPP11_     // Optional

#endif


// Check data type before copy variable from lua.
#define _LUAPP_CHECK_DATA_TYPE_

// Spend more time to make sure everything was fine.
#define _LUAPP_CHECK_CAREFUL_

// You can keep lua variable at C++ side, but it make luapp slow down.
#define _LUAPP_KEEP_LOCAL_LUA_VARIABLE_

// Release shared pointer when lua::State deconstruction. It make luapp slow down.
#define _LUAPP_CLEAN_LUA_HANDLE_


#include "luapp/Log.hpp"
