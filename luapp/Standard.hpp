/**
@file   Standard.hpp
@brief  It's just a wrapper of lua.
*/

#ifndef _LUAPP_STANDARD_HPP_
#define _LUAPP_STANDARD_HPP_



#include <vector>
#include <string>
#include "lua.hpp"


namespace lua{

/*
 * Only following date types could work in luapp.
 * You can't use the other date type to work with luapp.
 */
typedef double          Num;
typedef int             Int;
typedef std::string     Str;
typedef void*           Ptr;



typedef lua_State* Handle;
typedef int (*CFunction) (Handle);   // lua::CFunction as lua_CFunction.
typedef const char* Name;

// A function register for lua.
class FuncReg
{
	public:

		// lua::FunctionRegister::Item as luaL_Reg.
		struct Item
		{
			Item():name(NULL),func(NULL){}
			Name       name;
			CFunction  func;
		};

		FuncReg():mIndex(0),mSize(4),mData(0)
		{
			mData = new Item [mSize];
		}

		~FuncReg()
		{
			delete [] mData;
		}

		void Add(std::string name, CFunction func)
		{
			mNameList.push_back(name);

			mData[mIndex].name = mNameList[mNameList.size()-1].c_str();
			mData[mIndex].func = func;
			mIndex++;

			if ( mIndex+1 == mSize )
			{
				get_more_memory();
			}
		}

		Item* _get()
		{
			return mData;
		}

	private:

		void get_more_memory()
		{
			mSize = mSize*2;

			Item    *new_block = new Item [mSize];

			for ( int i=0 ; mData[i].name!=NULL ; i++ )
			{
				new_block[i] = mData[i];
			}

			delete [] mData;
			mData = new_block;
		}

		int     mIndex;
		int     mSize;
		Item    *mData;
		std::vector<std::string>   mNameList;
};

inline void NewModule(Handle h,FuncReg &reg)
{
	luaL_newlib(h,(luaL_Reg*)(reg._get()));
}

inline Handle CreateHandle()
{
	return luaL_newstate();
}
inline void DestroyHandle(Handle h)
{
	lua_close(h);
}
inline int PCall(Handle h,int num01,int num02,int num03)
{
	return lua_pcall(h,num01,num02,num03);
}
inline void OpenLibs(Handle h)
{
	luaL_openlibs(h);
}
inline Str GetError(Handle h)
{
	Str  str(lua_tostring(h, -1));
	lua_pop(h, 1);

	return str;
}
inline int DoScript(Handle h,Name filename)
{
	if( luaL_loadfile(h,filename) )
	{
		return 0;
	}

	if( lua_pcall(h,0,0,0) )
	{
		return 0;
	}

	return 1;
}
inline void NewTable(Handle h)
{
	lua_newtable(h);
}
inline int NewMetaTable(Handle h,Name tname)
{
	return luaL_newmetatable(h,tname);
}
inline void* NewUserData(Handle h,size_t size)
{
	return lua_newuserdata(h,size);
}
inline void SetGlobal(Handle h,Name var)
{
	lua_setglobal(h,var);
}
inline void GetGlobal(Handle h,Name var)
{
	lua_getglobal(h,var);
}
inline void SetTable(Handle h,int index)
{
	lua_settable(h,index);
}
inline void GetTable(Handle h,int index)
{
	lua_gettable(h,index);
}
inline void SetField(Handle h,int index, Name name)
{
	lua_setfield(h,index,name);
}
inline void GetField(Handle h,int index, Name k)
{
	lua_getfield(h,index,k);
}
inline int SetMetaTable(Handle h,int index)
{
	return lua_setmetatable(h,index);
}
inline void GetMetaTable(Handle h,Name name)
{
	luaL_getmetatable(h,name);
}
inline void PushClosure(Handle h,CFunction fn,int n)
{
	lua_pushcclosure(h, fn, n);
}
inline void PushFunction(Handle h,CFunction fn)
{
	lua_pushcfunction(h,fn);
}
inline Name PushString(Handle h,Name str)
{
	return lua_pushstring(h, str);
}
inline Name PushString(Handle h,Str str)
{
	return lua_pushstring(h, str.c_str());
}
inline void PushValue(Handle h,int index)
{
	lua_pushvalue(h,index);
}
inline void PushNumber(Handle h,double n)
{
	lua_pushnumber(h,n);
}
inline void PushInteger(Handle h,int num)
{
	lua_pushinteger(h,num);
}
inline double CheckNumber(Handle h,int index)
{
	return luaL_checknumber(h,index);
}
inline int CheckInteger(Handle h,int index)
{
	return luaL_checkinteger(h,index);
}
inline Str CheckString(Handle h,int index)
{
	return Str(luaL_checkstring(h,index));
}
inline void* CheckUserData(Handle h,int ud, Name tname)
{
	return luaL_checkudata(h, ud, tname);
}
inline void PushPointer(Handle h,Ptr num)
{
	lua_pushlightuserdata(h,num);
}
inline Ptr CheckPointer(Handle h,int index)
{
//	if (lua_islightuserdata(h, index))
//        luaL_typerror(h, index, "lightuserdata");

    return (Ptr)lua_topointer(h, index);

//	return (Ptr)luaL_checkudata(h,index)
//	return (Ptr)luaL_checklightudata(h,index);
}
inline double ToNumber(Handle h,int index)
{
	return lua_tonumber(h,index);
}
inline int UpValueIndex(int index)
{
	return lua_upvalueindex(index);
}
inline void Pop(Handle h,int num)
{
	lua_pop(h,num);
}
inline void SetTop(Handle h,int num)
{
	lua_settop(h,num);
}
inline int GetTop(Handle h)
{
	return lua_gettop(h);
}


//----------------------tools----------------------start
inline void PushVarToLua(lua::Handle hLua,lua::Int t)
{
	lua::PushInteger(hLua,t);
}
inline void PushVarToLua(lua::Handle hLua,lua::Num t)
{
	lua::PushNumber(hLua,t);
}
inline void PushVarToLua(lua::Handle hLua,lua::Str t)
{
	lua::PushString(hLua,t);
}
inline void PushVarToLua(lua::Handle hLua,lua::Ptr t)
{
	lua::PushPointer(hLua,t);
}
inline void CheckVarFromLua(lua::Handle hLua,lua::Int *t,int i)
{
	*t=(lua::Int)lua::CheckInteger(hLua,i);
}
inline void CheckVarFromLua(lua::Handle hLua,lua::Num *t,int i)
{
	*t=(lua::Num)lua::CheckNumber(hLua,i);
}
inline void CheckVarFromLua(lua::Handle hLua,lua::Str *t,int i)
{
	*t=lua::CheckString(hLua,i);
}
inline void CheckVarFromLua(lua::Handle hLua,lua::Ptr *t,int i)
{
	*t=lua::CheckPointer(hLua,i);
}
//----------------------tools----------------------end


}//namespace lua

#endif//_LUAPP_STANDARD_HPP_
