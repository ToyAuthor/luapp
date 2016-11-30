/**
 * @file   FunctionIntoLua.cpp
 * @brief  Show you how to call a C function in lua script.
 */


#include <cstdlib>
#include "luapp.hpp"


/* FunctionIntoLua.lua
-----------------------------------------------------

print("Function Into Lua")

param = 6

num = NumberPlus(param)

print("Answer is " .. param .. "+1 = " .. num)

-----------------------------------------------------
*/


lua::Int MyFunction(lua::Int num)
{
	return num+1;
}


int main()
{
	lua::State<>    lua;

	lua.setFunc("NumberPlus",&MyFunction);   // Lua script has MyFunction() now.

	lua.run(LUAPP_SCRIPT_PATH,"FunctionIntoLua.lua");

	return EXIT_SUCCESS;
}
