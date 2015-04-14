/**
@file   MemberFunctionIntoLua.cpp
@brief  Put a member function into lua.
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

		lua::Int Count2( lua::Str num01)
		{
			printf("do MyClass::Count2()=%s\n",num01.c_str());
			return 30;
		}

		lua::Int Count( lua::Int num01,
		                lua::Num num02,
		                lua::Num num03,
		                lua::Str num04,
		                lua::Str num05)
		{
			printf("do MyClass::Count() start\n");

			printf("param2+param3=%f\n",num02+num03);
			printf("param4+param5=%s\n",(num04+num05).c_str());

			printf("do MyClass::Count() end\n");
			return num01+1;
		}
};

int main()
{
	MyClass    myClass;

	lua::State<>    lua;

	lua.Init();

	lua.RegisterFunction("PrintMyWord",&MyClass::Count2,&myClass);

	lua.DoScript("../script/MemberFunctionIntoLua.lua");

	return EXIT_SUCCESS;
}
