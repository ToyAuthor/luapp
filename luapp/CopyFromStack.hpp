#pragma once

#include "luapp/LuaAPI.hpp"
#include "luapp/Table.hpp"

namespace lua{


//------------------------------------------------------------------------------
inline void CheckVarFromLua(lua::NativeState hLua,lua::Bool *t,int i)
{
	*t=(lua::Bool)lua::CheckBoolean(hLua,i);
}
//------------------------------------------------------------------------------
inline void CheckVarFromLua(lua::NativeState hLua,lua::Int *t,int i)
{
	*t=(lua::Int)lua::CheckInteger(hLua,i);
}
//------------------------------------------------------------------------------
inline void CheckVarFromLua(lua::NativeState hLua,lua::Num *t,int i)
{
	*t=(lua::Num)lua::CheckNumber(hLua,i);
}
//------------------------------------------------------------------------------
inline void CheckVarFromLua(lua::NativeState hLua,lua::Str *t,int i)
{
	*t=lua::CheckString(hLua,i);
}
//------------------------------------------------------------------------------
inline void CheckVarFromLua(lua::NativeState hLua,lua::Ptr *t,int i)
{
	*t=lua::CheckPointer(hLua,i);
}
//------------------------------------------------------------------------------
inline void _VisitTable(lua::NativeState hLua,lua::Table *table);
template<typename T>
inline void _SaveTableValue(lua::NativeState hLua,lua::Table *table,T key)
{
	// ... [value]

	int   type = lua::_GetTypeID(hLua, -1);

	if ( type==lua::TypeID<lua::Str>() )
	{
		lua::Str   _value;
		CheckVarFromLua(hLua,&_value,-1);
		lua::Var   value(_value);
		(*table)[key] = value;
	}
	else if ( type==lua::TypeID<lua::Table>() )
	{
		lua::Table   subTable;
		_VisitTable(hLua,&subTable);

		lua::Var   value = subTable;
		(*table)[key] = value;
	}
	// Just in case.
	else if ( type==lua::TypeID<lua::Nil>() )
	{
		// This element is not exist.
	}
	else if ( type==lua::_GetTypeNone() )
	{
		lua::Log<<"error:No one know what type is it"<<lua::End;
	}
	else if ( type==lua::_GetTypeLightUserData() )
	{
		lua::Ptr   value;
		CheckVarFromLua(hLua,&value,-1);
		(*table)[key] = value;
	}
	else if ( type==lua::TypeID<lua::Bool>() )
	{
		lua::Bool   value;
		CheckVarFromLua(hLua,&value,-1);
		(*table)[key] = value;
	}
	#ifndef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
	else if ( type==lua::TypeID<lua::Func>() )
	{
		lua::Func   value;
		(*table)[key] = value;
	}
	else if ( type==lua::TypeID<lua::Task>() )
	{
		lua::Task   value;
		(*table)[key] = value;
	}
	else if ( type==lua::_GetTypeUserData() )
	{
		lua::User   value;
		(*table)[key] = value;
	}
	#endif
	else if ( type==lua::TypeID<lua::Int>() )
	{
		lua::Int   value;
		CheckVarFromLua(hLua,&value,-1);
		(*table)[key] = value;
	}
	else if ( type==lua::TypeID<lua::Num>() )
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
//------------------------------------------------------------------------------
inline void _SwitchTableKey(lua::NativeState hLua,lua::Table *table)
{
	                                       // ... [T] [key] [value] [key]

	if ( lua::IsType<lua::Str>(hLua, -1) )
	{
		lua::Str   key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua::Pop(hLua, 1);                 // ... [T] [key] [value]
		lua::_SaveTableValue(hLua,table,key);
	}
	#ifdef _LUAPP_ENABLE_BOOLEAN_INDEX_OF_TABLE_
	else if ( lua::IsType<lua::Bool>(hLua, -1) )
	{
		lua::Bool  key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua::Pop(hLua, 1);                 // ... [T] [key] [value]
		lua::_SaveTableValue(hLua,table,key);
	}
	#endif
	else if ( lua::IsType<lua::Int>(hLua, -1) )
	{
		lua::Int   key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua::Pop(hLua, 1);                 // ... [T] [key] [value]
		lua::_SaveTableValue(hLua,table,key);
	}
	else if ( lua::IsType<lua::Num>(hLua, -1) )
	{
		lua::Num   key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua::Pop(hLua, 1);                 // ... [T] [key] [value]
		lua::_SaveTableValue(hLua,table,key);
	}
	else// Just in case.
	{
		lua::Pop(hLua, 1);                 // ... [T] [key] [value]
	}

	lua::Pop(hLua, 1);                     // ... [T] [key]
}
//------------------------------------------------------------------------------
inline void _VisitTable(lua::NativeState hLua,lua::Table *table)
{
	                                    // ... [T]
	lua::PushNil(hLua);                 // ... [T] [nil]

	while ( lua::_VisitTableNext(hLua, -2) )
	{
		                                     // ... [T] [key] [value]
		/*
		 * I have to copy the key,
		 * because lua_isinteger may be modify key data.
		 * The modified key data will make lua_next crash.
		 */
		lua::PushValue(hLua,-2);             // ... [T] [key] [value] [key]
		lua::_SwitchTableKey(hLua,table);    // ... [T] [key]
	}

	// ... [T]
}
//------------------------------------------------------------------------------
inline void CheckVarFromLua(lua::NativeState hLua,lua::Table *table,int i)
{
	                                 // ...
	lua::PushValue(hLua,i);          // ... [T]
	lua::_VisitTable(hLua,table);    // ... [T]
	lua::Pop(hLua, 1);               // ...
}
//------------------------------------------------------------------------------
inline void CheckVarFromLua(lua::NativeState hLua,lua::Var *t,int i)
{
	int   type = lua::_GetTypeID(hLua, i);

	if ( type==lua::TypeID<lua::Str>() )
	{
		lua::Str   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else if ( type==lua::TypeID<lua::Bool>() )
	{
		lua::Bool   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else if ( type==lua::TypeID<lua::Nil>() )
	{
		*t = lua::Var();
	}
	else if ( type==lua::_GetTypeNone() )
	{
		lua::Log<<"error:The type is none. Maybe you try to catch a variable that doesn't exist."<<lua::End;
	}
	else if ( type==lua::_GetTypeLightUserData() )
	{
		lua::Ptr   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else if ( type==lua::TypeID<lua::Table>() )
	{
		lua::Table   table;
		CheckVarFromLua(hLua,&table,i);
		*t = table;
	}
	#ifndef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
	else if ( type==lua::TypeID<lua::Func>() )
	{
		lua::Func   var;
		*t = var;
	}
	else if ( type==lua::TypeID<lua::Task>() )
	{
		lua::Task   var;
		*t = var;
	}
	else if ( type==lua::_GetTypeUserData() )
	{
		lua::User   var;
		*t = var;
	}
	#endif
	else if ( lua::IsType<lua::Int>(hLua, i) )
	{
		lua::Int   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else if ( lua::IsType<lua::Num>(hLua, i) )
	{
		lua::Num   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else
	{
		lua::Log<<"error:you get something luapp can't handle with"<<lua::End;
		*t = lua::Var();
	}
}
//------------------------------------------------------------------------------

}
