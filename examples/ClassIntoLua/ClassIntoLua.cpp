/**
@file   ClassIntoLua.cpp
@brief  Show you how to new a C++ object in lua script.
*/


#include <cstdio>
#include <cstdlib>
#include "luapp.hpp"


/* ClassIntoLua.lua
-----------------------------------------------------

object = MyClass()

param = 6

num = object:Count(param)

print("Answer is " .. param .. "+1 = " .. num)

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

		lua::Int Count(lua::Int num)
		{
			printf("do MyClass::Count()\n");
			return num+1;
		}
};

int main()
{
	lua::State    lua;

	lua.Init();

	lua.RegisterClass<MyClass>("MyClass");                 // Lua script has class now.

	lua.RegisterMemberFunction("Count",&MyClass::Count);   // Lua script has member function now.

	lua.DoScript("../script/ClassIntoLua.lua");

	return EXIT_SUCCESS;
}
