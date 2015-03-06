/**
@file   LuaAdapter.hpp
@brief  Help lua and C++.
*/


#ifndef _LUAPP_ADAPTER_HPP_
#define _LUAPP_ADAPTER_HPP_


#include "LuaAdapterProxy.hpp"



namespace lua{
namespace adapter{



template<typename C>
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

		static void Register( lua::Handle    L,    ///< Handle of lua
		                      const char*    str   ///< Name of class
		                      )
		{
			Adapter<C>::mClassName=str;

			lua::PushFunction(L, &Adapter<C>::constructor);
			lua::SetGlobal(L, mClassName.c_str());

			lua::NewMetaTable(L, mClassName.c_str());

			lua::PushString(L, "__gc");
			lua::PushFunction(L, &Adapter<C>::gc_obj);
			lua::SetTable(L, -3);

			lua::Pop(L,1);
		}

	private:

		static Str         mClassName;

		static int gc_obj(lua::Handle L)
		{
			C** obj = static_cast<C**>(lua::CheckUserData(L, -1, mClassName.c_str()));
			delete (*obj);
			return 0;
		}

		static int constructor(lua::Handle L)
		{
			C* obj = new C;

			lua::NewTable(L);
			lua::PushNumber(L, 0);
			C** a = (C**)lua::NewUserData(L, sizeof(C*));
			*a = obj;
			lua::GetMetaTable(L, mClassName.c_str());
			lua::SetMetaTable(L, -2);
			lua::SetTable(L, -3);

			for (int i = Adapter<C>::mList.size()-1; i>=0; i--)
			{
				lua::PushString(L, Adapter<C>::mList[i].mName.c_str());
				lua::PushNumber(L, i);
				lua::PushClosure(L, &Adapter<C>::thunk, 1);
				lua::SetTable(L, -3);
			}

			return 1;
		}

		static int thunk(lua::Handle L)
		{
			int i = (int)lua::ToNumber(L, lua::UpValueIndex(1));
			lua::PushNumber(L, 0);
			lua::GetTable(L, 1);
			C** obj = static_cast<C**>(lua::CheckUserData(L, -1, mClassName.c_str()));
			lua::Pop(L, 1);

			return	Adapter<C>::mList[i].mProxy->Do(L,*obj);
		}
};

template <typename C>Str                                  Adapter<C>::mClassName;
template <typename C>typename Adapter<C>::PackList        Adapter<C>::mList;



}//namespace adapter
}//namespace lua

#endif//_LUAPP_ADAPTER_HPP_
