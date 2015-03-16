#include "Lua.hpp"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}



namespace lua{


Handle CreateHandle()
{
	return (Handle)luaL_newstate();
}
void DestroyHandle(Handle handle)
{
	lua_close((lua_State*)handle);
}
int PCall(Handle handle,int num01,int num02,int num03)
{
	return lua_pcall((lua_State*)handle,num01,num02,num03);
}
void OpenLibs(Handle handle)
{
	luaL_openlibs((lua_State*)handle);
}
int DoScript(Handle handle,const char *filename)
{
	luaL_loadfile((lua_State*)handle,filename);
	lua_pcall((lua_State*)handle,0,0,0);
//	lua_settop((lua_State*)handle, 0);    // May be I don't need this.
	return 0;
}
void NewTable(Handle handle)
{
	lua_newtable((lua_State*)handle);
}
int NewMetaTable(Handle handle,const char *tname)
{
	return luaL_newmetatable((lua_State*)handle,tname);
}
void* NewUserData(Handle handle,size_t size)
{
	return lua_newuserdata((lua_State*)handle,size);
}
void SetGlobal(Handle handle,const char *var)
{
	lua_setglobal((lua_State*)handle,var);
}
void GetGlobal(Handle handle,const char *var)
{
	lua_getglobal((lua_State*)handle,var);
}
void SetTable(Handle handle,int index)
{
	lua_settable((lua_State*)handle,index);
}
void GetTable(Handle handle,int index)
{
	lua_gettable((lua_State*)handle,index);
}
void GetField(Handle handle,int index, const char *k)
{
	lua_getfield ((lua_State*)handle,index,k);
}
int SetMetaTable(Handle handle,int index)
{
	return lua_setmetatable((lua_State*)handle,index);
}
void GetMetaTable(Handle handle,const char *name)
{
	luaL_getmetatable((lua_State*)handle,name);
}
void PushClosure(Handle handle,CFunction fn,int n)
{
	lua_pushcclosure((lua_State*)handle, (lua_CFunction)fn, n);
}
void PushFunction(Handle handle,CFunction fn)
{
	lua_pushcfunction((lua_State*)handle,(lua_CFunction)fn);
}
const char* PushString(Handle handle,const char *str)
{
	return lua_pushstring((lua_State*)handle, str);
}
const char* PushString(Handle handle,Str str)
{
	return lua_pushstring((lua_State*)handle, str.c_str());
}
void PushValue(Handle handle,int index)
{
	lua_pushvalue((lua_State*)handle,index);
}
void PushNumber(Handle handle,double n)
{
	lua_pushnumber((lua_State*)handle,n);
}
void PushInteger(Handle handle,int num)
{
	lua_pushinteger((lua_State*)handle,num);
}
double CheckNumber(Handle handle,int index)
{
	return luaL_checknumber((lua_State*)handle,index);
}
int CheckInteger(Handle handle,int index)
{
	return (int)luaL_checkinteger((lua_State*)handle,index);
}
Str CheckString(Handle handle,int index)
{
	return Str(luaL_checkstring((lua_State*)handle,index));
}
void* CheckUserData(Handle handle,int ud, const char *tname)
{
	return luaL_checkudata((lua_State*)handle, ud, tname);
}
double ToNumber(Handle handle,int index)
{
	return lua_tonumber((lua_State*)handle,index);
}
int UpValueIndex(int index)
{
	return lua_upvalueindex(index);
}
void Pop(Handle handle,int num)
{
	lua_pop((lua_State*)handle,num);
}
void SetTop(Handle handle,int num)
{
	lua_settop((lua_State*)handle,num);
}
int GetTop(Handle handle)
{
	return lua_gettop((lua_State*)handle);
}

/*
void Remove(Handle handle,int index)
{
	lua_remove((lua_State*)handle, index);
}
*/

}//namespace lua
