/**
@file   HelloWorld.cpp
@brief  Print a message from lua script.
*/


#include <cstdlib>
#include <iostream>
#include "luapp.hpp"


/* simple.lua
-----------------------------------------------------

print("Hello lua")

-----------------------------------------------------
*/


int main()
{
	lua::State<>    lua;

	if( ! lua.run(LUAPP_SCRIPT_PATH,"simple.lua") )
	{
		std::cout<<lua.error()<<std::endl;
	}

	return EXIT_SUCCESS;
}
