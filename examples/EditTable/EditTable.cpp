/**
 * @file   EditTable.cpp
 * @brief  Show you how to use my table helping library.
 */


#include <cstdlib>
#include "luapp.hpp"


/* EditTable.lua
-----------------------------------------------------

local tab =
{
	andy = 45,
	ss = "dd"
}

_G.GetTable = function()
	return tab
end

_G.SetTable = function(t)
	tab = t
end

function PrintMyAnswer()
	_G.PrintGlobalTable("table",tab)
end

-----------------------------------------------------
*/

static void ModifyTable(lua::Table &tab)
{
	tab["happy"] = 100;
//	tab["ff"][13][15] = "ddff";
}

template<typename F1,typename F2>
void ModifyTable(F1 getTable, F2 setTable)
{
	lua::Table  tab = getTable();
	ModifyTable(tab);
	setTable(tab);
}

int main()
{
	lua::State<>    lua;

	lua.run(LUAPP_SCRIPT_PATH,"EditTable.lua");

	// Set a global lua function that could print lua table.
	if ( ! lua::SetPrintTableFunc(&lua,"PrintGlobalTable") )
	{
		return EXIT_FAILURE;
	}

	lua::GlobalFunction<lua::Table(void)>   getTable;
	lua::GlobalFunction<void(lua::Table)>   setTable;

	lua.getFunc("GetTable",&getTable);
	lua.getFunc("SetTable",&setTable);

	lua.call("PrintMyAnswer");       // Print the content of table.
	ModifyTable(getTable,setTable);  // Add a item to the table.
	lua.call("PrintMyAnswer");       // Print the content of table again.

	return EXIT_SUCCESS;
}
