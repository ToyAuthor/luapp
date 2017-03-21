/**
 * @file   Adapter.hpp
 * @brief  Help lua and C++.
 */

#pragma once

#include "luapp/AdapterProxy.hpp"


namespace lua{
namespace adapter{



template<typename C,int N>
class Adapter
{
	public:

		struct Pack
		{
			Pack():_proxy(0){}
			Pack(Str name,Proxy<C> *param):_name(name),_proxy(param){}

			Str            _name;
			Proxy<C>*      _proxy;
		};

		// It's a general way to register class.
		static void registerClass(lua::Handle L,lua::Str& className)
		{
			set_class_name(className);                         // ...

			//--------Setup a global function to lua--------
			lua::PushFunction(L, &Adapter<C,N>::constructor);  // ... [F]
			lua::SetGlobal(L, _className);                     // ...

			buildMetaTableForUserdata(L);
		}

		// Call it after every member function was registed at _list[].
		static void registerClassEx(lua::Handle L,lua::Str& className)
		{
			set_class_name(className);                         // ...

			//--------Setup a global function to lua--------
			lua::PushFunction(L, &Adapter<C,N>::constructorEx);// ... [F]
			lua::SetGlobal(L, _className);                     // ...

			buildMetaTableForUserdata(L);
			buildMetaTableForMemberFunction(L);
		}

		static lua::CFunction getConstructor(lua::Handle L,lua::Str& className)
		{
			set_class_name(className);
			buildMetaTableForUserdata(L);
			return &Adapter<C,N>::constructor;
		}

		static lua::CFunction getConstructorEx(lua::Handle L,lua::Str& className)
		{
			set_class_name(className);

			buildMetaTableForUserdata(L);
			buildMetaTableForMemberFunction(L);

			return &Adapter<C,N>::constructorEx;
		}

		static void pushPack(struct Pack pak)
		{
			Adapter<C,N>::_list.push_back(pak);
		}

		#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
		#ifdef _LUAPP_CLEAN_LUA_HANDLE_
		static void cleanPtr()
		{
			Adapter<C,N>::_lua = NULL;
		}
		#endif
		static lua::Handle _lua;
		#endif

	private:

		class PackList : public std::vector<struct Pack>
		{
			public:

				~PackList()
				{
					for(int i =this->size()-1;i>=0;i--)
					{
						delete (*this)[i]._proxy;
					}
				}
		};

		static Str         _className;
		static Str         _classNameUD;   // For user data.
	//	static Str         _classNameMT;   // For meta table.    Maybe I need this!
		static PackList    _list;

		static void buildMetaTableForUserdata(lua::Handle L)
		{
			lua::NewMetaTable(L, _classNameUD);                // ... [T]
			lua::PushString(L, "__gc");                        // ... [T] ["__gc"]
			lua::PushFunction(L, &Adapter<C,N>::gc_obj);       // ... [T] ["__gc"] [F]
			lua::SetTable(L, -3);                              // ... [T]
			lua::Pop(L,1);                                     // ...
		}

		static void buildMetaTableForMemberFunction(lua::Handle L)
		{
			lua::NewMetaTable(L, _className);                  // ... [T]
			lua::PushString(L, "__index");                     // ... [T] ["__index"]
			lua::PushValue(L,-2);                              // ... [T] ["__index"] [T]
			lua::SetTable(L,-3);                               // ... [T]

			/*
			visit( every element of _list[] )
			{
				... [T] [member func name]
				... [T] [member func name] [member func ID]
				... [T] [member func name] [closure]
				... [T]
			}
			*/
			for (int i = Adapter<C,N>::_list.size()-1; i>=0; i--)
			{
				lua::PushString(L, Adapter<C,N>::_list[i]._name);
				lua::PushInteger(L, i);
				lua::PushClosure(L, &Adapter<C,N>::thunk, 1);
				lua::SetTable(L, -3);
			}

			lua::Pop(L,1);                                     // ...
		}

		// As destructor.
		static int gc_obj(lua::NativeState L)
		{
			C** obj = static_cast<C**>(lua::CheckUserData(L, -1, _classNameUD));
			delete (*obj);

			return 0;
		}

		// It's a general way to build object(table).
		// Lua just only need to store constructor and a small metatable of userdata.
		static int constructor(lua::NativeState L)
		{
			lua::NewTable(L);                                  // ... [T]
			lua::PushNumber(L, 0);                             // ... [T] [0]
			C** a = (C**)lua::NewUserData(L, sizeof(C*));      // ... [T] [0] [UD]
			*a = new C;
			lua::GetMetaTable(L, _classNameUD);                // ... [T] [0] [UD] [MT]
			lua::SetMetaTable(L, -2);                          // ... [T] [0] [UD]
			lua::SetTable(L, -3);                              // ... [T]

			/*
			visit( every element of _list[] )
			{
				... [T] [member func name]
				... [T] [member func name] [member func ID]
				... [T] [member func name] [closure]
				... [T]
			}
			*/
			for (int i = Adapter<C,N>::_list.size()-1; i>=0; i--)
			{
				lua::PushString(L, Adapter<C,N>::_list[i]._name);
				lua::PushInteger(L, i);
				lua::PushClosure(L, &Adapter<C,N>::thunk, 1);
				lua::SetTable(L, -3);
			}

			return 1;
		}

		// It's a faster way to build object(table).
		// Lua have to store a big metatable that include every each member function.
		static int constructorEx(lua::NativeState L)
		{
			lua::NewTable(L);                                  // ... [T]

			//-----------Setup member function-----------
			lua::GetMetaTable(L, _className);                  // ... [T] [MT]
			lua::SetMetaTable(L, -2);                          // ... [T]

			//-----------New a object and setup destructor-----------
			lua::PushNumber(L, 0);                             // ... [T] [0]
			C** a = (C**)lua::NewUserData(L, sizeof(C*));      // ... [T] [0] [UD]
			*a = new C;
			lua::GetMetaTable(L, _classNameUD);                // ... [T] [0] [UD] [MT]
			lua::SetMetaTable(L, -2);                          // ... [T] [0] [UD]
			lua::SetTable(L, -3);                              // ... [T]

			return 1;
		}

		static int thunk(lua::NativeState L)
		{
			                                                        // [this] [arg1] [arg2] ... [argN]
			int id = lua::CheckInteger(L, lua::UpValueIndex(1));
			lua::PushNumber(L, 0);                                  // [this] [arg1] [arg2] ... [argN] [0]
			lua::GetTable(L, 1);                                    // [this] [arg1] [arg2] ... [argN] [UD]
			C** obj = static_cast<C**>(lua::CheckUserData(L, -1, _classNameUD));
			lua::Pop(L, 1);                                         // [this] [arg1] [arg2] ... [argN]

			#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
			return	Adapter<C,N>::_list[id]._proxy->Do(Adapter<C,N>::_lua,*obj);
			#else
			return	Adapter<C,N>::_list[id]._proxy->Do(L,*obj);
			#endif
		}

		static void set_class_name(lua::Str &name)
		{
			_className   = name;
			_classNameUD = _className + "_luapp_ud";
		}
};

template <typename C,int N>Str                                  Adapter<C,N>::_className;
template <typename C,int N>Str                                  Adapter<C,N>::_classNameUD;
template <typename C,int N>typename Adapter<C,N>::PackList      Adapter<C,N>::_list;

#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
template <typename C,int N>Handle                               Adapter<C,N>::_lua;
#endif


}//namespace adapter
}//namespace lua
