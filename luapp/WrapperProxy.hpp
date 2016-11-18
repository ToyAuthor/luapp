/**
@file   WrapperProxy.hpp
@brief  To get all of parameters.
*/


#pragma once


#include "luapp/Standard.hpp"


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
	void returnValue(lua::Handle L,R num)
	{
		PushVarToLua(L,num);
	}
};

template<>
struct ProxyReturn<void> : public Proxy
{
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
		this->returnValue(L,func00());
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

	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	Func    func01;

	template<typename tagR>
	void doFunction(lua::Handle L,tagR (*fn)(A1),A1 p1)
	{
		this->returnValue(L,fn(p1));
	}

	void doFunction(lua::Handle  ,void (*fn)(A1),A1 p1)
	{
		fn(p1);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		lua::CheckVarFromLua(L,&p1,1);
		doFunction(L,func01,p1);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename R,typename A1,typename A2>
struct Proxy02 : public ProxyReturn<R>
{
	typedef R (*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}

	Func    func02;

	template<typename tagR>
	void doFunction(lua::Handle L,tagR (*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->returnValue(L,fn(p1,p2));
	}

	void doFunction(lua::Handle  ,void (*fn)(A1,A2),A1 p1,A2 p2)
	{
		fn(p1,p2);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		A2      p2;
		lua::CheckVarFromLua(L,&p1,1);
		lua::CheckVarFromLua(L,&p2,2);
		doFunction(L,func02,p1,p2);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename R,typename A1,typename A2,typename A3>
struct Proxy03 : public ProxyReturn<R>
{
	typedef R (*Func)(A1,A2,A3);

	Proxy03(){}
	Proxy03(Func fn):func03(fn){}

	Func    func03;

	template<typename tagR>
	void doFunction(lua::Handle L,tagR (*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		this->returnValue(L,fn(p1,p2,p3));
	}

	void doFunction(lua::Handle  ,void (*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		fn(p1,p2,p3);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		lua::CheckVarFromLua(L,&p1,1);
		lua::CheckVarFromLua(L,&p2,2);
		lua::CheckVarFromLua(L,&p3,3);
		doFunction(L,func03,p1,p2,p3);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename R,typename A1,typename A2,typename A3,typename A4>
struct Proxy04 : public ProxyReturn<R>
{
	typedef R (*Func)(A1,A2,A3,A4);

	Proxy04(){}
	Proxy04(Func fn):func04(fn){}

	Func    func04;

	template<typename tagR>
	void doFunction(lua::Handle L,tagR (*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		this->returnValue(L,fn(p1,p2,p3,p4));
	}

	void doFunction(lua::Handle  ,void (*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		fn(p1,p2,p3,p4);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		lua::CheckVarFromLua(L,&p1,1);
		lua::CheckVarFromLua(L,&p2,2);
		lua::CheckVarFromLua(L,&p3,3);
		lua::CheckVarFromLua(L,&p4,4);
		doFunction(L,func04,p1,p2,p3,p4);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename R,typename A1,typename A2,typename A3,typename A4,typename A5>
struct Proxy05 : public ProxyReturn<R>
{
	typedef R (*Func)(A1,A2,A3,A4,A5);

	Proxy05(){}
	Proxy05(Func fn):func05(fn){}

	Func    func05;

	template<typename tagR>
	void doFunction(lua::Handle L,tagR (*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		this->returnValue(L,fn(p1,p2,p3,p4,p5));
	}

	void doFunction(lua::Handle  ,void (*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		fn(p1,p2,p3,p4,p5);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		A5      p5;
		lua::CheckVarFromLua(L,&p1,1);
		lua::CheckVarFromLua(L,&p2,2);
		lua::CheckVarFromLua(L,&p3,3);
		lua::CheckVarFromLua(L,&p4,4);
		lua::CheckVarFromLua(L,&p5,5);
		doFunction(L,func05,p1,p2,p3,p4,p5);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename R,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct Proxy06 : public ProxyReturn<R>
{
	typedef R (*Func)(A1,A2,A3,A4,A5,A6);

	Proxy06(){}
	Proxy06(Func fn):func06(fn){}

	Func    func06;

	template<typename tagR>
	void doFunction(lua::Handle L,tagR (*fn)(A1,A2,A3,A4,A5,A6),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5,A6 p6)
	{
		this->returnValue(L,fn(p1,p2,p3,p4,p5,p6));
	}

	void doFunction(lua::Handle  ,void (*fn)(A1,A2,A3,A4,A5,A6),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5,A6 p6)
	{
		fn(p1,p2,p3,p4,p5,p6);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		A5      p5;
		A6      p6;
		lua::CheckVarFromLua(L,&p1,1);
		lua::CheckVarFromLua(L,&p2,2);
		lua::CheckVarFromLua(L,&p3,3);
		lua::CheckVarFromLua(L,&p4,4);
		lua::CheckVarFromLua(L,&p5,5);
		lua::CheckVarFromLua(L,&p6,6);
		doFunction(L,func06,p1,p2,p3,p4,p5,p6);
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

template <typename R,typename A1,typename A2,typename A3>
static Proxy* GetProxy(R(*f)(A1,A2,A3))
{
	return (Proxy*)new Proxy03<R,A1,A2,A3>(f);
}

template <typename R,typename A1,typename A2,typename A3,typename A4>
static Proxy* GetProxy(R(*f)(A1,A2,A3,A4))
{
	return (Proxy*)new Proxy04<R,A1,A2,A3,A4>(f);
}

template <typename R,typename A1,typename A2,typename A3,typename A4,typename A5>
static Proxy* GetProxy(R(*f)(A1,A2,A3,A4,A5))
{
	return (Proxy*)new Proxy05<R,A1,A2,A3,A4,A5>(f);
}

template <typename R,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
static Proxy* GetProxy(R(*f)(A1,A2,A3,A4,A5,A6))
{
	return (Proxy*)new Proxy06<R,A1,A2,A3,A4,A5,A6>(f);
}

//------------------------------------------------------------

template<typename C,typename R>
struct ProxyBind00 : public ProxyReturn<R>
{
	typedef R (C::*Func)();

	ProxyBind00(){}
	ProxyBind00(Func fn,C *c):func(fn),obj(c){}

	Func    func;
	C*      obj;

	int Do(lua::Handle L)
	{
		this->returnValue(L,(obj->*func)());
		return (int)1;
	}
};

template<typename C>
struct ProxyBind00<C,void> : public ProxyReturn<void>
{
	typedef void R;
	typedef R (C::*Func)();

	ProxyBind00(){}
	ProxyBind00(Func fn,C *c):func(fn),obj(c){}

	Func    func;
	C*      obj;

	int Do(lua::Handle)
	{
		(obj->*func)();
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1>
struct ProxyBind01 : public ProxyReturn<R>
{
	typedef R (C::*Func)(A1);

	ProxyBind01(){}
	ProxyBind01(Func fn,C *c):func(fn),obj(c){}

	Func    func;
	C*      obj;

	template<typename tagR>
	void doFunction(lua::Handle L,C *c,tagR (C::*fn)(A1),A1 p1)
	{
		this->returnValue(L,(c->*fn)(p1));
	}

	void doFunction(lua::Handle  ,C *c,void (C::*fn)(A1),A1 p1)
	{
		(c->*fn)(p1);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		lua::CheckVarFromLua(L,&p1,1);
		doFunction(L,obj,func,p1);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2>
struct ProxyBind02 : public ProxyReturn<R>
{
	typedef R (C::*Func)(A1,A2);

	ProxyBind02(){}
	ProxyBind02(Func fn,C *c):func(fn),obj(c){}

	Func    func;
	C*      obj;

	template<typename tagR>
	void doFunction(lua::Handle L,C *c,tagR (C::*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->returnValue(L,(c->*fn)(p1,p2));
	}

	void doFunction(lua::Handle  ,C *c,void (C::*fn)(A1,A2),A1 p1,A2 p2)
	{
		(c->*fn)(p1,p2);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		A2      p2;
		lua::CheckVarFromLua(L,&p1,1);
		lua::CheckVarFromLua(L,&p2,2);
		doFunction(L,obj,func,p1,p2);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3>
struct ProxyBind03 : public ProxyReturn<R>
{
	typedef R (C::*Func)(A1,A2,A3);

	ProxyBind03(){}
	ProxyBind03(Func fn,C *c):func(fn),obj(c){}

	Func    func;
	C*      obj;

	template<typename tagR>
	void doFunction(lua::Handle L,C *c,tagR (C::*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		this->returnValue(L,(c->*fn)(p1,p2,p3));
	}

	void doFunction(lua::Handle  ,C *c,void (C::*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		(c->*fn)(p1,p2,p3);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		lua::CheckVarFromLua(L,&p1,1);
		lua::CheckVarFromLua(L,&p2,2);
		lua::CheckVarFromLua(L,&p3,3);
		doFunction(L,obj,func,p1,p2,p3);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4>
struct ProxyBind04 : public ProxyReturn<R>
{
	typedef R (C::*Func)(A1,A2,A3,A4);

	ProxyBind04(){}
	ProxyBind04(Func fn,C *c):func(fn),obj(c){}

	Func    func;
	C*      obj;

	template<typename tagR>
	void doFunction(lua::Handle L,C *c,tagR (C::*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		this->returnValue(L,(c->*fn)(p1,p2,p3,p4));
	}

	void doFunction(lua::Handle  ,C *c,void (C::*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		(c->*fn)(p1,p2,p3,p4);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		lua::CheckVarFromLua(L,&p1,1);
		lua::CheckVarFromLua(L,&p2,2);
		lua::CheckVarFromLua(L,&p3,3);
		lua::CheckVarFromLua(L,&p4,4);
		doFunction(L,obj,func,p1,p2,p3,p4);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4,typename A5>
struct ProxyBind05 : public ProxyReturn<R>
{
	typedef R (C::*Func)(A1,A2,A3,A4,A5);

	ProxyBind05(){}
	ProxyBind05(Func fn,C *c):func(fn),obj(c){}

	Func    func;
	C*      obj;

	template<typename tagR>
	void doFunction(lua::Handle L,C *c,tagR (C::*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		this->returnValue(L,(c->*fn)(p1,p2,p3,p4,p5));
	}

	void doFunction(lua::Handle  ,C *c,void (C::*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		(c->*fn)(p1,p2,p3,p4,p5);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		A5      p5;
		lua::CheckVarFromLua(L,&p1,1);
		lua::CheckVarFromLua(L,&p2,2);
		lua::CheckVarFromLua(L,&p3,3);
		lua::CheckVarFromLua(L,&p4,4);
		lua::CheckVarFromLua(L,&p5,5);
		doFunction(L,obj,func,p1,p2,p3,p4,p5);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct ProxyBind06 : public ProxyReturn<R>
{
	typedef R (C::*Func)(A1,A2,A3,A4,A5,A6);

	ProxyBind06(){}
	ProxyBind06(Func fn,C *c):func(fn),obj(c){}

	Func    func;
	C*      obj;

	template<typename tagR>
	void doFunction(lua::Handle L,C *c,tagR (C::*fn)(A1,A2,A3,A4,A5,A6),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5,A6 p6)
	{
		this->returnValue(L,(c->*fn)(p1,p2,p3,p4,p5,p6));
	}

	void doFunction(lua::Handle  ,C *c,void (C::*fn)(A1,A2,A3,A4,A5,A6),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5,A6 p6)
	{
		(c->*fn)(p1,p2,p3,p4,p5,p6);
	}

	int Do(lua::Handle L)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		A5      p5;
		A6      p6;
		lua::CheckVarFromLua(L,&p1,1);
		lua::CheckVarFromLua(L,&p2,2);
		lua::CheckVarFromLua(L,&p3,3);
		lua::CheckVarFromLua(L,&p4,4);
		lua::CheckVarFromLua(L,&p5,5);
		lua::CheckVarFromLua(L,&p6,6);
		doFunction(L,obj,func,p1,p2,p3,p4,p5,p6);
		return (int)1;
	}
};

//------------------------------------------------------------

template <typename C,typename R>
static Proxy* GetProxy(R(C::*f)(),C *obj)
{
	return (Proxy*)new ProxyBind00<C,R>(f,obj);
}

template <typename C,typename R,typename A1>
static Proxy* GetProxy(R(C::*f)(A1),C *obj)
{
	return (Proxy*)new ProxyBind01<C,R,A1>(f,obj);
}

template <typename C,typename R,typename A1,typename A2>
static Proxy* GetProxy(R(C::*f)(A1,A2),C *obj)
{
	return (Proxy*)new ProxyBind02<C,R,A1,A2>(f,obj);
}

template <typename C,typename R,typename A1,typename A2,typename A3>
static Proxy* GetProxy(R(C::*f)(A1,A2,A3),C *obj)
{
	return (Proxy*)new ProxyBind03<C,R,A1,A2,A3>(f,obj);
}

template <typename C,typename R,typename A1,typename A2,typename A3,typename A4>
static Proxy* GetProxy(R(C::*f)(A1,A2,A3,A4),C *obj)
{
	return (Proxy*)new ProxyBind04<C,R,A1,A2,A3,A4>(f,obj);
}

template <typename C,typename R,typename A1,typename A2,typename A3,typename A4,typename A5>
static Proxy* GetProxy(R(C::*f)(A1,A2,A3,A4,A5),C *obj)
{
	return (Proxy*)new ProxyBind05<C,R,A1,A2,A3,A4,A5>(f,obj);
}

template <typename C,typename R,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
static Proxy* GetProxy(R(C::*f)(A1,A2,A3,A4,A5,A6),C *obj)
{
	return (Proxy*)new ProxyBind06<C,R,A1,A2,A3,A4,A5,A6>(f,obj);
}

//------------------------------------------------------------


}//namespace wrapper
}//namespace lua
