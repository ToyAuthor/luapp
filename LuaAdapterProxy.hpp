/**
@file   LuaAdapterProxy.hpp
@brief  To get all of parameters.
*/


#ifndef _LUAPP_ADAPTER_PROXY_HPP_
#define _LUAPP_ADAPTER_PROXY_HPP_


#include "Lua.hpp"



namespace lua{
namespace adapter{


//------------------------------------------------------------

template<typename C>
struct Proxy
{
	virtual ~Proxy(){}
	virtual int Do(lua::Handle,C*)=0;
};

//------------------------------------------------------------

template<typename C,typename R>
struct ProxyReturn : public Proxy<C>
{
	ProxyReturn(){/*warning message*/}
};

template<typename C>
struct ProxyReturn<C,void> : public Proxy<C>
{
};

template<typename C>
struct ProxyReturn<C,lua::Int> : public Proxy<C>
{
	void ReturnValue(lua::Handle L,lua::Int num)
	{
		lua::PushInteger(L,num);
	}
};

template<typename C>
struct ProxyReturn<C,lua::Num> : public Proxy<C>
{
	void ReturnValue(lua::Handle L,lua::Num num)
	{
		lua::PushNumber(L,num);
	}
};

template<typename C>
struct ProxyReturn<C,lua::Str> : public Proxy<C>
{
	void ReturnValue(lua::Handle L,lua::Str num)
	{
		lua::PushString(L,num.c_str());
	}
};

//------------------------------------------------------------

template<typename C,typename R>
struct Proxy00 : public ProxyReturn<C,R>
{
	typedef R(C::*Func)();
	Proxy00(){}
	Proxy00(Func fn):func00(fn){}

	Func    func00;

	int Do(lua::Handle L,C *obj)
	{
		this->ReturnValue(L,(obj->*func00)());
		return (int)1;
	}
};

template<typename C>
struct Proxy00<C,void> : public ProxyReturn<C,void>
{
	typedef void R;
	typedef R(C::*Func)();
	Proxy00(){}
	Proxy00(Func fn):func00(fn){}
	Func    func00;

	int Do(lua::Handle,C *obj)
	{
		(obj->*func00)();
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1>
struct Proxy01 : public ProxyReturn<C,R>
{
	typedef R (C::*Func)(A1);
	Proxy01(Func){/*warning message*/}
};

template<typename C,typename R>
struct Proxy01<C,R,lua::Int> : public ProxyReturn<C,R>
{
	typedef lua::Int A1;
	typedef R (C::*Func)(A1);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckInteger(L, 2);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,(obj->*fn)(p1));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1),A1 p1)
	{
		(obj->*fn)(p1);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue01(L);
		DoFunction(L,obj,func01,p1);
		return (int)1;
	}
};

template<typename C,typename R>
struct Proxy01<C,R,lua::Num> : public ProxyReturn<C,R>
{
	typedef lua::Num A1;
	typedef R (C::*Func)(A1);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckNumber(L, 2);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,(obj->*fn)(p1));
	}

	template<typename tagC>
	void DoFunction(lua::Handle,  tagC *obj,void (tagC::*fn)(A1),A1 p1)
	{
		(obj->*fn)(p1);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue01(L);
		DoFunction(L,obj,func01,p1);
		return (int)1;
	}
};

template<typename C,typename R>
struct Proxy01<C,R,lua::Str> : public ProxyReturn<C,R>
{
	typedef lua::Str A1;
	typedef R (C::*Func)(A1);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckString(L, 2);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,(obj->*fn)(p1));
	}

	template<typename tagC>
	void DoFunction(lua::Handle,  tagC *obj,void (tagC::*fn)(A1),A1 p1)
	{
		(obj->*fn)(p1);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue01(L);
		DoFunction(L,obj,func01,p1);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2>
struct Proxy02 : public Proxy01<C,R,A1>
{
	typedef R (C::*Func)(A1,A2);
	Proxy02(Func){/*warning message*/}
};

template<typename C,typename R,typename A1>
struct Proxy02<C,R,A1,lua::Int> : public Proxy01<C,R,A1>
{
	typedef lua::Int A2;
	typedef R(C::*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckInteger(L, 3);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		(obj->*fn)(p1,p2);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue02(L);
		DoFunction(L,obj,func02,this->p1,p2);
		return (int)1;
	}
};

template<typename C,typename R,typename A1>
struct Proxy02<C,R,A1,lua::Num> : public Proxy01<C,R,A1>
{
	typedef lua::Num A2;
	typedef R(C::*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckNumber(L, 3);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		(obj->*fn)(p1,p2);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue02(L);
		DoFunction(L,obj,func02,this->p1,p2);
		return (int)1;
	}
};

template<typename C,typename R,typename A1>
struct Proxy02<C,R,A1,lua::Str> : public Proxy01<C,R,A1>
{
	typedef lua::Str A2;
	typedef R(C::*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckString(L, 3);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		(obj->*fn)(p1,p2);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue02(L);
		DoFunction(L,obj,func02,this->p1,p2);
		return (int)1;
	}
};

//------------------------------------------------------------

template <typename C,typename R>
static Proxy<C>* GetProxy(R(C::*f)())
{
	return (Proxy<C>*)new Proxy00<C,R>(f);
}

template <typename C,typename R,typename A1>
static Proxy<C>* GetProxy(R(C::*f)(A1))
{
	return (Proxy<C>*)new Proxy01<C,R,A1>(f);
}

template <typename C,typename R,typename A1,typename A2>
static Proxy<C>* GetProxy(R(C::*f)(A1,A2))
{
	return (Proxy<C>*)new Proxy02<C,R,A1,A2>(f);
}

//------------------------------------------------------------





}//namespace adapter
}//namespace lua

#endif//_LUAPP_ADAPTER_PROXY_HPP_
