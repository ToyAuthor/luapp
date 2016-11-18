/**
 * @file   CallMultipleReturnValueFunctionFromLua.cpp
 * @brief  Show you how to call a global function of lua script.
 */


#include <cstdlib>
#include <iostream>
#include "luapp.hpp"


/* CallMultipleReturnValueFunctionFromLua.lua
-----------------------------------------------------

function func(a,b,c)
	local   x,y,z=c,b,a
--	local   x=c,y=b,z=a    It's not allow in lua.
	return x,y,z
end

-----------------------------------------------------
*/


int main()
{
	using lua::Int;
	using lua::Str;
	using lua::Num;

	lua::State<>    lua;

	lua.run(LUAPP_SCRIPT_PATH,"CallMultipleReturnValueFunctionFromLua.lua");

	lua::FunctionExt<void(Str,Num,Int),void(Int,Num,Str)>   func;

	lua.getFunc("func",&func);

	Str   x;
	Num   y;
	Int   z;

	Int   a = 3;
	Num   b = 0.5;
	Str   c = "hello";

	func( &x, &y, &z, a, b, c );

	std::cout << "Return values:" << std::endl;
	std::cout << "x=" << x << std::endl;
	std::cout << "y=" << y << std::endl;
	std::cout << "z=" << z << std::endl;

	return EXIT_SUCCESS;
}
