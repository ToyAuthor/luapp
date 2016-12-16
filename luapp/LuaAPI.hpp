/**
 * @file   LuaAPI.hpp
 * @brief  It's just a wrapper of lua.
 */

#pragma once


#include "lua.hpp"
#include "luapp/DataType.hpp"
#include "luapp/FuncReg.hpp"

namespace lua{


//------------------------------------------------------------------------------
inline void NewModule(NativeState h,FuncReg &reg)
{
	luaL_newlib(h,(luaL_Reg*)(reg._get()));
}
//------------------------------------------------------------------------------
inline NativeState CreateHandle()
{
	return luaL_newstate();
}
//------------------------------------------------------------------------------
inline void DestroyHandle(NativeState h)
{
	lua_close(h);
}
//------------------------------------------------------------------------------
inline int PCall(NativeState h,int num01,int num02,int num03)
{
	int  result = lua_pcall(h,num01,num02,num03);

	if ( result != LUA_OK )
	{
		const char *msg = lua_tostring(h,-1);

		lua::Log<<"error:lua_pcall get error."<<lua::End;
		lua::Log<<msg<<lua::End;
		lua_pop(h, 1);  // remove message
	}

	return result;
}
//------------------------------------------------------------------------------
inline void OpenLibs(NativeState h)
{
	luaL_openlibs(h);
}
//------------------------------------------------------------------------------
inline int TypeCast(NativeState h,int index)
{
	return lua_type(h,index);
}
//------------------------------------------------------------------------------
inline void DoString(NativeState h,lua::Str code)
{
	luaL_dostring(h, code.c_str());
}
//------------------------------------------------------------------------------
inline void _PrintScriptLoadingError(NativeState h,int error_code,lua::Str& filename)
{
	switch ( error_code )
	{
		case 0:
			lua::Log<<"warning:big mistake! It's not a error."<<lua::End;
			return;
		case LUA_ERRFILE:
			lua::Log<<"error:cannot open the file:"<<filename<<lua::End;
			break;
		case LUA_ERRSYNTAX:
			lua::Log<<"error:syntax error during pre-compilation"<<lua::End;
			break;
		case LUA_ERRMEM:
			lua::Log<<"error:memory allocation error"<<lua::End;
			break;
		default:
			lua::Log<<"error:load script failed for some reason"<<lua::End;
	}

	const char *msg = lua_tostring(h,-1);
	lua::Log<<msg<<lua::End;
	lua_pop(h, 1);  // remove message
}
//------------------------------------------------------------------------------
inline int LoadScript(NativeState h,lua::Str name,lua::Str& code)
{
	if ( name.empty() )
	{
		lua::Log<<"error:script name is empty string"<<lua::End;
		return 0;
	}
	else
	{
		int result = luaL_loadbuffer(h,code.c_str(), code.size(), name.c_str());

		if ( result != LUA_OK )
		{
			_PrintScriptLoadingError(h,result,name);
			lua::Log<<"error:luaL_loadbuffer get error."<<lua::End;

			return 0;
		}
	}

	return 1;
}
//------------------------------------------------------------------------------
inline int LoadScript(NativeState h,lua::Str filename)
{
	if ( filename.empty() )
	{
		lua::Log<<"error:file name is empty string"<<lua::End;
		return 0;
	}
	else
	{
		int result = luaL_loadfile(h,filename.c_str());

		if ( result )
		{
			_PrintScriptLoadingError(h,result,filename);
			lua::Log<<"error:luaL_loadfile get error."<<lua::End;
			return 0;
		}
	}

	return 1;
}
//------------------------------------------------------------------------------
inline int DoScript(NativeState h,lua::Str name,lua::Str& code)
{
	if ( name.empty() )
	{
		lua::Log<<"error:script name is empty string"<<lua::End;
		return 0;
	}
	else
	{
		int result = luaL_loadbuffer(h,code.c_str(), code.size(), name.c_str());

		if ( result )
		{
			_PrintScriptLoadingError(h,result,name);
			lua::Log<<"error:luaL_loadbuffer get error."<<lua::End;
			return 0;
		}
	}

	if( ::lua::PCall(h,0,0,0) )
	{
		return 0;
	}

	return 1;
}
//------------------------------------------------------------------------------
inline int DoScript(NativeState h,lua::Str filename)
{
	if ( filename.empty() )
	{
		lua::Log<<"error:file name is empty string"<<lua::End;
		return 0;
	}
	else
	{
		int result = luaL_loadfile(h,filename.c_str());

		if ( result )
		{
			_PrintScriptLoadingError(h,result,filename);
			lua::Log<<"error:luaL_loadfile get error."<<lua::End;
			return 0;
		}
	}

	if( ::lua::PCall(h,0,0,0) )
	{
		return 0;
	}

	return 1;
}
//------------------------------------------------------------------------------
inline void NewTable(NativeState h)
{
	lua_newtable(h);
}
//------------------------------------------------------------------------------
inline int NewMetaTable(NativeState h,lua::Str tname)
{
	#ifdef _LUAPP_CHECK_CAREFUL_
	luaL_getmetatable(h,tname.c_str());
	if ( lua_type(h, -1)!=LUA_TNIL )
	{
		lua::Log<<"error:this meta table already exist."<<lua::End;
	}
	lua_pop(h,1);
	#endif

	return luaL_newmetatable(h,tname.c_str());
}
//------------------------------------------------------------------------------
inline void* NewUserData(NativeState h,size_t size)
{
	return lua_newuserdata(h,size);
}
//------------------------------------------------------------------------------
inline void RemoveGlobal(NativeState h,lua::Str var)
{
	lua_pushnil(h);
	lua_setglobal(h,var.c_str());
}
//------------------------------------------------------------------------------
inline void SetGlobal(NativeState h,lua::Str var)
{
	#ifdef _LUAPP_CHECK_CAREFUL_
	lua_getglobal(h,var.c_str());
	if ( lua_type(h, -1)!=LUA_TNIL )
	{
		lua::Log<<"warning:this global variable already exist."<<lua::End;
	}
	lua_pop(h,1);
	#endif

	lua_setglobal(h,var.c_str());
}
//------------------------------------------------------------------------------
inline void GetGlobal(NativeState h,lua::Str var)
{
	lua_getglobal(h,var.c_str());
}
//------------------------------------------------------------------------------
inline void SetTable(NativeState h,int index)
{
	lua_settable(h,index);
}
//------------------------------------------------------------------------------
inline void GetTable(NativeState h,int index)
{
	lua_gettable(h,index);
}
//------------------------------------------------------------------------------
inline void SetField(NativeState h,int index, lua::Str name)
{
	lua_setfield(h,index,name.c_str());
}
//------------------------------------------------------------------------------
inline void GetField(NativeState h,int index, lua::Str k)
{
	lua_getfield(h,index,k.c_str());
}
//------------------------------------------------------------------------------
inline int SetMetaTable(NativeState h,int index)
{
	return lua_setmetatable(h,index);
}
//------------------------------------------------------------------------------
inline void GetMetaTable(NativeState h,lua::Str name)
{
	luaL_getmetatable(h,name.c_str());
}
//------------------------------------------------------------------------------
inline void PushNil(NativeState h)
{
	lua_pushnil(h);
}
//------------------------------------------------------------------------------
inline void PushClosure(NativeState h,CFunction fn,int n)
{
	lua_pushcclosure(h, fn, n);
}
//------------------------------------------------------------------------------
inline void PushFunction(NativeState h,CFunction fn)
{
	lua_pushcfunction(h,fn);
}
//------------------------------------------------------------------------------
inline void PushString(NativeState h,lua::Str str)
{
	lua_pushstring(h, str.c_str());
}
//------------------------------------------------------------------------------
inline void PushValue(NativeState h,int index)
{
	lua_pushvalue(h,index);
}
//------------------------------------------------------------------------------
inline void PushNumber(NativeState h,double n)
{
	lua_pushnumber(h,n);
}
//------------------------------------------------------------------------------
inline void PushBoolean(NativeState h,bool num)
{
	lua_pushboolean(h,(int)num);
}
//------------------------------------------------------------------------------
inline void PushInteger(NativeState h,int num)
{
	lua_pushinteger(h,num);
}
//------------------------------------------------------------------------------
template<typename S>
inline void PushUserData(NativeState h,S ud)
{
	                                               // ...
	void*  ptr = lua::NewUserData(h, sizeof(S));   // ... [UD]
	*((S*)ptr) = ud;
}
//------------------------------------------------------------------------------
template<typename S>
inline void PushUserData(NativeState h,S ud, lua::Str tname)
{
	                                               // ...
	void*  ptr = lua::NewUserData(h, sizeof(S));   // ... [UD]
	*((S*)ptr) = ud;
	lua::GetMetaTable(h, tname.c_str());           // ... [UD] [MT]
	lua::SetMetaTable(h, -2);                      // ... [UD]
}
//------------------------------------------------------------------------------
inline double CheckNumber(NativeState h,int index)
{
//	return luaL_checknumber(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h,index)!=LUA_TNUMBER )
	{
		lua::Log<<"error:lua::CheckNumber"<<lua::End;
		return 0.0;
	}
	#endif

	return lua_tonumber(h,index);
}
//------------------------------------------------------------------------------
inline bool CheckBoolean(NativeState h,int index)
{
//	return luaL_checkboolean(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h,index)!=LUA_TBOOLEAN )
	{
		lua::Log<<"error:lua::CheckBoolean"<<lua::End;
		return false;
	}
	#endif

	return lua_toboolean(h,index)==0 ? false:true;
}
//------------------------------------------------------------------------------
inline int CheckInteger(NativeState h,int index)
{
//	return luaL_checkinteger(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h, index)!=LUA_TNUMBER )
	{
		lua::Log<<"error:lua::CheckInteger"<<lua::End;
		return 0;
	}
	else if ( ! lua_isinteger(h,index) )
	{
		lua::Log<<"error:lua::CheckInteger: not a integer"<<lua::End;
		return 0;
	}
	#endif

	return (int)lua_tointeger(h,index);
}
//------------------------------------------------------------------------------
inline Str CheckString(NativeState h,int index)
{
//	return Str(luaL_checkstring(h,index));

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h, index)!=LUA_TSTRING )
	{
		lua::Log<<"error:lua::CheckString"<<lua::End;
		return Str("none");
	}
	#endif

	return lua_tostring(h,index);
}
//------------------------------------------------------------------------------
inline void* CheckUserData(NativeState h,int index)
{
	return lua_touserdata(h,index);
}
//------------------------------------------------------------------------------
inline void* CheckUserData(NativeState h,int index, lua::Str tname)
{
	return luaL_checkudata(h, index, tname.c_str());
}
//------------------------------------------------------------------------------
inline void PushPointer(NativeState h,Ptr ptr)
{
	lua_pushlightuserdata(h,ptr);
}
//------------------------------------------------------------------------------
#ifdef _LUAPP_CPP11_
inline void PushPointer(NativeState h,std::nullptr_t)
{
	lua_pushlightuserdata(h,(void*)0);
}
#endif
//------------------------------------------------------------------------------
inline Ptr CheckPointer(NativeState h,int index)
{
//	return (Ptr)luaL_checklightudata(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h, index)!=LUA_TLIGHTUSERDATA )
	{
		lua::Log<<"error:lua::CheckPointer"<<lua::End;
		#ifdef _LUAPP_CPP11_
		return nullptr;
		#else
		return NULL;
		#endif
	}
	#endif

    return (Ptr)lua_topointer(h, index);
}
//------------------------------------------------------------------------------
inline int UpValueIndex(int index)
{
	return lua_upvalueindex(index);
}
//------------------------------------------------------------------------------
inline void Pop(NativeState h,int num)
{
	lua_pop(h,num);
}
//------------------------------------------------------------------------------
inline void Replace(NativeState h,int num)
{
	lua_replace(h,num);
}
//------------------------------------------------------------------------------
inline void SetTop(NativeState h,int num)
{
	lua_settop(h,num);
}
//------------------------------------------------------------------------------
inline int GetTop(NativeState h)
{
	return lua_gettop(h);
}
//------------------------------------------------------------------------------

}
