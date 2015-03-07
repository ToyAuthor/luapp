/**
@file   Lua.hpp
@brief  It's just a wrapper of lua.
*/

#ifndef _LUA_HPP_
#define _LUA_HPP_


#include <cstdlib>
#include <vector>
#include <string>



namespace lua{

/*
Those date type have worked in luapp.
You can't use the other date type to work with luapp.
*/
typedef double          Num;
//typedef int             Bool;   Do I need it?
typedef int             Int;
typedef std::string     Str;



typedef void* Handle;               // lua::Handle as lua_State*
typedef int (*CFunction) (void*);   // lua::CFunction as lua_CFunction
typedef const char* Name;


Handle  CreateHandle();
void    DestroyHandle(Handle);

void    OpenLibs(     Handle);
int     DoScript(     Handle,Name filename);
void    NewTable(     Handle);
int     NewMetaTable( Handle,Name tname);
void*   NewUserData(  Handle,size_t size);
void    SetGlobal(    Handle,Name var);
void    GetGlobal(    Handle,Name var);
void    SetTable(     Handle,int index);
void    GetTable(     Handle,int index);
void    GetField(     Handle,int index, Name k);
int     SetMetaTable( Handle,int index);
void    GetMetaTable( Handle,Name name);
void    PushClosure(  Handle,CFunction fn,int n);
void    PushFunction( Handle,CFunction fn);
Name    PushString(   Handle,Name s);
Name    PushString(   Handle,Str s);
void    PushValue(    Handle,int index);
void    PushNumber(   Handle,double n);
void    PushInteger(  Handle,int num);
double  CheckNumber(  Handle,int index);
int     CheckInteger( Handle,int index);
Str     CheckString(  Handle,int index);
void*   CheckUserData(Handle,int ud, Name tname);
double  ToNumber(     Handle,int index);
int     UpValueIndex(        int index);
void    Pop(          Handle,int num);
void    SetTop(       Handle,int num);
int     GetTop(       Handle);

/*
void    Remove(       Handle,int index);             // It's doesn't work in lua v5.3.0 on Windows.
*/

}//namespace lua

#endif//_LUA_HPP_
