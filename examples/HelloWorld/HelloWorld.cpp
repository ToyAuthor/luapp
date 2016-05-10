/**
@file   HelloWorld.cpp
@brief  Print a message from lua script.
*/


#include <cstdlib>
#include "luapp.hpp"


/* simple.lua
-----------------------------------------------------

print("Hello lua")

-----------------------------------------------------
*/


int main()
{
	lua::State<>    lua;

	lua.Init();
	lua.AddMainPath(LUAPP_SCRIPT_PATH);
	lua.DoScript("simple.lua");

	return EXIT_SUCCESS;
}
