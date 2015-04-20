/**
@file   LuaFunction.hpp
@brief  Let you call the function come from lua.
*/

#ifndef _LUAPP_FUNCTION_HPP_
#define _LUAPP_FUNCTION_HPP_


#include "Lua.hpp"



namespace lua{



template<typename R>
struct Function{};

template<>
struct Function<void()>
{
	Function(){}

	void operator()() const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		lua::PCall(hLua,0,0,0);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R>
struct Function<R()>
{
	Function(){}

	R operator()() const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		lua::PCall(hLua,0,1,0);

		R   result;
		CheckVarFromLua(hLua,&result,-1);
		lua::Pop(hLua,1);

		return result;
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename A1>
struct Function<void(A1)>
{
	void operator()(A1 a1) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		lua::PCall(hLua,1,0,0);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R,typename A1>
struct Function<R(A1)>
{
	R operator()(A1 a1) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		lua::PCall(hLua,1,1,0);

		R   result;
		CheckVarFromLua(hLua,&result,-1);

		lua::Pop(hLua,1);

		return result;
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename A1,typename A2>
struct Function<void(A1,A2)>
{
	void operator()(A1 a1,A2 a2) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		lua::PCall(hLua,2,0,0);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R,typename A1,typename A2>
struct Function<R(A1,A2)>
{
	R operator()(A1 a1,A2 a2) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		lua::PCall(hLua,2,1,0);

		R   result;
		CheckVarFromLua(hLua,&result,-1);

		lua::Pop(hLua,1);

		return result;
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename A1,typename A2,typename A3>
struct Function<void(A1,A2,A3)>
{
	void operator()(A1 a1,A2 a2,A3 a3) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		lua::PCall(hLua,3,0,0);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R,typename A1,typename A2,typename A3>
struct Function<R(A1,A2,A3)>
{
	R operator()(A1 a1,A2 a2,A3 a3) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		lua::PCall(hLua,3,1,0);

		R   result;
		CheckVarFromLua(hLua,&result,-1);

		lua::Pop(hLua,1);

		return result;
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename A1,typename A2,typename A3,typename A4>
struct Function<void(A1,A2,A3,A4)>
{
	void operator()(A1 a1,A2 a2,A3 a3,A4 a4) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		lua::PCall(hLua,4,0,0);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R,typename A1,typename A2,typename A3,typename A4>
struct Function<R(A1,A2,A3,A4)>
{
	R operator()(A1 a1,A2 a2,A3 a3,A4 a4) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		lua::PCall(hLua,4,1,0);

		R   result;
		CheckVarFromLua(hLua,&result,-1);

		lua::Pop(hLua,1);

		return result;
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename A1,typename A2,typename A3,typename A4,typename A5>
struct Function<void(A1,A2,A3,A4,A5)>
{
	void operator()(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		lua::PCall(hLua,5,0,0);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R,typename A1,typename A2,typename A3,typename A4,typename A5>
struct Function<R(A1,A2,A3,A4,A5)>
{
	R operator()(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		lua::PCall(hLua,5,1,0);

		R   result;
		CheckVarFromLua(hLua,&result,-1);

		lua::Pop(hLua,1);

		return result;
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct Function<void(A1,A2,A3,A4,A5,A6)>
{
	void operator()(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		PushVarToLua(hLua,a6);
		lua::PCall(hLua,6,0,0);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct Function<R(A1,A2,A3,A4,A5,A6)>
{
	R operator()(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		PushVarToLua(hLua,a6);
		lua::PCall(hLua,6,1,0);

		R   result;
		CheckVarFromLua(hLua,&result,-1);

		lua::Pop(hLua,1);

		return result;
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};


}//namespace lua

#endif//_LUAPP_FUNCTION_HPP_
