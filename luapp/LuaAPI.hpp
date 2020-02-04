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
inline void _ReportLuaError(lua::NativeState h,lua::Str msg)
{
	const char *error_msg = lua_tostring((lua_State*)h,-1);

	lua::Log<<msg<<lua::End;
	lua::Log<<error_msg<<lua::End;
	lua_pop((lua_State*)h, 1);  // remove message
}
//------------------------------------------------------------------------------
inline void NewModule(lua::NativeState h,FuncReg &reg)
{
	luaL_newlib((lua_State*)h,reinterpret_cast<luaL_Reg*>(reg._get()));
}
//------------------------------------------------------------------------------
inline NativeState CreateHandle()
{
	return luaL_newstate();
}
//------------------------------------------------------------------------------
inline void DestroyHandle(lua::NativeState h)
{
	lua_close((lua_State*)h);
}
//------------------------------------------------------------------------------
inline void Call(lua::NativeState h,int args,int results)
{
	lua_call( (lua_State*)h, args, results );
}
//------------------------------------------------------------------------------
inline int PCall(lua::NativeState h,int args,int results,int msg_handler)
{
	int  result = lua_pcall( (lua_State*)h, args, results, msg_handler );

	if ( result != LUA_OK )
	{
		_ReportLuaError((lua_State*)h,"error:lua_pcall get error.");
	}

	return result;
}
//------------------------------------------------------------------------------
#ifdef _LUAPP_CHECK_CAREFUL_
static inline int _OpenLibs(lua::NativeState h)
{
	luaL_openlibs((lua_State*)h);
	return 1;
}
inline void OpenLibs(lua::NativeState h)
{
	//------Maybe luaL_openlibs will report something------
	lua_pushcfunction((lua_State*)h,(lua_CFunction)_OpenLibs);
	lua::PCall((lua_State*)h,0,0,0);
}
#else
inline void OpenLibs(lua::NativeState h)
{
	luaL_openlibs((lua_State*)h);
}
#endif
//------------------------------------------------------------------------------
inline int TypeCast(lua::NativeState h,int index)
{
	return lua_type((lua_State*)h,index);
}
//------------------------------------------------------------------------------
inline void DoString(lua::NativeState h,lua::Str code)
{
	if ( luaL_dostring((lua_State*)h, code.c_str()) )
	{
		_ReportLuaError((lua_State*)h,"error:DoString");
	}
}
//------------------------------------------------------------------------------
inline void _PrintScriptLoadingError(lua::NativeState h,int error_code,lua::Str& filename)
{
	lua::Str    msg;

	switch ( error_code )
	{
		case 0:
			msg = "warning:big mistake! It's not a error.";
			return;
		case LUA_ERRFILE:
			msg = "error:cannot open the file:";
			msg += filename;
			break;
		case LUA_ERRSYNTAX:
			msg = "error:syntax error during pre-compilation";
			break;
		case LUA_ERRMEM:
			msg = "error:memory allocation error";
			break;
		default:
			msg = "error:load script failed for some reason";
	}

	_ReportLuaError((lua_State*)h,msg);
}
//------------------------------------------------------------------------------
inline int LoadScript(lua::NativeState h,lua::Str name,lua::Str& code)
{
	if ( name.empty() )
	{
		lua::Log<<"error:script name is empty string"<<lua::End;
		return 0;
	}
	else
	{
		int result = luaL_loadbuffer((lua_State*)h,code.c_str(), code.size(), name.c_str());

		if ( result != LUA_OK )
		{
			_PrintScriptLoadingError((lua_State*)h,result,name);
			lua::Log<<"error:luaL_loadbuffer get error."<<lua::End;

			return 0;
		}
	}

	return 1;
}
//------------------------------------------------------------------------------
inline int LoadScript(lua::NativeState h,lua::Str filename)
{
	if ( filename.empty() )
	{
		lua::Log<<"error:file name is empty string"<<lua::End;
		return 0;
	}
	else
	{
		int result = luaL_loadfile((lua_State*)h,filename.c_str());

		if ( result )
		{
			_PrintScriptLoadingError((lua_State*)h,result,filename);
			lua::Log<<"error:luaL_loadfile get error."<<lua::End;
			return 0;
		}
	}

	return 1;
}
//------------------------------------------------------------------------------
inline int DoScript(lua::NativeState h,lua::Str name,lua::Str& code)
{
	if ( name.empty() )
	{
		lua::Log<<"error:script name is empty string"<<lua::End;
		return 0;
	}
	else
	{
		int result = luaL_loadbuffer((lua_State*)h,code.c_str(), code.size(), name.c_str());

		if ( result )
		{
			_PrintScriptLoadingError((lua_State*)h,result,name);
			lua::Log<<"error:luaL_loadbuffer get error."<<lua::End;
			return 0;
		}
	}

	if( ::lua::PCall((lua_State*)h,0,0,0) )
	{
		return 0;
	}

	return 1;
}
//------------------------------------------------------------------------------
inline int DoScript(lua::NativeState h,lua::Str filename)
{
	if ( filename.empty() )
	{
		lua::Log<<"error:file name is empty string"<<lua::End;
		return 0;
	}
	else
	{
		int result = luaL_loadfile((lua_State*)h,filename.c_str());

		if ( result )
		{
			_PrintScriptLoadingError((lua_State*)h,result,filename);
			lua::Log<<"error:luaL_loadfile get error."<<lua::End;
			return 0;
		}
	}

	if( ::lua::PCall((lua_State*)h,0,0,0) )
	{
		return 0;
	}

	return 1;
}
//------------------------------------------------------------------------------
inline void NewTable(lua::NativeState h)
{
	lua_newtable((lua_State*)h);
}
//------------------------------------------------------------------------------
inline int NewMetaTable(lua::NativeState h,lua::Str tname)
{
	#ifdef _LUAPP_CHECK_CAREFUL_
	luaL_getmetatable((lua_State*)h,tname.c_str());
	if ( lua_type((lua_State*)h, -1)!=LUA_TNIL )
	{
		lua::Log<<"error:this meta table already exist."<<lua::End;
	}
	lua_pop((lua_State*)h,1);
	#endif

	return luaL_newmetatable((lua_State*)h,tname.c_str());
}
//------------------------------------------------------------------------------
inline void* NewUserData(lua::NativeState h,size_t size)
{
	return lua_newuserdata((lua_State*)h,size);
}
//------------------------------------------------------------------------------
inline void RemoveGlobal(lua::NativeState h,lua::Str var)
{
	lua_pushnil((lua_State*)h);
	lua_setglobal((lua_State*)h,var.c_str());
}
//------------------------------------------------------------------------------
inline void SetGlobal(lua::NativeState h,lua::Str var)
{
	#ifdef _LUAPP_CHECK_CAREFUL_
	lua_getglobal((lua_State*)h,var.c_str());
	if ( lua_type((lua_State*)h, -1)!=LUA_TNIL )
	{
		lua::Log<<"warning:this global variable already exist."<<lua::End;
	}
	lua_pop((lua_State*)h,1);
	#endif

	lua_setglobal((lua_State*)h,var.c_str());
}
//------------------------------------------------------------------------------
inline bool IsGlobal(lua::NativeState h,lua::Str var)
{
	lua_getglobal((lua_State*)h,var.c_str());

	if ( lua_type((lua_State*)h, -1)!=LUA_TNIL )
	{
		lua_pop((lua_State*)h,1);
		return true;
	}

	lua_pop((lua_State*)h,1);
	return false;
}
//------------------------------------------------------------------------------
inline void GetGlobal(lua::NativeState h,lua::Str var)
{
	lua_getglobal((lua_State*)h,var.c_str());
}
//------------------------------------------------------------------------------
inline void SetTable(lua::NativeState h,int index)
{
	lua_settable((lua_State*)h,index);
}
//------------------------------------------------------------------------------
inline void GetTable(lua::NativeState h,int index)
{
	lua_gettable((lua_State*)h,index);
}
//------------------------------------------------------------------------------
inline void SetField(lua::NativeState h,int index, lua::Str name)
{
	lua_setfield((lua_State*)h,index,name.c_str());
}
//------------------------------------------------------------------------------
inline void GetField(lua::NativeState h,int index, lua::Str k)
{
	lua_getfield((lua_State*)h,index,k.c_str());
}
//------------------------------------------------------------------------------
inline int SetMetaTable(lua::NativeState h,int index)
{
	return lua_setmetatable((lua_State*)h,index);
}
//------------------------------------------------------------------------------
inline void GetMetaTable(lua::NativeState h,lua::Str name)
{
	luaL_getmetatable((lua_State*)h,name.c_str());
}
//------------------------------------------------------------------------------
inline void PushNil(lua::NativeState h)
{
	lua_pushnil((lua_State*)h);
}
//------------------------------------------------------------------------------
inline void PushClosure(lua::NativeState h,CFunction fn,int n)
{
	lua_pushcclosure((lua_State*)h, (lua_CFunction)fn, n);
}
//------------------------------------------------------------------------------
inline void PushFunction(lua::NativeState h,CFunction fn)
{
	lua_pushcfunction((lua_State*)h,(lua_CFunction)fn);
}
//------------------------------------------------------------------------------
inline void PushString(lua::NativeState h,lua::Str str)
{
	lua_pushstring((lua_State*)h, str.c_str());
}
//------------------------------------------------------------------------------
inline void PushValue(lua::NativeState h,int index)
{
	lua_pushvalue((lua_State*)h,index);
}
//------------------------------------------------------------------------------
inline void PushNumber(lua::NativeState h,lua::Num n)
{
	lua_pushnumber((lua_State*)h,n);
}
//------------------------------------------------------------------------------
inline void PushBoolean(lua::NativeState h,bool num)
{
	lua_pushboolean((lua_State*)h,(int)num);
}
//------------------------------------------------------------------------------
inline void PushInteger(lua::NativeState h,lua::Int num)
{
	lua_pushinteger((lua_State*)h,num);
}
//------------------------------------------------------------------------------
template<typename S>
inline void PushUserData(lua::NativeState h,S ud)
{
	                                                          // ...
	void* ptr = lua::NewUserData((lua_State*)h, sizeof(S));   // ... [UD]
	*((S*)ptr) = ud;
}
//------------------------------------------------------------------------------
template<typename S>
inline void PushUserData(lua::NativeState h,S ud, lua::Str tname)
{
	                                                           // ...
	void*  ptr = lua::NewUserData((lua_State*)h, sizeof(S));   // ... [UD]
	*((S*)ptr) = ud;
	lua::GetMetaTable((lua_State*)h, tname.c_str());           // ... [UD] [MT]
	lua::SetMetaTable((lua_State*)h, -2);                      // ... [UD]
}
//------------------------------------------------------------------------------
inline lua::Num CheckNumber(lua::NativeState h,int index)
{
//	return luaL_checknumber((lua_State*)h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type((lua_State*)h,index)!=LUA_TNUMBER )
	{
		lua::Log<<"error:lua::CheckNumber"<<lua::End;
		return (lua::Num)0.0;
	}
	#endif

	return lua_tonumber((lua_State*)h,index);
}
//------------------------------------------------------------------------------
inline bool CheckBoolean(lua::NativeState h,int index)
{
//	return luaL_checkboolean((lua_State*)h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type((lua_State*)h,index)!=LUA_TBOOLEAN )
	{
		lua::Log<<"error:lua::CheckBoolean"<<lua::End;
		return false;
	}
	#endif

	return lua_toboolean((lua_State*)h,index)==0 ? false:true;
}
//------------------------------------------------------------------------------
inline lua::Int CheckInteger(lua::NativeState h,int index)
{
//	return luaL_checkinteger((lua_State*)h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type((lua_State*)h, index)!=LUA_TNUMBER )
	{
		lua::Log<<"error:lua::CheckInteger"<<lua::End;
		return (lua::Int)0;
	}
	else if ( ! lua_isinteger((lua_State*)h,index) )
	{
		lua::Log<<"error:lua::CheckInteger: not a integer"<<lua::End;
		return (lua::Int)0;
	}
	#endif

	return (lua::Int)lua_tointeger((lua_State*)h,index);
}
//------------------------------------------------------------------------------
inline Str CheckString(lua::NativeState h,int index)
{
//	return Str(luaL_checkstring((lua_State*)h,index));

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type((lua_State*)h, index)!=LUA_TSTRING )
	{
		lua::Log<<"error:lua::CheckString"<<lua::End;
		return Str("none");
	}
	#endif

	return lua_tostring((lua_State*)h,index);
}
//------------------------------------------------------------------------------
inline void* CheckUserData(lua::NativeState h,int index)
{
	return lua_touserdata((lua_State*)h,index);
}
//------------------------------------------------------------------------------
inline void* CheckUserData(lua::NativeState h,int index, lua::Str tname)
{
	return luaL_checkudata((lua_State*)h, index, tname.c_str());
}
//------------------------------------------------------------------------------
inline void PushPointer(lua::NativeState h,Ptr ptr)
{
	lua_pushlightuserdata((lua_State*)h,ptr);
}
//------------------------------------------------------------------------------
#ifdef _LUAPP_CPP11_
inline void PushPointer(lua::NativeState h,std::nullptr_t)
{
	lua_pushlightuserdata((lua_State*)h,nullptr);
}
#endif
//------------------------------------------------------------------------------
inline Ptr CheckPointer(lua::NativeState h,int index)
{
//	return (Ptr)luaL_checklightudata((lua_State*)h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type((lua_State*)h, index)!=LUA_TLIGHTUSERDATA )
	{
		lua::Log<<"error:lua::CheckPointer"<<lua::End;
		#ifdef _LUAPP_CPP11_
		return nullptr;
		#else
		return NULL;
		#endif
	}
	#endif

    return (lua::Ptr)lua_topointer((lua_State*)h, index);
}
//------------------------------------------------------------------------------
inline int UpValueIndex(int index)
{
	return lua_upvalueindex(index);
}
//------------------------------------------------------------------------------
inline void Pop(lua::NativeState h,int num)
{
	lua_pop((lua_State*)h,num);
}
//------------------------------------------------------------------------------
inline void Replace(lua::NativeState h,int num)
{
	lua_replace((lua_State*)h,num);
}
//------------------------------------------------------------------------------
inline void SetTop(lua::NativeState h,int num)
{
	lua_settop((lua_State*)h,num);
}
//------------------------------------------------------------------------------
inline int GetTop(lua::NativeState h)
{
	return lua_gettop((lua_State*)h);
}
//------------------------------------------------------------------------------
inline int RaiseError(lua::NativeState h)
{
	return lua_error((lua_State*)h);
}
//------------------------------------------------------------------------------
inline bool _VisitTableNext(lua::NativeState h,int index)
{
	return (lua_next((lua_State*)h, index)!=0)?true:false;
}
//------------------------------------------------------------------------------
inline int _GetTypeID(lua::NativeState h,int index)
{
	int id = lua_type((lua_State*)h,index);

	if ( (id==LUA_TNUMBER)&&lua_isinteger((lua_State*)h,index) )
	{
		return 20;      // Bad idea
	}

	return id;
}
//------------------------------------------------------------------------------
inline int _GetTypeBool()          { return LUA_TBOOLEAN; }
inline int _GetTypeInteger()       { return 20; }          // Bad idea
inline int _GetTypeNumber()        { return LUA_TNUMBER; }
inline int _GetTypeString()        { return LUA_TSTRING; }
inline int _GetTypeFunc()          { return LUA_TFUNCTION; }
inline int _GetTypeTable()         { return LUA_TTABLE; }
inline int _GetTypeNil()           { return LUA_TNIL; }
inline int _GetTypeNone()          { return LUA_TNONE; }
inline int _GetTypeUserData()      { return LUA_TUSERDATA; }
inline int _GetTypeLightUserData() { return LUA_TLIGHTUSERDATA; }
inline int _GetTypeThread()        { return LUA_TTHREAD; }
//------------------------------------------------------------------------------
inline bool IsTypeBool(lua::NativeState h,int index)
{
	return ( lua_type((lua_State*)h,index)==LUA_TBOOLEAN )?true:false;
}
//------------------------------------------------------------------------------
inline bool IsTypeInteger(lua::NativeState h,int index)
{
	return lua_isinteger((lua_State*)h,index)?true:false;
}
//------------------------------------------------------------------------------
inline bool IsTypeNumber(lua::NativeState h,int index)
{
	if ( lua_isnumber((lua_State*)h,index) )
	{
		if ( lua_isinteger((lua_State*)h,index) ) return false;
		return true;
	}

	return false;
}
//------------------------------------------------------------------------------
inline bool IsTypeString(lua::NativeState h,int index)
{
	return ( lua_type((lua_State*)h,index)==LUA_TSTRING )?true:false;
}
//------------------------------------------------------------------------------
inline bool IsTypeFunc(lua::NativeState h,int index)
{
	return ( lua_type((lua_State*)h,index)==LUA_TFUNCTION )?true:false;
}
//------------------------------------------------------------------------------
inline bool IsTypeTable(lua::NativeState h,int index)
{
	return ( lua_type((lua_State*)h,index)==LUA_TTABLE )?true:false;
}
//------------------------------------------------------------------------------
template<typename S> struct _TypeFilter{};
template<>
struct _TypeFilter<lua::Bool>
{
	static bool check(lua::NativeState h,int index)
	{
		return IsTypeBool(h,index);
	}

