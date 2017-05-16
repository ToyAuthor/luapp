
#pragma once

#include <typeinfo>
#include "luapp/DataType.hpp"

namespace lua{

template<typename T>
inline lua::Str _CreateUserTypeName(lua::Str name)
{
	name += typeid(T).name();

	return name;
}

template<typename T>
inline lua::Str CreateUserType()
{
	return lua::_CreateUserTypeName<T>("_luapp_user_type_");
}

}//namespace lua
