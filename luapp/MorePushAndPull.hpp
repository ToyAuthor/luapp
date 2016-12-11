#pragma once

#include "luapp/Map.hpp"
#include "luapp/Func.hpp"
#include "luapp/Task.hpp"
#include "luapp/User.hpp"

namespace lua{

//------------------------------------------------------------------------------

inline void CheckVarFromLua(lua::Handle h,lua::Map *t, int i)
{
	lua::PushValue(h,i);
	t->_set(h,h->_register->newItem());
	t->_getItem()->setVar();
}

inline void PushVarToLua(lua::Handle,lua::Map t)
{
	t._getItem()->getVar();
}

//------------------------------------------------------------------------------

inline void CheckVarFromLua(lua::Handle h,lua::Func *t, int i)
{
	lua::PushValue(h,i);
	t->_set(h,h->_register->newItem());
	t->_getItem()->setVar();
}

inline void PushVarToLua(lua::Handle,lua::Func t)
{
	t._getItem()->getVar();
}

//------------------------------------------------------------------------------

inline void CheckVarFromLua(lua::Handle h,lua::Task *t, int i)
{
	lua::PushValue(h,i);
	t->_set(h,h->_register->newItem());
	t->_getItem()->setVar();
}

inline void PushVarToLua(lua::Handle,lua::Task t)
{
	t._getItem()->getVar();
}

//------------------------------------------------------------------------------

inline void CheckVarFromLua(lua::Handle h,lua::User *t, int i)
{
	lua::PushValue(h,i);
	t->_set(h,h->_register->newItem());
	t->_getItem()->setVar();
}

inline void PushVarToLua(lua::Handle,lua::User t)
{
	t._getItem()->getVar();
}

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
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
		else if ( lua::VarType<lua::Map>(value) )
		{
			lua::Map    t_value = lua::VarCast<lua::Map>(value);
			t_value._getItem()->getVar();                             // ... [T] [key] [value]
		}
		else if ( lua::VarType<lua::Func>(value) )
		{
			lua::Func   t_value = lua::VarCast<lua::Func>(value);
			t_value._getItem()->getVar();                             // ... [T] [key] [value]
		}
		else if ( lua::VarType<lua::Task>(value) )
		{
			lua::Task   t_value = lua::VarCast<lua::Task>(value);
			t_value._getItem()->getVar();                             // ... [T] [key] [value]
		}
		else if ( lua::VarType<lua::Table>(value) )
		{
			lua::Table   t_value = lua::VarCast<lua::Table>(value);
			_PushValueToLuaTable(hLua,t_value);                       // ... [T] [key] [value]
		}
		else if ( lua::VarType<lua::User>(value) )
		{
			lua::User   t_value = lua::VarCast<lua::User>(value);
			t_value._getItem()->getVar();                             // ... [T] [key] [value]
		}
		else
		{
			lua::Pop(hLua, 1);           // ... [T]
			continue;
		}

		lua::SetTable(hLua,-3);      // ... [T]
	}

	// ... [T]
}
//------------------------------------------------------------------------------
inline void PushVarToLua(lua::Handle hLua,lua::Table &table)
{
	                                     // ...
	_PushValueToLuaTable(hLua,table);    // ... [T]
}
//------------------------------------------------------------------------------
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
		lua::PushNil(hLua);
	}
	else if ( lua::VarType<lua::Ptr>(t) )
	{
		lua::Ptr  var = lua::VarCast<lua::Ptr>(t);
		PushVarToLua(hLua,var);
	}
	else if ( lua::VarType<lua::Map>(t) )
	{
		lua::Map    var = lua::VarCast<lua::Map>(t);
		var._getItem()->getVar();
	}
	else if ( lua::VarType<lua::Func>(t) )
	{
		lua::Func   var = lua::VarCast<lua::Func>(t);
		var._getItem()->getVar();
	}
	else if ( lua::VarType<lua::Task>(t) )
	{
		lua::Task   var = lua::VarCast<lua::Task>(t);
		var._getItem()->getVar();
	}
	else if ( lua::VarType<lua::Table>(t) )
	{
		lua::Table  var = lua::VarCast<lua::Table>(t);
		PushVarToLua(hLua,var);
	}
	else if ( lua::VarType<lua::User>(t) )
	{
		lua::User   var = lua::VarCast<lua::User>(t);
		var._getItem()->getVar();
	}
	else
	{
		lua::log::Cout<<"luapp:you push unknown or unsupported data type"<<lua::log::End;
		lua::PushNil(hLua);
	}
}
//------------------------------------------------------------------------------















