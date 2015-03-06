/**
@file   LuaWrapper.hpp
@brief  Help lua and C++.
*/


#ifndef _LUAPP_WRAPPER_HPP_
#define _LUAPP_WRAPPER_HPP_


#include "LuaWrapperProxy.hpp"



namespace lua{
namespace wrapper{


struct Pack
{
	Pack():mProxy(0){}
	Pack(Str name,Proxy *param):mName(name),mProxy(param){}

	Str         mName;
	Proxy*      mProxy;
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

extern PackList        gFuncList;

int gThunk(lua::Handle L);


template <typename F>
void RegisterFunction( lua::Handle    L,
                       const char*    name,
                       F              fn
                       )
{
	Str                 str(name);
	struct Pack         func(str,GetProxy(fn));
	gFuncList.push_back(func);

	lua::PushNumber(L, gFuncList.size()-1);
	lua::PushClosure(L, &gThunk, 1);
	lua::SetGlobal(L, str.c_str());
}


}//namespace wrapper
}//namespace lua

#endif//_LUAPP_WRAPPER_HPP_
