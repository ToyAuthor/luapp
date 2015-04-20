/**
@file   CallFunctionFromLua.cpp
@brief  Show you how to call a global function from lua script.
*/


#include <cstdio>
#include <cstdlib>
#include "luapp.hpp"


/* CallFunctionFromLua.lua
-----------------------------------------------------

local std = require "std"

function func(a, b, c)

	print("script:func() start")
	print("script:a =", a)
	print("script:b =", b)
	print("script:c =", c)

	local   x=std.sum(a,b,c)

	print("script:x =", x)
	print("script:func() end")

	return x
end

-----------------------------------------------------
*/


int main()
{
	using lua::Int;

	lua::State<>    lua;

	lua.Init();

	lua.AddSearchPath("../script");

	lua.DoScript("CallFunctionFromLua.lua");

	lua::Function<Int(Int,Int,Int)>   func;

	lua.GetFunction("func",&func);

	printf("Return value is %d\n",func(1,2,3));

	return EXIT_SUCCESS;
}
