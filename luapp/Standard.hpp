/**
@file   Standard.hpp
@brief  It's just a wrapper of lua.
*/

#ifndef _LUAPP_STANDARD_HPP_
#define _LUAPP_STANDARD_HPP_



#include <vector>
#include <string>
#include "lua.hpp"
#include "luapp/Define.hpp"
#include "luapp/DataType.hpp"
#include "luapp/Table.hpp"

namespace lua{


//----------Short name----------
typedef lua_State* Handle;
typedef int (*CFunction) (Handle);   // lua::CFunction as lua_CFunction.
typedef const char* Name;


/*
 * It's a function register for lua.
 * Basically, this class just a manager of luaL_Reg.
 */
class FuncReg
{
	public:

		// lua::FuncReg::Item as luaL_Reg.
		#ifdef _LUAPP_USING_CPP11_
		struct Item
		{
			Name       name = nullptr;
			CFunction  func = nullptr;
		};
		#else
		struct Item
		{
			Item():name(NULL),func(NULL){}
			Name       name;
			CFunction  func;
		};
		#endif

		FuncReg():_index(0),_size(4),_data(0)
		{
			_data = new Item [_size];
		}

		~FuncReg()
		{
			delete [] _data;
		}

		void add(std::string name, CFunction func)
		{
			_nameList.push_back(name);

			_data[_index].func = func;
			_index++;

			// If it get n elements in list, then list size alway bigger than n+1.
			if ( _index+1 == _size )
			{
				get_more_memory();
			}
		}

		void refresh()
		{
			for ( int i=0 ; i<_index ; i++ )
			{
				_data[i].name = _nameList[i].c_str();
			}
		}

		Item* _get()
		{
			return _data;
		}

	private:

		void get_more_memory()
		{
			_size = _size*2;

			Item    *new_block = new Item [_size];

			for ( int i=0 ; _data[i].func!=NULL ; i++ )
			{
				new_block[i] = _data[i];
			}

			delete [] _data;
			_data = new_block;
		}

		int     _index;
		int     _size;
		Item*   _data;
		std::vector<std::string>   _nameList;
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
inline void PushBoolean(Handle h,bool num)
{
	lua_pushboolean(h,(int)num);
}
inline void PushInteger(Handle h,int num)
{
	lua_pushinteger(h,num);
}
inline double CheckNumber(Handle h,int index)
{
//	return luaL_checknumber(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h,index)!=LUA_TNUMBER )
	{
		printf("error:lua::CheckNumber\n");
		return 0.0;
	}
	#endif

	return lua_tonumber(h,index);
}
inline bool CheckBoolean(Handle h,int index)
{
//	return luaL_checkboolean(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h,index)!=LUA_TBOOLEAN )
	{
		printf("error:lua::CheckBoolean\n");
		return false;
	}
	#endif

	return lua_toboolean(h,index);
}
inline int CheckInteger(Handle h,int index)
{
//	return luaL_checkinteger(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h, index)!=LUA_TNUMBER )
	{
		printf("error:lua::CheckInteger\n");
		return 0;
	}
	else if ( ! lua_isinteger(h,index) )
	{
		printf("error:lua::CheckInteger: not a integer\n");
		return 0;
	}
	#endif

	return lua_tointeger(h,index);
}
inline Str CheckString(Handle h,int index)
{
//	return Str(luaL_checkstring(h,index));

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h, index)!=LUA_TSTRING )
	{
		printf("error:lua::CheckString\n");
		return Str();
	}
	#endif

