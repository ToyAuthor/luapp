/**
 * @file   LoadScriptFromBuffer.cpp
 * @brief  Load the lua script from std::string.
 */

#include <cstdlib>
#include <iostream>
#include "luapp.hpp"


// Include GetSubFileScript() and GetMainFileScript()
#if __cplusplus > 201100L
	#include "script_cpp11.hpp"
#else
	#include "script.hpp"
#endif


static lua::Str   SubFileScript;
static lua::Str   MainFileScript;

inline void SetScript()
{
	SubFileScript = GetSubFileScript();
	MainFileScript = GetMainFileScript();
}

// MainFileScript use it to find out SubFileScript.
static lua::Str& MySearcher(lua::Str name)
{
	static lua::Str   result;

	if ( name=="ssd.subfile" )
	{
		return SubFileScript;
	}

	return result;
}

class MyClass
{
	public:

		MyClass(){}
		~MyClass(){}

		lua::Int add(lua::Int a,lua::Int b,lua::Int c)
		{
			std::cout<<a<<","<<b<<","<<c<<std::endl;
			return a+b+c;
		}
};

int main()
{
	SetScript();

	lua::State<>    lua;

	lua.bindMethod("add",&MyClass::add);
	lua.bindClassEx<MyClass>("NewClass");

	/*
	lua.searcher(MySearcher);
	lua.run(MainFileScript);
	*/

	/*
	lua.searcher(MySearcher);
	lua.load("main", MainFileScript);
	lua.run();
	*/

	lua.run( "main", MainFileScript, MySearcher );

	return EXIT_SUCCESS;
}
