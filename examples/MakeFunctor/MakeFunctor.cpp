/**
 * @file   MakeFunctor.cpp
 * @brief  Make lua::Func by C/C++ function.
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "luapp.hpp"


/* MakeFunctor.lua
-----------------------------------------------------

PrintAgain = function ( cat, pri )
	print(cat("sss","ttt"))
	pri(5.6)
end

-----------------------------------------------------
*/

class MyClass
{
	public:

		MyClass():id(100.0f){}
		~MyClass(){}

		void print(lua::Num num)
		{
			lua::Log<< id+num <<lua::End;
		}

		lua::Num   id;
};

static lua::Str MyStrcat(lua::Str a,lua::Str b)
{
	return a+b;
}

#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_

int main()
{
	MyClass   obj;

	lua::State<>    lua;

	lua::Closure<lua::Str(lua::Str,lua::Str)>   cat = lua.bind(&MyStrcat);
	lua::Closure<void(lua::Num)>                pri = lua.bind(&MyClass::print,&obj);

	lua.run(LUAPP_SCRIPT_PATH,"MakeFunctor.lua");

	lua::Log<<"-----------------------"<<lua::End;
	lua::Log<< cat("sss","ttt") <<lua::End;
	pri(5.6f);
	lua::Log<<"-----------------------"<<lua::End;
	lua.call("PrintAgain",cat,pri);
	lua::Log<<"-----------------------"<<lua::End;

	return EXIT_SUCCESS;
}

#else

int main()
{
	lua::Log<<"Define _LUAPP_KEEP_LOCAL_LUA_VARIABLE_ to show this demo"<<lua::End;
	return EXIT_SUCCESS;
}

#endif
