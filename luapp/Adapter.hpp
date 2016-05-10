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
			Pack():mProxy(0){}
			Pack(Str name,Proxy<C> *param):mName(name),mProxy(param){}

			Str            mName;
			Proxy<C>*      mProxy;
		};

		class PackList : public std::vector<struct Pack>
		{
			typedef std::vector<struct Pack> base;

			public:

				~PackList()
				{
					for(int i =this->size()-1;i>=0;i--)
					{
						delete (*this)[i].mProxy;
					}
				}
		};

		static PackList     mList;

		// It's a general way to register class.
		static void Register( lua::Handle    L,    ///< Handle of lua
		                      const char*    str   ///< Name of class
		                      )
		{
			Adapter<C,N>::mClassName=str;                      // ...

			//--------Setup a global function to lua--------
			lua::PushFunction(L, &Adapter<C,N>::constructor);  // ... [F]
			lua::SetGlobal(L, mClassName.c_str());             // ...

			//--------Create a metatable for userdata--------
			lua::NewMetaTable(L, (mClassName+"_ud").c_str());  // ... [T]
			lua::PushString(L, "__gc");                        // ... [T] ["__gc"]
			lua::PushFunction(L, &Adapter<C,N>::gc_obj);       // ... [T] ["__gc"] [F]
			lua::SetTable(L, -3);                              // ... [T]
			lua::Pop(L,1);                                     // ...
		}

		// Call it after every member function was registed at mList[].
		static void RegisterEx( lua::Handle    L,    ///< Handle of lua
		                        const char*    str   ///< Name of class
		                        )
		{
			Adapter<C,N>::mClassName=str;                      // ...

			//--------Setup a global function to lua--------
			lua::PushFunction(L, &Adapter<C,N>::constructor2); // ... [F]
			lua::SetGlobal(L, mClassName.c_str());             // ...

			//--------Create a metatable for userdata--------
			lua::NewMetaTable(L, (mClassName+"_ud").c_str());  // ... [T]
			lua::PushString(L, "__gc");                        // ... [T] ["__gc"]
			lua::PushFunction(L, &Adapter<C,N>::gc_obj);       // ... [T] ["__gc"] [F]
			lua::SetTable(L, -3);                              // ... [T]
			lua::Pop(L,1);                                     // ...


			//--------Create a metatable for member function--------start

			lua::NewMetaTable(L, mClassName.c_str());          // ... [T]
			lua::PushString(L, "__index");                     // ... [T] ["__index"]
			lua::PushValue(L,-2);                              // ... [T] ["__index"] [T]
			lua::SetTable(L,-3);                               // ... [T]

			/*
			visit( every element of mList[] )
			{
				... [T] [member func name]
				... [T] [member func name] [member func ID]
				... [T] [member func name] [closure]
				... [T]
			}
			*/
			for (int i = Adapter<C,N>::mList.size()-1; i>=0; i--)
			{
				lua::PushString(L, Adapter<C,N>::mList[i].mName.c_str());
				lua::PushNumber(L, i);
				lua::PushClosure(L, &Adapter<C,N>::thunk, 1);
				lua::SetTable(L, -3);
			}

			lua::Pop(L,1);                                     // ...

			//--------Create a metatable for member function--------end
		}

	private:

		static Str         mClassName;

		// As destructor.
		static int gc_obj(lua::Handle L)
		{
			C** obj = static_cast<C**>(lua::CheckUserData(L, -1, (mClassName+"_ud").c_str()));
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
			lua::GetMetaTable(L, (mClassName+"_ud").c_str());  // ... [T] [0] [UD] [MT]
			lua::SetMetaTable(L, -2);                          // ... [T] [0] [UD]
			lua::SetTable(L, -3);                              // ... [T]

			/*
			visit( every element of mList[] )
			{
				... [T] [member func name]
				... [T] [member func name] [member func ID]
				... [T] [member func name] [closure]
				... [T]
			}
			*/
			for (int i = Adapter<C,N>::mList.size()-1; i>=0; i--)
			{
				lua::PushString(L, Adapter<C,N>::mList[i].mName.c_str());
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
			lua::GetMetaTable(L, mClassName.c_str());          // ... [T] [MT]
			lua::SetMetaTable(L, -2);                          // ... [T]

			//-----------New a object and setup destructor-----------
			lua::PushNumber(L, 0);                             // ... [T] [0]
			C** a = (C**)lua::NewUserData(L, sizeof(C*));      // ... [T] [0] [UD]
			*a = new C;
			lua::GetMetaTable(L, (mClassName+"_ud").c_str());  // ... [T] [0] [UD] [MT]
			lua::SetMetaTable(L, -2);                          // ... [T] [0] [UD]
			lua::SetTable(L, -3);                              // ... [T]

			return 1;
		}

		static int thunk(lua::Handle L)
		{
			int i = (int)lua::ToNumber(L, lua::UpValueIndex(1));
			lua::PushNumber(L, 0);
			lua::GetTable(L, 1);
			C** obj = static_cast<C**>(lua::CheckUserData(L, -1, (mClassName+"_ud").c_str()));
			lua::Pop(L, 1);

			return	Adapter<C,N>::mList[i].mProxy->Do(L,*obj);
		}
};

template <typename C,int N>Str                                  Adapter<C,N>::mClassName;
template <typename C,int N>typename Adapter<C,N>::PackList      Adapter<C,N>::mList;



}//namespace adapter
}//namespace lua

#endif//_LUAPP_ADAPTER_HPP_
