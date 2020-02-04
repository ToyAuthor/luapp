
#pragma once

namespace lua{

typedef void* NativeState;                // NativeState == (lua_State*)
typedef int (*CFunction) (NativeState);   // lua::CFunction as lua_CFunction.
typedef const char* Name;

}
