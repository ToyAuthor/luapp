/**
 * @file   MultipleLuaFile.cpp
 * @brief  Show you how to use multiple lua files.
 */


#include <cstdlib>
#include "luapp.hpp"


/* MultipleLuaFile.lua
-----------------------------------------------------

local std = require "std"

function func(a, b, c)
	local   x=std.sum(a,b,c)
	print( a .. "+" .. b .. "+" .. c .. "=" .. x)
	return x
end

-----------------------------------------------------
*/


int main()
{
	using lua::Int;

	lua::State<>    lua;

	lua.run(LUAPP_SCRIPT_PATH,"MultipleLuaFile.lua");

	lua::GlobalFunction<Int(Int,Int,Int)>   func;

	lua.getFunc("func",&func);

	lua::Log<<"Return value is "<<func(1,2,3)<<lua::End;

	return EXIT_SUCCESS;
}
