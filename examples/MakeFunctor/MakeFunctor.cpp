/**
 * @file   MakeFunctor.cpp
 * @brief  Make lua::Func by C/C++ function.
 */


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

//------------------------------------------------------------------------------

class MyClass
{
	public:

		MyClass():id(100.0){}
		~MyClass(){}

		void print(lua::Num num)
		{
			std::cout<< id+num <<std::endl;
		}

		lua::Num   id;
};

static lua::Str MyStrcat(lua::Str a,lua::Str b)
{
	return a+b;
}

//------------------------------------------------------------------------------

template<typename F1,typename F2>
static void PrintSample(F1 cat,F2 pri)
{
	std::cout<<"-----------------------"<<std::endl;
	std::cout<< cat("sss","ttt") <<std::endl;
	pri(5.6);
}

template<typename F1,typename F2>
static void PrintSample(lua::State<> *lua,const char* name,F1 cat,F2 pri)
{
	std::cout<<"-----------------------"<<std::endl;
	lua->call(name,cat,pri);
}

//------------------------------------------------------------------------------

#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_

int main()
{
	MyClass   obj;

	lua::State<>    lua;

	lua::Function<lua::Str(lua::Str,lua::Str)>   cat = lua.bind(&MyStrcat);
	lua::Function<void(lua::Num)>                pri = lua.bind(&MyClass::print,&obj);

	lua.run(LUAPP_SCRIPT_PATH,"MakeFunctor.lua");

	PrintSample(cat,pri);                       // Call them at C++ side.
	PrintSample(&lua,"PrintAgain",cat,pri);     // Call them at lua side.

	return EXIT_SUCCESS;
}

#else

int main()
{
	std::cout<<"Define _LUAPP_KEEP_LOCAL_LUA_VARIABLE_ to show this demo"<<std::endl;
	return EXIT_SUCCESS;
}

#endif
