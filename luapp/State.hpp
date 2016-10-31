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

		State(lua::Handle h = (lua::Handle)0):_lua(h),_moduleMode(0)
		{
			if ( _lua )
			{
				_moduleMode = 1;
			}
		}

		~State()
		{
			if(_lua)Drop();
		}

		void RegisterNativeFunction(lua::Str name,lua::CFunction func)
		{
			if ( _moduleMode )
			{
				_funcReg.Add(name,func);
			}
			else
			{
				// I am not sure.
				lua::PushFunction(_lua, func);
				lua::SetGlobal(_lua, name.c_str());
			}
		}

		/// Let lua script could use given class type.
		template<typename C>
		void RegisterClass(lua::Str class_name)
		{
			if ( _moduleMode ) return; // Not support yet.
			adapter::Adapter<C,N>::Register(_lua,class_name);
		}

		/** Let lua script could use given class type.
		It have a faster constructor. But lua need to store more information.
		Call it after every each RegisterMemberFunction().*/
		template<typename C>
		void RegisterClassEx(lua::Str class_name)
		{
			if ( _moduleMode )
			{
				_funcReg.Add(class_name,adapter::Adapter<C,N>::GetConstructor(_lua,class_name));
			}
			else
			{
				adapter::Adapter<C,N>::RegisterEx(_lua,class_name);
			}
		}

		/// Let lua script could use given member function. You can't use it without RegisterClass() or RegisterClassEx().
		template<typename F>
		void RegisterMemberFunction(lua::Str func_name,F fn)
		{
			typedef typename ClassTypeFilter<F>::ClassType C;
			struct adapter::Adapter<C,N>::Pack     myF( func_name,adapter::GetProxy(fn));
			adapter::Adapter<C,N>::_list.push_back(myF);
		}

		/// Let lua script could use given global function.
		template<typename F>
		void RegisterFunction(lua::Str func_name,F fn)
		{
			if ( _moduleMode ) return; // Not support yet.
			wrapper::Wrapper<N>::RegisterFunction(_lua,func_name,fn);
		}

		/**
		Let lua script could use given member function.
		This member function will be look like a global function in lua.
		*/
		template<typename F,typename C>
		void RegisterFunction(lua::Str func_name,F fn,C *obj)
		{
			if ( _moduleMode ) return; // Not support yet.
			// Add class type checked here some times later.
			wrapper::Wrapper<N>::RegisterFunction(_lua,func_name,fn,obj);
		}

		int Init()
		{
			if ( _moduleMode ) return (int)0; // Why you did this? You already got a lua_State.

			if (_lua)   return (int)0; // You can only call Init() once.

			_lua=lua::CreateHandle();
			lua::OpenLibs(_lua);

			if(IsScriptPathExist())
			{
				AddScriptPathToLua(_path);
			}
			return (int)1;
		}

		void Drop()
		{
			if ( _moduleMode )
			{
				_funcReg.Refresh();
				lua::NewModule(_lua,_funcReg);
			}
			else
			{
				lua::DestroyHandle(_lua);
			}
			_lua=(lua::Handle)0;
		}

		lua::Str GetError()
		{
			return lua::GetError(_lua);
		}

		int DoScript(lua::Str str)
		{
			if ( _moduleMode ) return (int)0; // You can't do this. Because module mode didn't have its own script.

			if(IsScriptPathExist())
			{
				str=_path+str;
			}

			return lua::DoScript(_lua,str.c_str());
		}

		/// Tell luapp where to read main lua scripts.
		void AddMainPath(lua::Str path)
		{
			_path=path;
			_path+="/";
			if(_lua)
			{
				AddScriptPathToLua(_path);
			}
		}

		/// Tell luapp where to read more lua scripts.
		void AddSearchPath(lua::Str path)
		{
			path+="/";
			if(_lua)
			{
				AddScriptPathToLua(path);
			}
		}

		/// Set global variable to lua script. Don't try to send function.
		template<typename T>
		void SetGlobal(lua::Str name,T t)
		{
			PushVarToLua(_lua,t);
			lua::SetGlobal(_lua,name.c_str());
		}

		/// Get global variable from lua script.
		template<typename T>
		void GetGlobal(lua::Str name,T t)
		{
			lua::GetGlobal(_lua,name.c_str());
			CheckVarFromLua(_lua,t,-1);
			lua::Pop(_lua,1);
		}

		/// Get global function(only one return value).
		template<typename F>
		void GetFunction(const char *name,lua::Function<F> *func)
		{
			func->_lua=_lua;
			func->_funcName=name;
		}

		/// Get global function(more than one return value).
		template<typename R,typename P>
		void GetFunction(const char *name,lua::FunctionExt<R,P> *func)
		{
			func->_lua=_lua;
			func->_funcName=name;
		}

		/// Call global function that don't have return value.
		void Call(lua::Str name)
		{
			lua::GetGlobal(_lua,name.c_str());
			lua::PCall(_lua,0,0,0);
		}

		template<typename A1>
		void Call(lua::Str name,A1 a1)
		{
			lua::GetGlobal(_lua,name.c_str());
			lua::PushVarToLua(_lua,a1);
			lua::PCall(_lua,1,0,0);
		}

		template<typename A1,typename A2>
		void Call(lua::Str name,A1 a1,A2 a2)
		{
			lua::GetGlobal(_lua,name.c_str());
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PCall(_lua,2,0,0);
		}

		template<typename A1,typename A2,typename A3>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3)
		{
			lua::GetGlobal(_lua,name.c_str());
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PCall(_lua,3,0,0);
		}

		template<typename A1,typename A2,typename A3,typename A4>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4)
		{
			lua::GetGlobal(_lua,name.c_str());
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PushVarToLua(_lua,a4);
			lua::PCall(_lua,4,0,0);
		}

		template<typename A1,typename A2,typename A3,typename A4,typename A5>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5)
		{
			lua::GetGlobal(_lua,name.c_str());
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PushVarToLua(_lua,a4);
			lua::PushVarToLua(_lua,a5);
			lua::PCall(_lua,5,0,0);
		}

		template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6)
		{
			lua::GetGlobal(_lua,name.c_str());
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PushVarToLua(_lua,a4);
			lua::PushVarToLua(_lua,a5);
			lua::PushVarToLua(_lua,a6);
			lua::PCall(_lua,6,0,0);
		}

	private:

		void AddScriptPathToLua(lua::Str str)
		{
			lua::GetGlobal(_lua,"package");
			lua::GetField(_lua,-1, "path");
			lua::Str  path=lua::CheckString(_lua,-1);
			path=str+"?.lua;"+path;
			lua::Pop(_lua,1);
			lua::PushString(_lua,path);
			lua::SetField(_lua,-2, "path");
			lua::Pop(_lua,1);
		}

		int IsScriptPathExist()
		{
			return !_path.empty();
		}

		lua::Handle      _lua;
		lua::Str         _path;         // A path for search scripts.
		bool             _moduleMode;
		lua::FuncReg     _funcReg;      // Only work for module mode.
};



}//namespace lua

#endif//_LUAPP_STATE_HPP_
