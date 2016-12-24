/**
 * @file   MakeFunctor.cpp
 * @brief  Make lua::Func by C/C++ function.
 */


#include <cstdlib>
#include <iostream>
#include "luapp.hpp"


/* MakeFunctor.lua
-----------------------------------------------------

PrintAgain = function ( func1, func2 )
	print(func1("sss","ttt"))
	func2(5.6)
end

-----------------------------------------------------
*/


#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
//------------------------------------------------------------------------------

class MyClass
{
	public:

		MyClass():id(100.0){}
		~MyClass(){}

		// It's func2
		void print(lua::Num num)
		{
			std::cout<< id+num <<std::endl;
		}

		lua::Num   id;
};

// It's func1
static lua::Str MyStrcat(lua::Str a,lua::Str b)
{
	return a+b;
}

//------------------------------------------------------------------------------

template<typename F1,typename F2>
static void PrintSample(F1 func1,F2 func2)
{
	std::cout<<"-----------------------"<<std::endl;
	std::cout<< func1("sss","ttt") <<std::endl;
	func2(5.6);
}

template<typename F1,typename F2>
static void PrintSample(lua::State<> *lua,const char* name,F1 func1,F2 func2)
{
	std::cout<<"-----------------------"<<std::endl;
	lua->call(name,func1,func2);
}

//------------------------------------------------------------------------------

int main()
{
	MyClass   obj;

	lua::State<>    lua;

	lua::Function<lua::Str(lua::Str,lua::Str)>   func1 = lua.bind(&MyStrcat);
	lua::Function<void(lua::Num)>                func2 = lua.bind(&MyClass::print,&obj);

	lua.run(LUAPP_SCRIPT_PATH,"MakeFunctor.lua");

	PrintSample(func1,func2);                       // Call them at C++ side.
	PrintSample(&lua,"PrintAgain",func1,func2);     // Call them at lua side.

	return EXIT_SUCCESS;
}

#else

int main()
{
	std::cout<<"Define _LUAPP_KEEP_LOCAL_LUA_VARIABLE_ to show this demo"<<std::endl;
	return EXIT_SUCCESS;
}

#endif
