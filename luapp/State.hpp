/**
@file   State.hpp
@brief  Help lua and C++.
*/


#ifndef _LUAPP_STATE_HPP_
#define _LUAPP_STATE_HPP_

#include "luapp/Adapter.hpp"
#include "luapp/Wrapper.hpp"
#include "luapp/Function.hpp"
#include "luapp/FunctionExt.hpp"


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

		State(lua::Handle h = (lua::Handle)0):hLua(h),mIsModuleMode(0)
		{
			if ( hLua )
			{
				mIsModuleMode = 1;
			}
		}

		~State()
		{
			if(hLua)Drop();
		}

		void RegisterNativeFunction(lua::Str name,lua::CFunction func)
		{
			if ( mIsModuleMode )
			{
				mFuncReg.Add(name,func);
			}
			else
			{
				// I am not sure.
				lua::PushFunction(hLua, func);
				lua::SetGlobal(hLua, name.c_str());
			}
		}

		/// Let lua script could use given class type.
		template<typename C>
		void RegisterClass(lua::Str class_name)
		{
			if ( mIsModuleMode ) return; // Not support yet.
			adapter::Adapter<C,N>::Register(hLua,class_name);
		}

		/** Let lua script could use given class type.
		It have a faster constructor. But lua need to store more information.
		Call it after every each RegisterMemberFunction().*/
		template<typename C>
		void RegisterClassEx(lua::Str class_name)
		{
			if ( mIsModuleMode )
			{
				mFuncReg.Add(class_name,adapter::Adapter<C,N>::GetConstructor(hLua,class_name));
			}
			else
			{
				adapter::Adapter<C,N>::RegisterEx(hLua,class_name);
			}
		}

		/// Let lua script could use given member function. You can't use it without RegisterClass() or RegisterClassEx().
		template<typename F>
		void RegisterMemberFunction(lua::Str func_name,F fn)
		{
			typedef typename ClassTypeFilter<F>::ClassType C;
			struct adapter::Adapter<C,N>::Pack     myF( func_name,adapter::GetProxy(fn));
			adapter::Adapter<C,N>::mList.push_back(myF);
		}

		/// Let lua script could use given global function.
		template<typename F>
		void RegisterFunction(lua::Str func_name,F fn)
		{
			if ( mIsModuleMode ) return; // Not support yet.
			wrapper::Wrapper<N>::RegisterFunction(hLua,func_name,fn);
		}

		/**
		Let lua script could use given member function.
		This member function will be look like a global function in lua.
		*/
		template<typename F,typename C>
		void RegisterFunction(lua::Str func_name,F fn,C *obj)
		{
			if ( mIsModuleMode ) return; // Not support yet.
			// Add class type checked here some times later.
			wrapper::Wrapper<N>::RegisterFunction(hLua,func_name,fn,obj);
		}

		int Init()
		{
			if ( mIsModuleMode ) return (int)0; // Why you did this? You already got a lua_State.

			if (hLua)   return (int)0; // You can only call Init() once.

			hLua=lua::CreateHandle();
			lua::OpenLibs(hLua);

			if(IsScriptPathExist())
			{
				AddScriptPathToLua(mScriptPath);
			}
			return (int)1;
		}

		void Drop()
		{
			if ( mIsModuleMode )
			{
				lua::NewModule(hLua,mFuncReg);
			}
			else
			{
				lua::DestroyHandle(hLua);
			}
			hLua=(lua::Handle)0;
		}

		lua::Str GetError()
		{
			return lua::GetError(hLua);
		}

		int DoScript(lua::Str str)
		{
			if ( mIsModuleMode ) return (int)0; // You can't do this. Because module mode didn't have its own script.

			if(IsScriptPathExist())
			{
				str=mScriptPath+str;
			}

			return lua::DoScript(hLua,str.c_str());
		}

		/// Tell luapp where to read main lua scripts.
		void AddMainPath(lua::Str path)
		{
			mScriptPath=path;
			mScriptPath+="/";
			if(hLua)
			{
				AddScriptPathToLua(mScriptPath);
			}
		}

		/// Tell luapp where to read more lua scripts.
		void AddSearchPath(lua::Str path)
		{
			path+="/";
			if(hLua)
			{
				AddScriptPathToLua(path);
			}
		}

		/// Set global variable to lua script. Don't try to send function.
		template<typename T>
		void SetGlobal(lua::Str name,T t)
		{
			PushVarToLua(hLua,t);
			lua::SetGlobal(hLua,name.c_str());
		}

		/// Get global variable from lua script.
		template<typename T>
		void GetGlobal(lua::Str name,T t)
		{
			lua::GetGlobal(hLua,name.c_str());
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

		/// Call global function that don't have return value.
		void Call(lua::Str name)
		{
			lua::GetGlobal(hLua,name.c_str());
			lua::PCall(hLua,0,0,0);
		}

		template<typename A1>
		void Call(lua::Str name,A1 a1)
		{
			lua::GetGlobal(hLua,name.c_str());
			lua::PushVarToLua(hLua,a1);
			lua::PCall(hLua,1,0,0);
		}

		template<typename A1,typename A2>
		void Call(lua::Str name,A1 a1,A2 a2)
		{
			lua::GetGlobal(hLua,name.c_str());
			lua::PushVarToLua(hLua,a1);
			lua::PushVarToLua(hLua,a2);
			lua::PCall(hLua,2,0,0);
		}

		template<typename A1,typename A2,typename A3>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3)
		{
			lua::GetGlobal(hLua,name.c_str());
			lua::PushVarToLua(hLua,a1);
			lua::PushVarToLua(hLua,a2);
			lua::PushVarToLua(hLua,a3);
			lua::PCall(hLua,3,0,0);
		}

		template<typename A1,typename A2,typename A3,typename A4>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4)
		{
			lua::GetGlobal(hLua,name.c_str());
			lua::PushVarToLua(hLua,a1);
			lua::PushVarToLua(hLua,a2);
			lua::PushVarToLua(hLua,a3);
			lua::PushVarToLua(hLua,a4);
			lua::PCall(hLua,4,0,0);
		}

		template<typename A1,typename A2,typename A3,typename A4,typename A5>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5)
		{
			lua::GetGlobal(hLua,name.c_str());
			lua::PushVarToLua(hLua,a1);
			lua::PushVarToLua(hLua,a2);
			lua::PushVarToLua(hLua,a3);
			lua::PushVarToLua(hLua,a4);
			lua::PushVarToLua(hLua,a5);
			lua::PCall(hLua,5,0,0);
		}

		template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6)
		{
			lua::GetGlobal(hLua,name.c_str());
			lua::PushVarToLua(hLua,a1);
			lua::PushVarToLua(hLua,a2);
			lua::PushVarToLua(hLua,a3);
			lua::PushVarToLua(hLua,a4);
			lua::PushVarToLua(hLua,a5);
			lua::PushVarToLua(hLua,a6);
			lua::PCall(hLua,6,0,0);
		}

	private:

		void AddScriptPathToLua(lua::Str str)
		{
			lua::GetGlobal(hLua,"package");
			lua::GetField(hLua,-1, "path");
			lua::Str  path=lua::CheckString(hLua,-1);
			path=str+"?.lua;"+path;
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
		bool             mIsModuleMode;
		lua::FuncReg     mFuncReg;
};



}//namespace lua

#endif//_LUAPP_STATE_HPP_
