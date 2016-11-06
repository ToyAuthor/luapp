
#ifndef _LUAPP_SHORT_NAME_HPP_
#define _LUAPP_SHORT_NAME_HPP_

namespace lua{

typedef lua_State* Handle;
typedef int (*CFunction) (Handle);   // lua::CFunction as lua_CFunction.
typedef const char* Name;

}

#endif
