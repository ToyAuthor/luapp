/**
@file   CallMultipleReturnValueFunctionFromLua.cpp
@brief  Show you how to call a global function of lua script.
*/


#include <cstdio>
#include <cstdlib>
#include "luapp.hpp"


/* CallMultipleReturnValueFunctionFromLua.lua
-----------------------------------------------------

function func()
	local   x,y,z=1,2,3
--	local   x=1,y=2,z=3    It's not allow in lua.
	return x,y,z
end

-----------------------------------------------------
*/


int main()
{
	using lua::Int;

	lua::State<>    lua;

	lua.Init();

	lua.AddMainPath(LUAPP_SCRIPT_PATH);

	lua.DoScript("CallMultipleReturnValueFunctionFromLua.lua");

	lua::FunctionExt<void(Int,Int,Int),void(void)>   func;

	lua.GetFunction("func",&func);

	int   x,y,z;

	func(&x,&y,&z);

	printf("Return values:\n");
	printf("x=%d\n",x);
	printf("y=%d\n",y);
	printf("z=%d\n",z);

	return EXIT_SUCCESS;
}
