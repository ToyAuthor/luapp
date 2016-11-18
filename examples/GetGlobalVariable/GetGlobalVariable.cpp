/**
 * @file   GetGlobalVariable.cpp
 * @brief  Show you how to get global variable from lua script.
 */


#include <cstdlib>
#include <iostream>
#include "luapp.hpp"


/* GetGlobalVariable.lua
-----------------------------------------------------

lua_power = "on"

test_table=
{
	hello  = "abcd",
	[20]   = false,
	["15"] = 123,
--	[true] = "no",    Not support boolean index.
	sub =
	{
		[3.14] = "21",
		["3.14"] =
		{
			[6] =
			{
				["end"] = "stop"
			}
		},
		lua = true
	},
	pi = 3.14
}

-----------------------------------------------------
*/


inline void Print(lua::Str t)
{
	std::cout << t << std::endl;
}

void PrintTableItem(lua::Table &,int *);

int main()
{
	lua::State<>    lua;

	lua.run(LUAPP_SCRIPT_PATH,"GetGlobalVariable.lua");

	lua::Var   var;

	lua.getGlobal("lua_power",&var);

	if ( lua::VarType<lua::Str>(var) )   // Make sure it's a string.
	{
		lua::Str    power = lua::VarCast<lua::Str>(var);
		std::cout << "Power was turn " << power << std::endl;
	}

	Print("-------------------------------------------------------");

	lua.getGlobal("test_table",&var);

	if ( lua::VarType<lua::Table>(var) )   // Make sure it's a table.
	{
		lua::Table  table = lua::VarCast<lua::Table>(var);

		int  indentation = 1;
		Print("test_table =");
		Print("{");
		PrintTableItem(table,&indentation);
		Print("}");
	}

	return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------

const int IndentationSize = 4;

inline void Print(lua::Int t)
{
	std::cout << t << std::endl;
}

inline void Print(lua::Num t)
{
	std::cout << t << std::endl;
}

static bool PrintKey(lua::Var &key,int *indentation)
{
	int       indent = (*indentation) * IndentationSize;
	lua::Str  tab(indent,' ');

	if ( lua::VarType<lua::Str>(key) )
	{
		lua::Str  key_r = lua::VarCast<lua::Str>(key);
		std::cout << tab;
		std::cout << "\"" << key_r << "\" = ";
	}
	else if ( lua::VarType<lua::Int>(key) )
	{
		lua::Int  key_r = lua::VarCast<lua::Int>(key);
		std::cout << tab;
		std::cout << key_r << " = ";
	}
	else if ( lua::VarType<lua::Num>(key) )
	{
		lua::Num  key_r = lua::VarCast<lua::Num>(key);
		std::cout << tab;
		std::cout << key_r << " = ";
	}
	else if ( lua::VarType<lua::Bool>(key) )
	{
		lua::Bool key_r = lua::VarCast<lua::Bool>(key);
		std::cout << tab;

		if ( key_r )
		{
			std::cout << "true = ";
		}
		else
		{
			std::cout << "false = ";
		}
	}
	else
	{
		Print("The key is not a string");
		return true;
	}

	return false;
}

static void PrintValue(lua::Var &value)
{
	if ( lua::VarType<lua::Str>(value) )
	{
		lua::Str  value_t = lua::VarCast<lua::Str>(value);
		std::cout << "\"" << value_t << "\"" << std::endl;
	}
	else if ( lua::VarType<lua::Nil>(value) )
	{
		std::cout << std::endl;
	}
	else if ( lua::VarType<lua::Int>(value) )
	{
		lua::Int  value_t = lua::VarCast<lua::Int>(value);
		Print(value_t);
	}
	else if ( lua::VarType<lua::Num>(value) )
	{
		lua::Num  value_t = lua::VarCast<lua::Num>(value);
		Print(value_t);
	}
	else if ( lua::VarType<lua::Bool>(value) )
	{
		lua::Bool  value_t = lua::VarCast<lua::Bool>(value);
		if ( value_t )
		{
			Print("true");
		}
		else
		{
			Print("false");
		}
	}
	else if ( lua::VarType<lua::Ptr>(value) )
	{
		Print("pointer");
	}
	else
	{
		Print("unknow type");
	}
}

static void PrintTableKeyValue(lua::Var key,lua::Var value,int *indentation)
{
	if (PrintKey(key,indentation) )
	{
		return;
	}

	PrintValue(value);
}

void PrintTableItem(lua::Table &table,int *indentation)
{
	lua::Table::Iterator   it = table.getBegin();

	lua::Var   key;
	lua::Var   value;

	for ( ; ! it.isEnd() ; it++ )
	{
		it.getKeyValue(&key,&value);

		if ( lua::VarType<lua::Table>(value) )
		{
			PrintTableKeyValue(key,lua::Var(),indentation);

			int indent = (*indentation) * IndentationSize;
			lua::Str  tab(indent,' ');
			std::cout << tab;
			Print("{");

			lua::Table  table = lua::VarCast<lua::Table>(value);
			*indentation = *indentation + 1;
			PrintTableItem(table,indentation);
			*indentation = *indentation - 1;

			std::cout << tab;
			Print("}");
		}
		else
		{
			PrintTableKeyValue(key,value,indentation);
		}
	}
}
