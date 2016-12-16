
#pragma once

#include "luapp/Handle.hpp"
#include "luapp/Register.hpp"

namespace lua{

class Map
{
	public:

		struct _Value
		{
			_Value(Map *m):_map(m),_level(0){}
			~_Value(){}

			// They implemented at luapp/MorePushAndPull.hpp
			template<typename T>
			_Value& operator [] (const T key);
			lua::Nil operator = (lua::Nil value);
			lua::Str operator = (lua::Str value);
			lua::Int operator = (lua::Int value);
			lua::Num operator = (lua::Num value);
			lua::Ptr operator = (lua::Ptr value);
			lua::Var operator = (lua::Var value);
			lua::Map operator = (lua::Map value);
			lua::Bool operator = (lua::Bool value);
			lua::Func operator = (lua::Func value);
			lua::Task operator = (lua::Task value);
			lua::User operator = (lua::User value);
			lua::Table operator = (lua::Table value);

			Map   *_map;
			int   _level;
		};

		Map():_temp(this){}

		~Map()
		{
			_item = NULL;   // Just make sure it released before this->_lua.
		}

		// It implemented at luapp/MorePushAndPull.hpp
		template<typename T>
		lua::Var operator >> (const T key);

		// It implemented at luapp/MorePushAndPull.hpp
		template<typename T>
		_Value& operator [] (const T key);

		void _set(lua::Handle h,lua::Register::Item i)
		{
			if ( _lua ) lua::Log<<"warning:why you set handle of function again?"<<lua::End;
			_item = i;
			_lua = h;
		}

		lua::Register::Item _getItem()
		{
			return this->_item;
		}

	private:

		lua::Handle          _lua;
		lua::Register::Item  _item;
		_Value               _temp;
};

inline Var::Var(const lua::Map &t)
{
	this->_ptr = new ::lua::_VarType<lua::Map>(t);
}

inline Var& Var::operator = (const lua::Map &t)
{
	this->free_ptr();
	this->_ptr = new ::lua::_VarType<lua::Map>(t);
	return *this;
}


}
