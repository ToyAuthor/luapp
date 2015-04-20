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
template<typename R,typename C,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct ClassTypeFilter<R (C::*)(A1,A2,A3,A4,A5,A6)>
{
	typedef C ClassType;
};
//-----------------ClassTypeFilter-----------------end


template<int N=0>
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
			adapter::Adapter<C,N>::Register(hLua,class_name);
		}

		/// Let lua script could use given member function. You can't use it without RegisterClass().
		template<typename F>
		void RegisterMemberFunction(const char *func_name,F fn)
		{
			typedef typename ClassTypeFilter<F>::ClassType C;
			struct adapter::Adapter<C,N>::Pack     myF( Str(func_name),adapter::GetProxy(fn));
			adapter::Adapter<C,N>::mList.push_back(myF);
		}

		/// Let lua script could use given global function.
		template<typename F>
		void RegisterFunction(const char *func_name,F fn)
		{
			wrapper::Wrapper<N>::RegisterFunction(hLua,func_name,fn);
		}

		/**
		Let lua script could use given member function.
		The member function will be look like a global function in lua.
		*/
		template<typename F,typename C>
		void RegisterFunction(const char *func_name,F fn,C *obj)
		{
			// check class type here
			wrapper::Wrapper<N>::RegisterFunction(hLua,func_name,fn,obj);
		}

		int Init()
		{
			hLua=lua::CreateHandle();
			lua::OpenLibs(hLua);

			if(IsScriptPathExist())
			{
				AddScriptPathToLua();
			}
			return (int)1;
		}

		void Drop()
		{
			lua::DestroyHandle(hLua);
			hLua=(lua::Handle)0;
		}

		int DoScript(lua::Str str)
		{
			if(IsScriptPathExist())
			{
				str=mScriptPath+str;
				lua::DoScript(hLua,str.c_str());
			}
			else
				lua::DoScript(hLua,str.c_str());

			return (int)1;
		}

		int DoScript(const char *str)
		{
			return DoScript(lua::Str(str));
		}

		/// Tell luapp where to read those lua scripts.
		void AddSearchPath(const char *path)
		{
			mScriptPath=path;
			mScriptPath+="/";
			if(hLua)
			{
				AddScriptPathToLua();
			}
		}

		/// Set global variable to lua script. Don't try to send function.
		template<typename T>
		void SetGlobal(T t,const char *name)
		{
			PushVarToLua(hLua,t);
			lua::SetGlobal(hLua,name);
		//	lua::Pop(hLua,1);
		}

		/// Get global variable from lua script.
		template<typename T>
		void GetGlobal(T *t,const char *name)
		{
			lua::GetGlobal(hLua,name);
			CheckVarFromLua(hLua,t,-1);
			lua::Pop(hLua,1);
		}

		/// Get global function(only one return value).
		template<typename F>
		void GetFunction(const char *name,lua::Function<F> *func)
		{
			func->hLua=hLua;
			func->mFuncName=name;
		}

		/// Get global function(more than one return value).
		template<typename R,typename P>
		void GetFunction(const char *name,lua::FunctionExt<R,P> *func)
		{
			func->hLua=hLua;
			func->mFuncName=name;
		}

		void Call(lua::Str name)
		{
			Call(name.c_str());
		}

		/// Calling function only for "void(void)".
		void Call(const char *name)
		{
			lua::GetGlobal(hLua,name);
			lua::PCall(hLua,0,0,0);
		}

	private:

		void AddScriptPathToLua()
		{
			lua::GetGlobal(hLua,"package");
			lua::GetField(hLua,-1, "path");
			lua::Str  path=lua::CheckString(hLua,-1);
			path=mScriptPath+"?.lua;"+path;
			lua::Pop(hLua,1);
			lua::PushString(hLua,path);
			lua::SetField(hLua,-2, "path");
			lua::Pop(hLua,1);
		}

		int IsScriptPathExist()
		{
			return !mScriptPath.empty();
		}

		lua::Handle      hLua;
		lua::Str         mScriptPath;
};



}//namespace lua

#endif//_LUAPP_STATE_HPP_