	static int id()
	{
		return _GetTypeBool();
	}
};
template<>
struct _TypeFilter<lua::Int>
{
	static bool check(lua::NativeState h,int index)
	{
		return IsTypeInteger(h,index);
	}

	static int id()
	{
		return _GetTypeInteger();
	}
};
template<>
struct _TypeFilter<lua::Num>
{
	static bool check(lua::NativeState h,int index)
	{
		return IsTypeNumber(h,index);
	}

	static int id()
	{
		return _GetTypeNumber();
	}
};
template<>
struct _TypeFilter<lua::Str>
{
	static bool check(lua::NativeState h,int index)
	{
		return IsTypeString(h,index);
	}

	static int id()
	{
		return _GetTypeString();
	}
};
template<>
struct _TypeFilter<lua::Func>
{
	static bool check(lua::NativeState h,int index)
	{
		return IsTypeFunc(h,index);
	}

	static int id()
	{
		return _GetTypeFunc();
	}
};
template<>
struct _TypeFilter<lua::Table>
{
	static bool check(lua::NativeState h,int index)
	{
		return IsTypeTable(h,index);
	}

	static int id()
	{
		return _GetTypeTable();
	}
};
template<>
struct _TypeFilter<lua::Nil>
{
	static bool check(lua::NativeState h,int index)
	{
		return ( _GetTypeID(h,index)==_GetTypeNil() ) ? true : false;
	}

	static int id()
	{
		return _GetTypeNil();
	}
};
template<>
struct _TypeFilter<lua::Task>
{
	static int id()
	{
		return _GetTypeThread();
	}
};
template<typename T>
inline bool IsType(lua::NativeState h,int index)
{
	return _TypeFilter<T>::check(h,index);
}
template<typename T>
inline int TypeID()
{
	return _TypeFilter<T>::id();
}
//------------------------------------------------------------------------------

}
