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

		void call()
		{
			if ( ! _lua ) lua::Log<<"error:Func::void call()"<<lua::log::End;
			_item->getVar();         // ... [F]
			lua::PCall(_lua,0,0,0);  // ...
		}

		template<typename R>
		R call()
		{
			if ( ! _lua ) lua::Log<<"error:Func::R call()"<<lua::log::End;
			_item->getVar();         // ... [F]
			lua::PCall(_lua,0,1,0);  // ... [R]
			R   result;
			lua::CheckVarFromLua(_lua,&result,-1);
			lua::Pop(_lua,1);
			return result;
		}

		template<typename A1>
		void call(A1 a1)
		{
			if ( ! _lua ) lua::Log<<"error:Func::void call(A1 a1)"<<lua::log::End;
			_item->getVar();
			lua::PushVarToLua(_lua,a1);
			lua::PCall(_lua,1,0,0);
		}

		template<typename R,typename A1>
		R call(A1 a1)
		{
			if ( ! _lua ) lua::Log<<"error:Func::R call(A1 a1)"<<lua::log::End;
			_item->getVar();
			lua::PushVarToLua(_lua,a1);
			lua::PCall(_lua,1,1,0);
			R   result;
			lua::CheckVarFromLua(_lua,&result,-1);
			lua::Pop(_lua,1);
			return result;
		}

		template<typename A1,typename A2>
		void call(A1 a1, A2 a2)
		{
			if ( ! _lua ) lua::Log<<"error:Func::void call(A1 a1, A2 a2)"<<lua::log::End;
			_item->getVar();
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PCall(_lua,2,0,0);
		}

		template<typename R,typename A1,typename A2>
		R call(A1 a1, A2 a2)
		{
			if ( ! _lua ) lua::Log<<"error:Func::R call(A1 a1, A2 a2)"<<lua::log::End;
			_item->getVar();
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PCall(_lua,2,1,0);
			R   result;
			lua::CheckVarFromLua(_lua,&result,-1);
			lua::Pop(_lua,1);
			return result;
		}

		template<typename A1,typename A2,typename A3>
		void call(A1 a1, A2 a2, A3 a3)
		{
			if ( ! _lua ) lua::Log<<"error:Func::void call(A1 a1, A2 a2, A3 a3)"<<lua::log::End;
			_item->getVar();
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PCall(_lua,3,0,0);
		}

		template<typename R,typename A1,typename A2,typename A3>
		R call(A1 a1, A2 a2, A3 a3)
		{
			if ( ! _lua ) lua::Log<<"error:Func::R call(A1 a1, A2 a2, A3 a3)"<<lua::log::End;
			_item->getVar();
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PCall(_lua,3,1,0);
			R   result;
			lua::CheckVarFromLua(_lua,&result,-1);
			lua::Pop(_lua,1);
			return result;
		}

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

//------------------------------------------------------------------------------

template<typename T> struct Closure{};

//------------------------------------------------------------------------------

template<typename R, typename P1>
struct Closure<R(P1)>
{
	public:

		Closure(const Func &f):_func(f){}
		~Closure(){}

		R operator()(P1 p1)
		{
			return _func.call<R,P1>(p1);
		}

	private:

		lua::Func   _func;
};

template<typename P1>
struct Closure<void(P1)>
{
	public:

		Closure(const Func &f):_func(f){}
		~Closure(){}

		void operator()(P1 p1)
		{
			_func.call(p1);
		}

	private:

		lua::Func   _func;
};

//------------------------------------------------------------------------------

template<typename R, typename P1, typename P2>
struct Closure<R(P1,P2)>
{
	public:

		Closure(const Func &f):_func(f){}
		~Closure(){}

		R operator()(P1 p1,P2 p2)
		{
			return _func.call<R,P1,P2>(p1,p2);
		}

	private:

		lua::Func   _func;
};

template<typename P1, typename P2>
struct Closure<void(P1,P2)>
{
	public:

		Closure(const Func &f):_func(f){}
		~Closure(){}

		void operator()(P1 p1,P2 p2)
		{
			_func.call(p1,p2);
		}

	private:

		lua::Func   _func;
};

//------------------------------------------------------------------------------

template<typename R, typename P1, typename P2, typename P3>
struct Closure<R(P1,P2,P3)>
{
	public:

		Closure(const Func &f):_func(f){}
		~Closure(){}

		R operator()(P1 p1,P2 p2,P3 p3)
		{
			return _func.call<R,P1,P2,P3>(p1,p2,p3);
		}

	private:

		lua::Func   _func;
};

template<typename P1, typename P2, typename P3>
struct Closure<void(P1,P2,P3)>
{
	public:

		Closure(const Func &f):_func(f){}
		~Closure(){}

		void operator()(P1 p1,P2 p2,P3 p3)
		{
			_func.call(p1,p2,p3);
		}

	private:

		lua::Func   _func;
};

//------------------------------------------------------------------------------

template<typename R, typename P1, typename P2, typename P3, typename P4>
struct Closure<R(P1,P2,P3,P4)>
{
	public:

		Closure(const Func &f):_func(f){}
		~Closure(){}

		R operator()(P1 p1,P2 p2,P3 p3,P4 p4)
		{
			return _func.call<R,P1,P2,P3,P4>(p1,p2,p3,p4);
		}

	private:

		lua::Func   _func;
};

template<typename P1, typename P2, typename P3, typename P4>
struct Closure<void(P1,P2,P3,P4)>
{
	public:

		Closure(const Func &f):_func(f){}
		~Closure(){}

		void operator()(P1 p1,P2 p2,P3 p3,P4 p4)
		{
			_func.call(p1,p2,p3,p4);
		}

	private:

		lua::Func   _func;
};

//------------------------------------------------------------------------------

}
