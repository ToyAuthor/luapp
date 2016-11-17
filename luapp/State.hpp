/**
@file   State.hpp
@brief  The main interface of luapp.
*/


#ifndef _LUAPP_STATE_HPP_
#define _LUAPP_STATE_HPP_

#include "luapp/Adapter.hpp"
#include "luapp/Wrapper.hpp"
#include "luapp/Function.hpp"
#include "luapp/FunctionExt.hpp"
#include "luapp/Searcher.hpp"


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


/// The main interface of luapp.
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
			else
			{
				this->init();
			}
		}

		~State()
		{
			if(_lua)drop();
		}

		void bind(lua::Str name,lua::CFunction func)
		{
			if ( _moduleMode )
			{
				_funcReg.add(name,func);
			}
			else
			{
				lua::PushFunction(_lua, func);
				lua::SetGlobal(_lua, name);
			}
		}
		void RegisterNativeFunction(lua::Str name,lua::CFunction func)
		{
			bind(name,func);
		}

		/// Let lua script could use given class type.
		template<typename C>
		void bindClass(lua::Str class_name)
		{
			if ( _moduleMode )
			{
				_funcReg.add(class_name,adapter::Adapter<C,N>::getConstructor(_lua,class_name));
			}
			else
			{
				adapter::Adapter<C,N>::registerClass(_lua,class_name);
			}
		}
		template<typename C>
		void RegisterClass(lua::Str class_name)
		{
			bindClass<C>(class_name);
		}

		/**
		 * Let lua script could use given class type.
		 * It have a faster constructor. But lua need to store more information.
		 * Always call it after all bindMethod().
		 */
		template<typename C>
		void bindClassEx(lua::Str class_name)
		{
			if ( _moduleMode )
			{
				_funcReg.add(class_name,adapter::Adapter<C,N>::getConstructor2(_lua,class_name));
			}
			else
			{
				adapter::Adapter<C,N>::registerClassEx(_lua,class_name);
			}
		}
		template<typename C>
		void RegisterClassEx(lua::Str class_name)
		{
			bindClassEx<C>(class_name);
		}

		/**
		 * Let lua script could use given member function.
		 * Don't use it without bindClass() or bindClassEx().
		 */
		template<typename F>
		void bindMethod(lua::Str name,F fn)
		{
			typedef typename ClassTypeFilter<F>::ClassType C;
			struct adapter::Adapter<C,N>::Pack     myF( name,adapter::GetProxy(fn));
			adapter::Adapter<C,N>::pushPack(myF);
		}
		template<typename F>
		void RegisterMemberFunction(lua::Str name,F fn)
		{
			bindMethod(name,fn);
		}

		/// Let lua script could use given global function.
		template<typename F>
		void bind(lua::Str name,F fn)
		{
			if ( _moduleMode )
			{
				lua::log::Cout<<"error:bind(lua::Str name,F fn) not support module mode."<<lua::log::End;
				return;
			}

			wrapper::Wrapper<N>::registerFunction(_lua,name,fn);
		}
		template<typename F>
		void RegisterFunction(lua::Str name,F fn)
		{
			bind(name,fn);
		}

		/**
		 * Let lua script could use given member function.
		 * This member function will be looks like a global function in lua.
		 */
		template<typename F,typename C>
		void bind(lua::Str name,F fn,C *obj)
		{
			if ( _moduleMode )
			{
				printf("error:bind(lua::Str name,F fn,C *obj) not support module mode.\n");
				return;
			}

			// Add class type checked here some times later.
			wrapper::Wrapper<N>::registerFunction(_lua,name,fn,obj);
		}
		template<typename F,typename C>
		void RegisterFunction(lua::Str name,F fn,C *obj)
		{
			bind(name,fn,obj);
		}

		int init()
		{
			if ( _moduleMode )
			{
				printf("warning:you was chose another mode.\n");
				return (int)1;
			}

			if ( _lua )
			{
				printf("warning:you don't have to call init() by yourself.\n");
				return (int)1;
			}

			_lua=lua::CreateHandle();

			if ( ! _lua )
			{
				printf("error:can't get lua_State.\n");
				return (int)0;
			}

			lua::OpenLibs(_lua);

			if(is_script_path_exist())
			{
				add_script_path_to_lua(_path);
			}

			return (int)1;
		}
		int Init()
		{
			return this->init();
		}

		void drop()
		{
			if ( _moduleMode )
			{
				this->build_module();
			}
			else
			{
				lua::DestroyHandle(_lua);
			}
			_lua=(lua::Handle)0;
		}
		void Drop()
		{
			this->drop();
		}

		lua::Str GetError()
		{
			return this->error();
		}

		int load(lua::Str name,lua::Str& code)
		{
			int result = lua::LoadScript(_lua,name,code);

			if ( ! result )
			{
				printf("%s\n",this->error().c_str());
			}

			return result;
		}

		int load(lua::Str filename)
		{
			int result = lua::LoadScript(_lua,filename);

			if ( ! result )
			{
				printf("%s\n",this->error().c_str());
			}

			return result;
		}

		int run()
		{
			if ( _moduleMode )
			{
				printf("error:You can't do this. Because module mode didn't run its own script.\n");
				return (int)0;
			}

			if ( lua::PCall(_lua,0,0,0) )
			{
				return 0;
			}

			return 1;
		}

		int run(lua::Str name,lua::Str& code,lua::Str& (*loader)(lua::Str))
		{
			if ( _moduleMode )
			{
				printf("error:You can't do this. Because module mode didn't run its own script.\n");
				return (int)0;
			}

			if ( loader )
			{
				this->searcher(loader);
			}

			int result = lua::DoScript(_lua,name,code);

			if ( ! result )
			{
				printf("%s\n",this->error().c_str());
			}

			return result;
		}

		int run(lua::Str str)
		{
			if ( _moduleMode )
			{
				printf("error:You can't do this. Because module mode didn't run its own script.\n");
				return (int)0;
			}

			if(is_script_path_exist())
			{
				str=_path+str;
			}

			int result = lua::DoScript(_lua,str);

			if ( ! result )
			{
				printf("%s\n",this->error().c_str());
			}

			return result;
		}
		int DoScript(lua::Str str)
		{
			return this->run(str);
		}

		int run(lua::Str path,lua::Str script)
		{
			this->path(path);
			return this->run(path+"/"+script);
		}

		/// Tell luapp where to read main lua scripts.
		// Remove it in next version.
		void project(lua::Str path)
		{
			_path=path;
			_path+="/";
			if(_lua)
			{
				add_script_path_to_lua(_path);
			}
		}
		void AddMainPath(lua::Str path)
		{
			this->project(path);
		}

		/// Let luapp know where to read more lua scripts.
		void path(lua::Str path)
		{
			if(_lua)
			{
				path+="/";
				add_script_path_to_lua(path);
			}
		}
		void AddSearchPath(lua::Str path)
		{
			this->path(path);
		}

		/// Set global variable to lua script. Don't try to send function.
		template<typename T>
		void setGlobal(lua::Str name,T t)
		{
			PushVarToLua(_lua,t);
			lua::SetGlobal(_lua,name);
		}
		template<typename T>
		void SetGlobal(lua::Str name,T t)
		{
			this->setGlobal(name,t);
		}

		/// Get global variable from lua script.
		template<typename T>
		void getGlobal(lua::Str name,T t)
		{
			lua::GetGlobal(_lua,name);
			CheckVarFromLua(_lua,t,-1);
			lua::Pop(_lua,1);
		}
		template<typename T>
		void GetGlobal(lua::Str name,T t)
		{
			this->getGlobal(name,t);
		}

		/// Get global function(one or no return value).
		template<typename F>
		void getFunc(const char *name,lua::Function<F> *func)
		{
			func->_lua=_lua;
			func->_funcName=name;
		}
		template<typename F>
		void GetFunction(const char *name,lua::Function<F> *func)
		{
			this->getFunc(name,func);
		}

		/// Get global function(more than one return value).
		template<typename R,typename P>
		void getFunc(const char *name,lua::FunctionExt<R,P> *func)
		{
			func->_lua=_lua;
			func->_funcName=name;
		}
		template<typename R,typename P>
		void GetFunction(const char *name,lua::FunctionExt<R,P> *func)
		{
			this->getFunc(name,func);
		}

		/// Call global function that don't have return value.
		void call(lua::Str name)
		{
			lua::GetGlobal(_lua,name);
			lua::PCall(_lua,0,0,0);
		}
		void Call(lua::Str name)
		{
			this->call(name);
		}

		template<typename A1>
		void call(lua::Str name,A1 a1)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PCall(_lua,1,0,0);
		}
		template<typename A1>
		void Call(lua::Str name,A1 a1)
		{
			this->call(name,a1);
		}

		template<typename A1,typename A2>
		void call(lua::Str name,A1 a1,A2 a2)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PCall(_lua,2,0,0);
		}
		template<typename A1,typename A2>
		void Call(lua::Str name,A1 a1,A2 a2)
		{
			this->call(name,a1,a2);
		}

		template<typename A1,typename A2,typename A3>
		void call(lua::Str name,A1 a1,A2 a2,A3 a3)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PCall(_lua,3,0,0);
		}
		template<typename A1,typename A2,typename A3>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3)
		{
			this->call(name,a1,a2,a3);
		}

		template<typename A1,typename A2,typename A3,typename A4>
		void call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PushVarToLua(_lua,a4);
			lua::PCall(_lua,4,0,0);
		}
		template<typename A1,typename A2,typename A3,typename A4>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4)
		{
			this->call(name,a1,a2,a3,a4);
		}

		template<typename A1,typename A2,typename A3,typename A4,typename A5>
		void call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PushVarToLua(_lua,a4);
			lua::PushVarToLua(_lua,a5);
			lua::PCall(_lua,5,0,0);
		}
		template<typename A1,typename A2,typename A3,typename A4,typename A5>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5)
		{
			this->call(name,a1,a2,a3,a4,a5);
		}

		template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
		void call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PushVarToLua(_lua,a4);
			lua::PushVarToLua(_lua,a5);
			lua::PushVarToLua(_lua,a6);
			lua::PCall(_lua,6,0,0);
		}
		template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
		void Call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6)
		{
			this->call(name,a1,a2,a3,a4,a5,a6);
		}

	//	void searcher(std::function<lua::Str&(lua::Str)> loader)
		void searcher(lua::Str& (*loader)(lua::Str))
		{
			Searcher<N>::setup(_lua,loader);
		}

	private:

		void add_script_path_to_lua(lua::Str str)
		{
			                                 // ...
			lua::GetGlobal(_lua,"package");  // ... package
			lua::GetField(_lua,-1, "path");  // ... package path
			lua::PushString(_lua,str+"?.lua;"+lua::CheckString(_lua,-1));
			                                 // ... package path new_path
			lua::SetField(_lua,-3, "path");  // ... package path
			lua::Pop(_lua,2);                // ...
		}

		void build_module()
		{
			_funcReg.refresh();
			lua::NewModule(_lua,_funcReg);
		}

		lua::Str error()
		{
			lua::Var  var;
			lua::CheckVarFromLua(_lua,&var,-1);

			lua::Str  str("error message not found");

			if ( lua::VarType<lua::Str>(var) )
			{
				str = lua::VarCast<lua::Str>(var);
			//	lua::Pop(_lua,-1);    I can't make sure it is error message.
			}

			return str;
		}

		int is_script_path_exist()
		{
			return !_path.empty();
		}

		lua::Handle      _lua;
		lua::Str         _path;         // Remove it in next version.
		bool             _moduleMode;
		lua::FuncReg     _funcReg;      // Only work for module mode.
};



}//namespace lua

#endif//_LUAPP_STATE_HPP_
