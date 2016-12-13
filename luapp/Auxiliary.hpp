
#pragma once

#include "luapp/State.hpp"

namespace lua{

template<typename T,typename A>
void CopyVar(A &target,const lua::Var &data)
{
	if ( lua::VarType<T>(data) )
	{
		target = lua::VarCast<T>(data);
	}
}

}//namespace lua