//------------------------------------------------------------------------------
inline void _VisitTable(lua::Handle hLua,lua::Table *table);
template<typename T>
inline void _SaveTableValue(lua::Handle hLua,lua::Table *table,T key)
{
	// ... [value]

	int   type = lua::TypeCast(hLua, -1);

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
		lua::log::Cout<<"luapp:No one know what type is it"<<lua::log::End;
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
	else if ( type==LUA_TFUNCTION )
	{
		lua::PushValue(hLua,-1);
		lua::Func   value;
		lua::Register::Item   item = hLua->_register->newItem();
		item->setVar();
		value._set(hLua,item);
		(*table)[key] = value;
	}
	else if ( type==LUA_TUSERDATA )
	{
		lua::PushValue(hLua,-1);
		lua::User   value;
		lua::Register::Item   item = hLua->_register->newItem();
		item->setVar();
		value._set(hLua,item);
		(*table)[key] = value;
	}
	else if ( type==LUA_TTHREAD )
	{
		lua::PushValue(hLua,-1);
		lua::Task   value;
		lua::Register::Item   item = hLua->_register->newItem();
		item->setVar();
		value._set(hLua,item);
		(*table)[key] = value;
	}
	else if ( lua_isinteger(hLua->_lua, -1) )
	{
		lua::Int   value;
		CheckVarFromLua(hLua,&value,-1);
		(*table)[key] = value;
	}
	else if ( lua_isnumber(hLua->_lua, -1) )
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
inline void _SwitchTableKey(lua::Handle hLua,lua::Table *table)
{
	                                      // ... [T] [key] [value] [key]

	if ( lua::TypeCast(hLua, -1)==LUA_TSTRING )
	{
		lua::Str   key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua::Pop(hLua, 1);                 // ... [T] [key] [value]
		_SaveTableValue(hLua,table,key);
	}
	/* Not implement yet. Maybe I will ignore it ever.
	else if ( lua::TypeCast(hLua, -1)==LUA_TBOOLEAN )
	{
		lua::Bool  key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua_pop(hLua, 1);                 // ... [T] [key] [value]
		_SaveTableValue(hLua,table,key);
	}
	*/
	else if ( lua_isinteger(hLua->_lua, -1) )
	{
		lua::Int   key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua::Pop(hLua, 1);                 // ... [T] [key] [value]
		_SaveTableValue(hLua,table,key);
	}
	else if ( lua_isnumber(hLua->_lua, -1) )
	{
		lua::Num   key;
		lua::CheckVarFromLua(hLua,&key,-1);
		lua::Pop(hLua, 1);                 // ... [T] [key] [value]
		_SaveTableValue(hLua,table,key);
	}
	else// Just in case.
	{
		lua::Pop(hLua, 1);                 // ... [T] [key] [value]
	}

	lua::Pop(hLua, 1);                     // ... [T] [key]
}
//------------------------------------------------------------------------------
inline void _VisitTable(lua::Handle hLua,lua::Table *table)
{
	                                    // ... [T]
	lua::PushNil(hLua);                 // ... [T] [nil]

	while ( lua_next(hLua->_lua, -2) != 0 )
	{
		                                // ... [T] [key] [value]
		/*
		 * I have to copy the key,
		 * because lua_isinteger may be modify key data.
		 * The modified key data will make lua_next crash.
		 */
		lua::PushValue(hLua,-2);        // ... [T] [key] [value] [key]
		_SwitchTableKey(hLua,table);    // ... [T] [key]
	}

	// ... [T]
}
//------------------------------------------------------------------------------
inline void CheckVarFromLua(lua::Handle hLua,lua::Table *table,int i)
{
	                                 // ...
	::lua::PushValue(hLua,i);        // ... [T]
	::lua::_VisitTable(hLua,table);  // ... [T]
	::lua::Pop(hLua, 1);             // ...
}
//------------------------------------------------------------------------------
inline void CheckVarFromLua(lua::Handle hLua,lua::Var *t,int i)
{
	int   type = lua::TypeCast(hLua, i);

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
		lua::log::Cout<<"luapp:No one know what type is it. That's new"<<lua::log::End;
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
	else if ( type==LUA_TFUNCTION )
	{
		lua::PushValue(hLua,-1);
		lua::Func   func;
		lua::Register::Item   item = hLua->_register->newItem();
		item->setVar();
		func._set(hLua,item);

		*t = func;
	}
	else if ( type==LUA_TUSERDATA )
	{
		lua::PushValue(hLua,-1);
		lua::User   func;
		lua::Register::Item   item = hLua->_register->newItem();
		item->setVar();
		func._set(hLua,item);

		*t = func;
	}
	else if ( type==LUA_TTHREAD )
	{
		lua::PushValue(hLua,-1);
		lua::Task   func;
		lua::Register::Item   item = hLua->_register->newItem();
		item->setVar();
		func._set(hLua,item);

		*t = func;
	}
	else if ( lua_isinteger(hLua->_lua, i) )
	{
		lua::Int   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else if ( lua_isnumber(hLua->_lua, i) )
	{
		lua::Num   var;
		CheckVarFromLua(hLua,&var,i);
		*t = var;
	}
	else
	{
		lua::log::Cout<<"luapp:you get something luapp can't handle with"<<lua::log::End;
		*t = lua::Var();
	}
}
//------------------------------------------------------------------------------

template<typename T>
lua::Var Map::operator >> (const T key)
{
	_item->getVar();                 // ... [T]
	lua::PushVarToLua(_lua,key);     // ... [T] [key]
	lua::GetTable(_lua,-2);          // ... [T] [value]

	lua::Var  var;
	lua::CheckVarFromLua(_lua,&var,-1);

	lua::Pop(_lua,2);                // ...

	return var;
}

template<typename T>
Map::_Value& Map::operator [] (const T key)
{
	_temp._level = 0;
	_item->getVar();                   // ... [T]

	if ( lua::TypeCast(_lua, -1)!=LUA_TTABLE )
	{
		lua::Pop(_lua,1);              // ...
		lua::PushNil(_lua);            // ... [nil]

		lua::log::Cout<<"error:lua::Map doesn't have a table."<<lua::log::End;
		_temp._level = 1;

		return _temp;
	}

	lua::PushVarToLua(_lua,key);       // ... [T] [key]
	_temp._level = 2;

	return _temp;
}

template<typename T>
Map::_Value& Map::_Value::operator [] (const T key)
{
	// ... [?] [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return *this;
	}

	// ... [T] [pre_key]

	lua::PushValue(_map->_lua,-1);  // ... [T] [pre_key] [pre_key]

	lua::GetTable(_map->_lua,-3);   // ... [T] [pre_key] [value]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TTABLE )
	{
		                                      // ... [T] [pre_key] [value]
		lua::PushVarToLua(_map->_lua,key);    // ... [T] [pre_key] [Table] [key]
	}
	else
	{
		lua::Pop(_map->_lua,1);               // ... [T] [pre_key]
		lua::PushValue(_map->_lua,-1);        // ... [T] [pre_key] [pre_key]
		lua::PushValue(_map->_lua,-1);        // ... [T] [pre_key] [pre_key] [pre_key]
		lua::NewTable(_map->_lua);            // ... [T] [pre_key] [pre_key] [pre_key] [Table]
		lua::SetTable(_map->_lua,-5);         // ... [T] [pre_key] [pre_key]
		lua::GetTable(_map->_lua,-3);         // ... [T] [pre_key] [Table]
		lua::PushVarToLua(_map->_lua,key);    // ... [T] [pre_key] [Table] [key]
	}

	this->_level+=2;

	return *this;
}

//---------------------Map::_Value::operator = ---------------------start

inline lua::Nil Map::_Value::operator = (lua::Nil value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::Str Map::_Value::operator = (lua::Str value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::Int Map::_Value::operator = (lua::Int value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::Num Map::_Value::operator = (lua::Num value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::Ptr Map::_Value::operator = (lua::Ptr value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::Var Map::_Value::operator = (lua::Var value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::Map Map::_Value::operator = (lua::Map value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::Bool Map::_Value::operator = (lua::Bool value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::Func Map::_Value::operator = (lua::Func value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::Task Map::_Value::operator = (lua::Task value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::User Map::_Value::operator = (lua::User value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

inline lua::Table Map::_Value::operator = (lua::Table value)
{
	// ... [?]

	if ( lua::TypeCast(_map->_lua, -1)==LUA_TNIL )
	{
		return value;
	}

	// ... [Table] [key]

	lua::PushVarToLua(_map->_lua,value);   // ... [Table] [key] [value]
	lua::SetTable(_map->_lua,-3);          // ... [Table]

	lua::Pop(_map->_lua,this->_level-1);
	this->_level = 0;

	return value;
}

//---------------------Map::_Value::operator = ---------------------

}//namespace lua
