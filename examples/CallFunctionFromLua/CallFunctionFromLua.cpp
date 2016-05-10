/**
@file   CallFunctionFromLua.cpp
@brief  Show you how to call a global function of lua script.
*/


#include <cstdio>
#include <cstdlib>
#include "luapp.hpp"


/* CallFunctionFromLua.lua
-----------------------------------------------------

function func(a, b, c)
	local   x=a+b+c
	print( a .. "+" .. b .. "+" .. c .. "=" .. x)
	return x
end

-----------------------------------------------------
*/


int main()
{
	using lua::Int;

	lua::State<>    lua;

	lua.Init();

	lua.AddMainPath(LUAPP_SCRIPT_PATH);

	lua.DoScript("CallFunctionFromLua.lua");

	lua::Function<Int(Int,Int,Int)>   func;

	lua.GetFunction("func",&func);

	printf("Return value is %d\n",func(1,2,3));

	return EXIT_SUCCESS;
}
