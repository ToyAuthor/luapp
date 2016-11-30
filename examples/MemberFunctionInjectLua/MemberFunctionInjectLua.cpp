/**
 * @file   MemberFunctionIntoLua.cpp
 * @brief  Put a member function into lua.
 */


#include <cstdio>
#include <cstdlib>
#include "luapp.hpp"


/* MemberFunctionIntoLua.lua
-----------------------------------------------------

print("Member function Into Lua")

num = PrintMyWord("good")

print("Return value is " .. num)

-----------------------------------------------------
*/


class MyClass
{
	public:

		MyClass()
		{
			printf("do MyClass::MyClass()\n");
		}

		~MyClass()
		{
			printf("do MyClass::~MyClass()\n");
		}

		lua::Int print( lua::Str str)
		{
			printf("do MyClass::print()=%s\n",str.c_str());
			return 30;
		}
};

int main()
{
	MyClass    myClass;

	lua::State<>    lua;

	lua.setFunc("PrintMyWord",&MyClass::print,&myClass);

	lua.run(LUAPP_SCRIPT_PATH,"MemberFunctionIntoLua.lua");

	return EXIT_SUCCESS;
}