	return lua_tolstring(h,index,NULL);
}
inline void* CheckUserData(Handle h,int ud, Name tname)
{
	return luaL_checkudata(h, ud, tname);
}
inline void PushPointer(Handle h,Ptr ptr)
{
	lua_pushlightuserdata(h,ptr);
}
inline Ptr CheckPointer(Handle h,int index)
{
//	return (Ptr)luaL_checklightudata(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h, index)!=LUA_TLIGHTUSERDATA )
	{
		#ifdef _LUAPP_USING_CPP11_
		return nullptr;
		#else
		return NULL;
		#endif
	}
	#endif

    return (Ptr)lua_topointer(h, index);
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


//---------------------------PushVarToLua and CheckVarFromLua---------------------------start
inline void PushVarToLua(lua::Handle hLua,lua::Bool t)
{
	lua::PushBoolean(hLua,t);
}
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
inline void CheckVarFromLua(lua::Handle hLua,lua::Bool *t,int i)
{
	*t=(lua::Bool)lua::CheckBoolean(hLua,i);
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

// Only work for "void PushVarToLua(lua::Handle hLua,lua::Table &table)"
inline void _PushValueToLuaTable(lua::Handle hLua,lua::Table &table)
{
	lua::NewTable(hLua);                 // ... [T]

	lua::Table::Iterator   it = table.getBegin();

	lua::Var   key;
	lua::Var   value;

	for ( ; ! it.isEnd() ; it++ )
	{
		// ... [T]

		it.getKeyValue( &key, &value );

		if ( lua::VarType<lua::Str>(key) )
		{
			lua::Str   t_key = lua::VarCast<lua::Str>(key);
			PushVarToLua(hLua,t_key);                        // ... [T] [key]
		}
		else if ( lua::VarType<lua::Int>(key) )
		{
			lua::Int   t_key = lua::VarCast<lua::Int>(key);
			PushVarToLua(hLua,t_key);                        // ... [T] [key]
		}
		else if ( lua::VarType<lua::Num>(key) )
		{
			lua::Num   t_key = lua::VarCast<lua::Num>(key);
			PushVarToLua(hLua,t_key);                        // ... [T] [key]
		}
		/*
		else if ( lua::VarType<lua::Bool>(key) )
		{
			lua::Bool  t_key = lua::VarCast<lua::Bool>(key);
			PushVarToLua(hLua,t_key);                        // ... [T] [key]
		}
		*/
		else
		{
			continue;    // Just in case.
		}

		if ( lua::VarType<lua::Str>(value) )
		{
			lua::Str   t_value = lua::VarCast<lua::Str>(value);
			PushVarToLua(hLua,t_value);                               // ... [T] [key] [value]
		}
		else if ( lua::VarType<lua::Int>(value) )
		{
			lua::Int   t_value = lua::VarCast<lua::Int>(value);
			PushVarToLua(hLua,t_value);                               // ... [T] [key] [value]
		}
		else if ( lua::VarType<lua::Num>(value) )
		{
			lua::Num   t_value = lua::VarCast<lua::Num>(value);
			PushVarToLua(hLua,t_value);                               // ... [T] [key] [value]
		}
		else if ( lua::VarType<lua::Ptr>(value) )
		{
			lua::Ptr   t_value = lua::VarCast<lua::Ptr>(value);
			PushVarToLua(hLua,t_value);                               // ... [T] [key] [value]
		}
		else if ( lua::VarType<lua::Bool>(value) )
		{
			lua::Bool   t_value = lua::VarCast<lua::Bool>(value);
			PushVarToLua(hLua,t_value);                               // ... [T] [key] [value]
		}
		else if ( lua::VarType<lua::Table>(value) )
		{
			lua::Table   t_value = lua::VarCast<lua::Table>(value);
			_PushValueToLuaTable(hLua,t_value);                       // ... [T] [key] [value]
		}
		else
		{
			lua_pop(hLua, 1);           // ... [T]
			continue;
		}

		lua::SetTable(hLua,-3);      // ... [T]
	}

	// ... [T]
}

inline void PushVarToLua(lua::Handle hLua,lua::Table &table)
{
	                                     // ...
	_PushValueToLuaTable(hLua,table);    // ... [T]
}

//------They only work for void CheckVarFromLua(lua::Handle,lua::Table*,int)------start

inline void _VisitTable(lua::Handle hLua,lua::Table *table);

template<typename T>
inline void _SaveTableValue(lua::Handle hLua,lua::Table *table,T key)
{
	// ... [value]

	int   type = lua_type(hLua, -1);

	if ( type==LUA_TSTRING )
	{
		lua::Str   _value;
		CheckVarFromLua(hLua,&_value,-1);
		lua::Var   value(_value);
		(*table)[key] = value;
	}
	else if ( type==LUA_TTABLE )
	{
		lua::Table   subTable;
		_VisitTable(hLua,&subTable);

		lua::Var   value = subTable;
		(*table)[key] = value;
	}
	// Just in case.
	else if ( type==LUA_TNIL )
	{
		// This element is not exist.
	}
	else if ( type==LUA_TNONE )
	{
		printf("luapp:No one know what type is it\n");
	}
	else if ( type==LUA_TLIGHTUSERDATA )
	{
		lua::Ptr   value;
		CheckVarFromLua(hLua,&value,-1);
		(*table)[key] = value;
	}
	else if ( type==LUA_TBOOLEAN )
	{
		lua::Bool   value;
		CheckVarFromLua(hLua,&value,-1);
		(*table)[key] = value;
	}
	else if ( lua_isinteger(hLua, -1) )
	{
		lua::Int   value;
		CheckVarFromLua(hLua,&value,-1);
		(*table)[key] = value;
	}
	else if ( lua_isnumber(hLua, -1) )
	{
		lua::Num   value;
		CheckVarFromLua(hLua,&value,-1);
		(*table)[key] = value;
	}
	else
	{
		// drop else value.
	}

	// ... [value]
}

inline void _SwitchTableKey(lua::Handle hLua,lua::Table *table)
{
	                                      // ... [T] [key] [value] [key]

	if ( lua_type(hLua, -1)==LUA_TSTRING )
	{
		lua::Str   key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua_pop(hLua, 1);                 // ... [T] [key] [value]
		_SaveTableValue(hLua,table,key);
	}
	/* Not implement yet. Maybe I will ignore it ever.
	else if ( lua_type(hLua, -1)==LUA_TBOOLEAN )
	{
		lua::Bool  key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua_pop(hLua, 1);                 // ... [T] [key] [value]
		_SaveTableValue(hLua,table,key);
	}
	*/
	else if ( lua_isinteger(hLua, -1) )
	{
		lua::Int   key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua_pop(hLua, 1);                 // ... [T] [key] [value]
		_SaveTableValue(hLua,table,key);
	}
	else if ( lua_isnumber(hLua, -1) )
	{
		lua::Num   key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua_pop(hLua, 1);                 // ... [T] [key] [value]
		_SaveTableValue(hLua,table,key);
	}
	else// Just in case.
	{
		lua_pop(hLua, 1);                 // ... [T] [key] [value]
	}

	lua_pop(hLua, 1);                     // ... [T] [key]
}

inline void _VisitTable(lua::Handle hLua,lua::Table *table)
{
	                                    // ... [T]
	lua_pushnil(hLua);                  // ... [T] [nil]

	while ( lua_next(hLua, -2) != 0 )
	{
		                                // ... [T] [key] [value]
		/*
		 * I have to copy the key,
		 * because lua_isinteger may be modify key data.
		 * The modified key data will make lua_next crash.
		 */
		lua_pushvalue(hLua,-2);         // ... [T] [key] [value] [key]
		_SwitchTableKey(hLua,table);    // ... [T] [key]
	}

	// ... [T]
}

inline void CheckVarFromLua(lua::Handle hLua,lua::Table *table,int i)
{
	                                 // ...
	lua_pushvalue(hLua,i);           // ... [T]
	::lua::_VisitTable(hLua,table);  // ... [T]
	lua_pop(hLua, 1);                // ...
}

//------They only work for void CheckVarFromLua(lua::Handle,lua::Table*,int)------end

inline void PushVarToLua(lua::Handle hLua,lua::Var &t)
{
	if ( lua::VarType<lua::Str>(t) )
	{
		lua::Str   var = lua::VarCast<lua::Str>(t);
		PushVarToLua(hLua,var);
	}
	else if ( lua::VarType<lua::Num>(t) )
	{
		lua::Num   var = lua::VarCast<lua::Num>(t);
		PushVarToLua(hLua,var);
	}
	else if ( lua::VarType<lua::Int>(t) )
	{
		lua::Int   var = lua::VarCast<lua::Int>(t);
		PushVarToLua(hLua,var);
	}
	else if ( lua::VarType<lua::Bool>(t) )
	{
		lua::Bool  var = lua::VarCast<lua::Bool>(t);
		PushVarToLua(hLua,var);
	}
	else if ( lua::VarType<lua::Nil>(t) )
	{
		lua_pushnil(hLua);
	}
	else if ( lua::VarType<lua::Ptr>(t) )
	{
		lua::Ptr  var = lua::VarCast<lua::Ptr>(t);
		PushVarToLua(hLua,var);
	}
	else if ( lua::VarType<lua::Table>(t) )
	{
		lua::Table  var = lua::VarCast<lua::Table>(t);
		PushVarToLua(hLua,var);
	}
	else
	{
		printf("luapp:you push unknown data type\n");
		lua_pushnil(hLua);
	}
}

inline void CheckVarFromLua(lua::Handle hLua,lua::Var *t,int i)
{
	int   type = lua_type(hLua, i);

	if ( type==LUA_TSTRING )
	{
		lua::Str   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else if ( type==LUA_TBOOLEAN )
	{
		lua::Bool   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else if ( type==LUA_TNIL )
	{
		*t = lua::Var();
	}
	else if ( type==LUA_TNONE )
	{
		printf("luapp:No one know what type is it. That's new\n");
	}
	else if ( type==LUA_TLIGHTUSERDATA )
	{
		lua::Ptr   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else if ( type==LUA_TTABLE )
	{
		lua::Table   table;
		CheckVarFromLua(hLua,&table,i);
		*t = table;
	}
	else if ( lua_isinteger(hLua, i) )
	{
		lua::Int   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else if ( lua_isnumber(hLua, i) )
	{
		lua::Num   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else
	{
		printf("luapp:you get something luapp can't handle with\n");
		*t = lua::Var();
	}
}

//---------------------------PushVarToLua and CheckVarFromLua---------------------------end


}//namespace lua

#endif//_LUAPP_STANDARD_HPP_
