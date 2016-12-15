/**
 * @file   Func.cpp
 * @brief  A functor could work on C++ and lua.
 */

#pragma once

#include "luapp/Handle.hpp"
#include "luapp/Register.hpp"


namespace lua{

class Func
{
	public:

		Func(){}

		~Func()
		{
			_item = NULL;   // Just make sure it released before this->_lua.
		}

		void call();

		template<typename R>
		R call();

		template<typename A1>
		void call(A1 a1);

		template<typename R,typename A1>
		R call(A1 a1);

		template<typename A1,typename A2>
		void call(A1 a1, A2 a2);

		template<typename R,typename A1,typename A2>
		R call(A1 a1, A2 a2);

		template<typename A1,typename A2,typename A3>
		void call(A1 a1, A2 a2, A3 a3);

		template<typename R,typename A1,typename A2,typename A3>
		R call(A1 a1, A2 a2, A3 a3);

		void _set(lua::Handle h,lua::Register::Item i)
		{
			if ( _lua ) lua::Log<<"warning:why you set handle of function again?"<<lua::log::End;
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

};

inline Var::Var(const lua::Func &t)
{
	this->_ptr = new ::lua::_VarType<lua::Func>(t);
}

inline Var& Var::operator = (const lua::Func &t)
{
	this->free_ptr();
	this->_ptr = new ::lua::_VarType<lua::Func>(t);
	return *this;
}

}
