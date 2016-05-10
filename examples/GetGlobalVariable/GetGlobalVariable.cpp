/**
@file   GetGlobalVariable.cpp
@brief  Show you how to get global variable from lua script.
*/


#include <cstdio>
#include <cstdlib>
#include "luapp.hpp"


/* GetGlobalVariable.lua
-----------------------------------------------------

lua_power="on"

-----------------------------------------------------
*/



int main()
{
	lua::State<>    lua;

	lua.Init();

	lua.AddMainPath(LUAPP_SCRIPT_PATH);

	lua.DoScript("GetGlobalVariable.lua");

	lua::Str   power;

	lua.GetGlobal("lua_power",&power);

	printf("Power was turn %s\n",power.c_str());

	return EXIT_SUCCESS;
}
