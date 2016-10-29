/**
@file   SetGlobalVariable.cpp
@brief  Show you how to set global variable to lua.
*/


#include <cstdlib>
#include <iostream>
#include "luapp.hpp"


/* SetGlobalVariable.lua
-----------------------------------------------------

local function PrintGlobalTable(t)
	...
end

print("cpp_number = " .. _G.cpp_number)

PrintGlobalTable("cpp_table")

-----------------------------------------------------
*/

int main()
{
	lua::State<>    lua;

	lua.Init();

	lua.AddMainPath(LUAPP_SCRIPT_PATH);

	{
		lua::Int     number = 100;

		lua.SetGlobal("cpp_number",number);
	}

	{
		lua::Table   table;

		table["tool"] = 300;
		table[3.1415] = "pi";
		table[123]["A"] = true;
		table[123]["B"] = false;

		lua.SetGlobal("cpp_table",table);
	}

	lua.DoScript("SetGlobalVariable.lua");

	return EXIT_SUCCESS;
}
