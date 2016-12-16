/**
 * @file   CallFunctionFromLua.cpp
 * @brief  Show you how to call a global function of lua script.
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

	lua.run(LUAPP_SCRIPT_PATH,"CallFunctionFromLua.lua");

	lua::Function<Int(Int,Int,Int)>   func;

	lua.getFunc("func",&func);

	lua::Log<<"Return value is "<<func(1,2,3)<<lua::End;

	return EXIT_SUCCESS;
}
