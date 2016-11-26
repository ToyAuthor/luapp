
#pragma once

#include "lua.hpp"

namespace lua{

typedef lua_State* Handle;
typedef int (*CFunction) (Handle);   // lua::CFunction as lua_CFunction.
typedef const char* Name;

}
