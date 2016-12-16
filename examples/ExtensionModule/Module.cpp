/*
 * To show this example.
 * You need to put the following stuff into same directory.
 *
 * luainterpreter.exe
 * lua.dll
 * module.dll
 * ExtensionModule.lua
 *
 * Then type "luainterpreter.exe -i ExtensionModule.lua" to show it.
 * Then type "os.exit()" to close it.
 */


#include "luapp.hpp"



/* ExtensionModule.lua
-----------------------------------------------------
local t = require ("module")

local a = 1
local b = 2

print(a .. "+" .. b .. "=" .. t.count(a,b))

local obj = t.NewObject()
print("Message frome C++: " .. obj:name())
-----------------------------------------------------
*/

class MyClass
{
	public:

		MyClass(){}
		~MyClass(){}

		lua::Str name()
		{
			return lua::Str("It is MyClass");
		}
};

static int func_count(lua::NativeState L)
{
	lua::Int a;
	lua::Int b;
	lua::CheckVarFromLua(L,&a,1);
	lua::CheckVarFromLua(L,&b,2);
	lua::Pop(L,2);

//--------------------------------
//	int count(int a,int b)
//	{
		lua::Int c = a + b;
//		return c;
//	}
//--------------------------------

	lua::PushVarToLua(L,c);
	return 1;
}


#if defined(_WIN32)
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_module(lua::NativeState L)
{
	lua::State<>    lua(L);

	lua.setFunc("count",func_count);

	lua.bindMethod("name",&MyClass::name);
	lua.bindClassEx<MyClass>("NewObject");

	return 1;
}
