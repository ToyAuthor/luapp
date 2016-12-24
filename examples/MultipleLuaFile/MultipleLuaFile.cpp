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

print("Return value is " .. func(1,2,3))

-----------------------------------------------------
*/


int main()
{
	lua::State<>    lua;

	lua.run(LUAPP_SCRIPT_PATH,"MultipleLuaFile.lua");

	return EXIT_SUCCESS;
}
