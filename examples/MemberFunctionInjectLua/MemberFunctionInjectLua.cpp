/**
 * @file   MemberFunctionIntoLua.cpp
 * @brief  Put a member function into lua.
 */


#include <cstdlib>
#include <iostream>
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
			std::cout<<"do MyClass::MyClass()"<<std::endl;
		}

		~MyClass()
		{
			std::cout<<"do MyClass::~MyClass()"<<std::endl;
		}

		lua::Int print( lua::Str str)
		{
			std::cout<<"do MyClass::print()="<<str<<std::endl;
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
