/**
@file   Wrapper.hpp
@brief  Help lua and C++.
*/


#ifndef _LUAPP_WRAPPER_HPP_
#define _LUAPP_WRAPPER_HPP_


#include "luapp/WrapperProxy.hpp"



namespace lua{
namespace wrapper{


template<int N>
class Wrapper
{
	public:

		struct Pack
		{
			Pack():_proxy(0){}
			Pack(Str name,Proxy *param):_name(name),_proxy(param){}

			Str         _name;
			Proxy*      _proxy;
		};

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

		// For global function.
		template <typename F>
		static void RegisterFunction( lua::Handle    L,
		                              lua::Str       name,
		                              F              fn
		                              )
		{
			struct Pack         func(name,GetProxy(fn));
			_funcList.push_back(func);

			lua::PushNumber(L, _funcList.size()-1);
			lua::PushClosure(L, &thunk, 1);
			lua::SetGlobal(L, name.c_str());
		}

		// For member function.
		template <typename F,typename C>
		static void RegisterFunction( lua::Handle    L,
		                              lua::Str       name,
		                              F              fn,
		                              C*             obj
		                              )
		{

			struct Pack         func(name,GetProxy(fn,obj));
			_funcList.push_back(func);

			lua::PushNumber(L, _funcList.size()-1);
			lua::PushClosure(L, &thunk, 1);
			lua::SetGlobal(L, name.c_str());
		}

	private:

		static PackList        _funcList;

		static int thunk(lua::Handle L)
		{
			int i = (int)lua::CheckNumber(L, lua::UpValueIndex(1));

			return _funcList[i]._proxy->Do(L);
		}

};

template<int N>typename Wrapper<N>::PackList        Wrapper<N>::_funcList;


}//namespace wrapper
}//namespace lua

#endif//_LUAPP_WRAPPER_HPP_
