/**
@file   LuaWrapper.hpp
@brief  Help lua and C++.
*/


#ifndef _LUAPP_WRAPPER_HPP_
#define _LUAPP_WRAPPER_HPP_


#include "LuaWrapperProxy.hpp"



namespace lua{
namespace wrapper{


template<int N>
class Wrapper
{
	public:

		struct Pack
		{
			Pack():mProxy(0){}
			Pack(Str name,Proxy *param):mName(name),mProxy(param){}

			Str         mName;
			Proxy*      mProxy;
		};

		class PackList : public std::vector<struct Pack>
		{
			public:

				~PackList()
				{
					for(int i =this->size()-1;i>=0;i--)
					{
						delete (*this)[i].mProxy;
					}
				}
		};

		// For global function.
		template <typename F>
		static void RegisterFunction( lua::Handle    L,
		                              const char*    name,
		                              F              fn
		                              )
		{
			Str                 str(name);
			struct Pack         func(str,GetProxy(fn));
			mFuncList.push_back(func);

			lua::PushNumber(L, mFuncList.size()-1);
			lua::PushClosure(L, &thunk, 1);
			lua::SetGlobal(L, str.c_str());
		}

		// For member function.
		template <typename F,typename C>
		static void RegisterFunction( lua::Handle    L,
		                              const char*    name,
		                              F              fn,
		                              C*             obj
		                              )
		{
			Str                 str(name);

			struct Pack         func(str,GetProxy(fn,obj));
			mFuncList.push_back(func);

			lua::PushNumber(L, mFuncList.size()-1);
			lua::PushClosure(L, &thunk, 1);
			lua::SetGlobal(L, str.c_str());
		}

	private:

		static PackList        mFuncList;

		static int thunk(lua::Handle L)
		{
			int i = (int)lua::ToNumber(L, lua::UpValueIndex(1));

			return mFuncList[i].mProxy->Do(L);
		}

};

template<int N>typename Wrapper<N>::PackList        Wrapper<N>::mFuncList;


}//namespace wrapper
}//namespace lua

#endif//_LUAPP_WRAPPER_HPP_
