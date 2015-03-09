/**
@file   LuaState.hpp
@brief  Help lua and C++.
*/


#ifndef _LUAPP_STATE_HPP_
#define _LUAPP_STATE_HPP_

#include "LuaAdapter.hpp"
#include "LuaWrapper.hpp"
#include "LuaFunction.hpp"
#include "LuaFunctionExt.hpp"


namespace lua{


//-----------------ClassTypeFilter-----------------start
template<typename F>
struct ClassTypeFilter{};

template<typename R,typename C>
struct ClassTypeFilter<R (C::*)()>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1>
struct ClassTypeFilter<R (C::*)(A1)>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1,typename A2>
struct ClassTypeFilter<R (C::*)(A1,A2)>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1,typename A2,typename A3>
struct ClassTypeFilter<R (C::*)(A1,A2,A3)>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1,typename A2,typename A3,typename A4>
struct ClassTypeFilter<R (C::*)(A1,A2,A3,A4)>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1,typename A2,typename A3,typename A4,typename A5>
struct ClassTypeFilter<R (C::*)(A1,A2,A3,A4,A5)>
{
	typedef C ClassType;
};
//-----------------ClassTypeFilter-----------------end


class State
{
	public:

		State():hLua((lua::Handle)0)
		{}

		~State()
		{
			if(hLua)Drop();
		}

		/// Let lua script could use given class type.
		template<typename C>
		void RegisterClass(const char *class_name)
		{
			adapter::Adapter<C>::Register(hLua,class_name);
		}

		template<typename F>
		void RegisterMemberFunction(const char *func_name,F fn)
		{
			typedef typename ClassTypeFilter<F>::ClassType C;
			struct adapter::Adapter<C>::Pack     myF( Str(func_name),adapter::GetProxy(fn));
			adapter::Adapter<C>::mList.push_back(myF);
		}

		template<typename F>
		void RegisterFunction(const char *func_name,F fn)
		{
			wrapper::RegisterFunction(hLua,func_name,fn);
		}

		int Init()
		{
			hLua=lua::CreateHandle();
			lua::OpenLibs(hLua);
			return (int)1;
		}

		void Drop()
		{
			lua::DestroyHandle(hLua);
			hLua=(lua::Handle)0;
		}

		int DoScript(const char *str)
		{
			lua::DoScript(hLua,str);
			return (int)1;
		}

		int DoScript(lua::Str &str)
		{
			lua::DoScript(hLua,str.c_str());
			return (int)1;
		}

		void GetGlobal(lua::Int *t,const char *name)
		{
			lua::GetGlobal(hLua,name);
			*t=(lua::Int)lua::CheckInteger(hLua,-1);
			lua::Pop(hLua,1);
		}

		void GetGlobal(lua::Num *t,const char *name)
		{
			lua::GetGlobal(hLua,name);
			*t=(lua::Num)lua::CheckNumber(hLua,-1);
			lua::Pop(hLua,1);
		}

		void GetGlobal(lua::Str *t,const char *name)
		{
			lua::GetGlobal(hLua,name);
			*t=lua::CheckString(hLua,-1);
			lua::Pop(hLua,1);
		}

		template<typename F>
		void GetFunction(const char *name,lua::Function<F> *func)
		{
			func->hLua=hLua;
			func->mFuncName=name;
		}

		template<typename R,typename P>
		void GetFunction(const char *name,lua::FunctionExt<R,P> *func)
		{
			func->hLua=hLua;
			func->mFuncName=name;
		}

	private:

		lua::Handle      hLua;
};



}//namespace lua

#endif//_LUAPP_STATE_HPP_
