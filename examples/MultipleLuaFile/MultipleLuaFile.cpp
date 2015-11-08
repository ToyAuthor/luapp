/**
@file   MultipleLuaFile.cpp
@brief  Show you how to use multiple lua files.
*/


#include <cstdio>
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

	lua.Init();

	lua.AddMainPath("../script");// Add the path of "std.lua" file.

	lua.DoScript("MultipleLuaFile.lua");

	lua::Function<Int(Int,Int,Int)>   func;

	lua.GetFunction("func",&func);

	printf("Return value is %d\n",func(1,2,3));

	return EXIT_SUCCESS;
}
