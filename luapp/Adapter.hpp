/**
@file   Adapter.hpp
@brief  Help lua and C++.
*/


#ifndef _LUAPP_ADAPTER_HPP_
#define _LUAPP_ADAPTER_HPP_


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

		class PackList : public std::vector<struct Pack>
		{
			typedef std::vector<struct Pack> base;

			public:

				~PackList()
				{
					for(int i =this->size()-1;i>=0;i--)
					{
						delete (*this)[i]._proxy;
					}
				}
		};

		static PackList     _list;

		// It's a general way to register class.
		static void registerClass( lua::Handle    L,    ///< Handle of lua
		                           lua::Str       str   ///< Name of class
		                           )
		{
			Adapter<C,N>::_className=str;                      // ...

			//--------Setup a global function to lua--------
			lua::PushFunction(L, &Adapter<C,N>::constructor);  // ... [F]
			lua::SetGlobal(L, _className.c_str());             // ...

			buildMetaTableForUserdata(L);
		}

		// Call it after every member function was registed at _list[].
		static void registerClassEx( lua::Handle    L,    ///< Handle of lua
		                             lua::Str       str   ///< Name of class
		                             )
		{
			Adapter<C,N>::_className=str;                      // ...

			//--------Setup a global function to lua--------
			lua::PushFunction(L, &Adapter<C,N>::constructor2); // ... [F]
			lua::SetGlobal(L, _className.c_str());             // ...

			buildMetaTableForUserdata(L);
			buildMetaTableForMemberFunction(L);
		}

		// Return a lua function.
		static lua::CFunction getConstructor( lua::Handle    L,    ///< Handle of lua
		                                      lua::Str       str   ///< Name of class
		                                      )
		{
			Adapter<C,N>::_className=str;

			buildMetaTableForUserdata(L);
			buildMetaTableForMemberFunction(L);

			return &Adapter<C,N>::constructor2;
		}

	private:

		static Str         _className;

		static void buildMetaTableForUserdata(lua::Handle L)
		{
			lua::NewMetaTable(L, (_className+"_ud").c_str());  // ... [T]
			lua::PushString(L, "__gc");                        // ... [T] ["__gc"]
			lua::PushFunction(L, &Adapter<C,N>::gc_obj);       // ... [T] ["__gc"] [F]
			lua::SetTable(L, -3);                              // ... [T]
			lua::Pop(L,1);                                     // ...
		}

		static void buildMetaTableForMemberFunction(lua::Handle L)
		{
			lua::NewMetaTable(L, _className.c_str());          // ... [T]
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
				lua::PushString(L, Adapter<C,N>::_list[i]._name.c_str());
				lua::PushNumber(L, i);
				lua::PushClosure(L, &Adapter<C,N>::thunk, 1);
				lua::SetTable(L, -3);
			}

			lua::Pop(L,1);                                     // ...
		}

		// As destructor.
		static int gc_obj(lua::Handle L)
		{
			C** obj = static_cast<C**>(lua::CheckUserData(L, -1, (_className+"_ud").c_str()));
			delete (*obj);

			return 0;
		}

		// It's a general way to build table. Lua just only need to store constructor and userdata metatable.
		static int constructor(lua::Handle L)
		{
			lua::NewTable(L);                                  // ... [T]
			lua::PushNumber(L, 0);                             // ... [T] [0]
			C** a = (C**)lua::NewUserData(L, sizeof(C*));      // ... [T] [0] [UD]
			*a = new C;
			lua::GetMetaTable(L, (_className+"_ud").c_str());  // ... [T] [0] [UD] [MT]
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
				lua::PushString(L, Adapter<C,N>::_list[i]._name.c_str());
				lua::PushNumber(L, i);
				lua::PushClosure(L, &Adapter<C,N>::thunk, 1);
				lua::SetTable(L, -3);
			}

			return 1;
		}

		// It's a faster way to build table. Lua have to store metatable that include every each member function.
		static int constructor2(lua::Handle L)
		{
			lua::NewTable(L);                                  // ... [T]

			//-----------Setup member function-----------
			lua::GetMetaTable(L, _className.c_str());          // ... [T] [MT]
			lua::SetMetaTable(L, -2);                          // ... [T]

			//-----------New a object and setup destructor-----------
			lua::PushNumber(L, 0);                             // ... [T] [0]
			C** a = (C**)lua::NewUserData(L, sizeof(C*));      // ... [T] [0] [UD]
			*a = new C;
			lua::GetMetaTable(L, (_className+"_ud").c_str());  // ... [T] [0] [UD] [MT]
			lua::SetMetaTable(L, -2);                          // ... [T] [0] [UD]
			lua::SetTable(L, -3);                              // ... [T]

			return 1;
		}

		static int thunk(lua::Handle L)
		{
			int i = (int)lua::CheckNumber(L, lua::UpValueIndex(1));
			lua::PushNumber(L, 0);
			lua::GetTable(L, 1);
			C** obj = static_cast<C**>(lua::CheckUserData(L, -1, (_className+"_ud").c_str()));
			lua::Pop(L, 1);

			return	Adapter<C,N>::_list[i]._proxy->Do(L,*obj);
		}
};

template <typename C,int N>Str                                  Adapter<C,N>::_className;
template <typename C,int N>typename Adapter<C,N>::PackList      Adapter<C,N>::_list;



}//namespace adapter
}//namespace lua

#endif//_LUAPP_ADAPTER_HPP_
