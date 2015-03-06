/**
@file   LuaWrapperProxy.hpp
@brief  To get all of parameters.
*/


#ifndef _LUAPP_WRAPPER_PROXY_HPP_
#define _LUAPP_WRAPPER_PROXY_HPP_


#include "Lua.hpp"


namespace lua{
namespace wrapper{


//------------------------------------------------------------

struct Proxy
{
	virtual ~Proxy(){}
	virtual int Do(lua::Handle)=0;
};

//------------------------------------------------------------


template<typename R>
struct ProxyReturn : public Proxy
{
	ProxyReturn(){/*warning message*/}
};

template<>
struct ProxyReturn<void> : public Proxy
{
};

template<>
struct ProxyReturn<lua::Int> : public Proxy
{
	void ReturnValue(lua::Handle L,lua::Int num)
	{
		lua::PushInteger(L,num);
	}
};

template<>
struct ProxyReturn<lua::Num> : public Proxy
{
	void ReturnValue(lua::Handle L,lua::Num num)
	{
		lua::PushNumber(L,num);
	}
};

template<>
struct ProxyReturn<lua::Str> : public Proxy
{
	void ReturnValue(lua::Handle L,lua::Str num)
	{
		lua::PushString(L,num.c_str());
	}
};


//------------------------------------------------------------

template<typename R>
struct Proxy00 : public ProxyReturn<R>
{
	typedef R(*Func)();
	Proxy00(){}
	Proxy00(Func fn):func00(fn){}

	Func    func00;

	int Do(lua::Handle L)
	{
		this->ReturnValue(L,func00());
		return (int)1;
	}
};

template<>
struct Proxy00<void> : public ProxyReturn<void>
{
	typedef void R;
	typedef R(*Func)();
	Proxy00(){}
	Proxy00(Func fn):func00(fn){}

	Func    func00;

	int Do(lua::Handle)
	{
		func00();
		return (int)1;
	}
};


//------------------------------------------------------------

template<typename R,typename A1>
struct Proxy01 : public ProxyReturn<R>
{
	typedef R (*Func)(A1);
	Proxy01(Func){/*warning message*/}
};

template<typename R>
struct Proxy01<R,lua::Int> : public ProxyReturn<R>
{
	typedef lua::Int A1;
	typedef R (*Func)(A1);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckInteger(L, 1);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,fn(p1));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1),A1 p1)
	{
		fn(p1);
	}

	int Do(lua::Handle L)
	{
		GetValue01(L);
		DoFunction(L,func01,p1);
		return (int)1;
	}
};

template<typename R>
struct Proxy01<R,lua::Num> : public ProxyReturn<R>
{
	typedef lua::Num A1;
	typedef R (*Func)(lua::Num);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckNumber(L, 1);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,fn(p1));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1),A1 p1)
	{
		fn(p1);
	}

	int Do(lua::Handle L)
	{
		GetValue01(L);
		DoFunction(L,func01,p1);
		return (int)1;
	}
};

template<typename R>
struct Proxy01<R,lua::Str> : public ProxyReturn<R>
{
	typedef lua::Str A1;
	typedef R (*Func)(lua::Str);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckString(L, 1);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,fn(p1));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1),A1 p1)
	{
		fn(p1);
	}

	int Do(lua::Handle L)
	{
		GetValue01(L);
		DoFunction(L,func01,p1);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename R,typename A1,typename A2>
struct Proxy02 : public Proxy01<R,A1>
{
	typedef R (*Func)(A1,A2);
	Proxy02(Func){/*warning message*/}
};

template<typename R,typename A1>
struct Proxy02<R,A1,lua::Int> : public Proxy01<R,A1>
{
	typedef lua::Int A2;
	typedef R (*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckInteger(L, 2);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,fn(p1,p2));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2),A1 p1,A2 p2)
	{
		fn(p1,p2);
	}

	int Do(lua::Handle L)
	{
		GetValue02(L);
		DoFunction(L,func02,this->p1,p2);
		return (int)1;
	}
};

template<typename R,typename A1>
struct Proxy02<R,A1,lua::Num> : public Proxy01<R,A1>
{
	typedef lua::Num A2;
	typedef R(*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckNumber(L, 2);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,fn(p1,p2));
	}

	template<typename tagT>
	void DoFunction(lua::Handle  ,void (*fn)(A1,A2),A1 p1,A2 p2)
	{
		fn(p1,p2);
	}

	int Do(lua::Handle L)
	{
		GetValue02(L);
		DoFunction(L,func02,this->p1,p2);
		return (int)1;
	}
};

template<typename R,typename A1>
struct Proxy02<R,A1,lua::Str> : public Proxy01<R,A1>
{
	typedef lua::Str A2;
	typedef R(*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckString(L, 2);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,fn(p1,p2));
	}

	template<typename tagT>
	void DoFunction(lua::Handle  ,void (*fn)(A1,A2),A1 p1,A2 p2)
	{
		fn(p1,p2);
	}

	int Do(lua::Handle L)
	{
		GetValue02(L);
		DoFunction(L,func02,this->p1,p2);
		return (int)1;
	}
};

//------------------------------------------------------------

template <typename R>
static Proxy* GetProxy(R(*f)())
{
	return (Proxy*)new Proxy00<R>(f);
}

template <typename R,typename A1>
static Proxy* GetProxy(R(*f)(A1))
{
	return (Proxy*)new Proxy01<R,A1>(f);
}

template <typename R,typename A1,typename A2>
static Proxy* GetProxy(R(*f)(A1,A2))
{
	return (Proxy*)new Proxy02<R,A1,A2>(f);
}

//------------------------------------------------------------


}//namespace wrapper
}//namespace lua

#endif//_LUAPP_WRAPPER_PROXY_HPP_
