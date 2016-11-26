
#pragma once

#include "luapp/Handle.hpp"
#include "luapp/Register.hpp"


namespace lua{

class Func
{
	public:

		Func(){}

	//	Func()(lua::Handle h,lua::Register::Item i):_lua(h),_item(i){}

		~Func()
		{
			_item = NULL;   // Just make sure it released before this->_lua.
		}

		void call()
		{
			if ( ! _lua ) lua::log::Cout<<"error:Func::void call()"<<lua::log::End;
			_item->getVar();         // ... [F]
			lua::PCall(_lua,0,0,0);  // ...
		}

		template<typename R>
		R call()
		{
			if ( ! _lua ) lua::log::Cout<<"error:Func::R call()"<<lua::log::End;
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
			if ( ! _lua ) lua::log::Cout<<"error:Func::void call(A1 a1)"<<lua::log::End;
			_item->getVar();
			lua::PushVarToLua(_lua,a1);
			lua::PCall(_lua,1,0,0);
		}

		template<typename R,typename A1>
		R call(A1 a1)
		{
			if ( ! _lua ) lua::log::Cout<<"error:Func::R call(A1 a1)"<<lua::log::End;
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
			if ( ! _lua ) lua::log::Cout<<"error:Func::void call(A1 a1, A2 a2)"<<lua::log::End;
			_item->getVar();
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PCall(_lua,2,0,0);
		}

		template<typename R,typename A1,typename A2>
		R call(A1 a1, A2 a2)
		{
			if ( ! _lua ) lua::log::Cout<<"error:Func::R call(A1 a1, A2 a2)"<<lua::log::End;
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
			if ( ! _lua ) lua::log::Cout<<"error:Func::void call(A1 a1, A2 a2, A3 a3)"<<lua::log::End;
			_item->getVar();
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PCall(_lua,3,0,0);
		}

		template<typename R,typename A1,typename A2,typename A3>
		R call(A1 a1, A2 a2, A3 a3)
		{
			if ( ! _lua ) lua::log::Cout<<"error:Func::R call(A1 a1, A2 a2, A3 a3)"<<lua::log::End;
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
			if ( _lua ) lua::log::Cout<<"warning:why you set handle of function again?"<<lua::log::End;
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
