/**
@file   LuaFunctionExt.hpp
@brief  A multiple return value version of "LuaFunction.hpp".
<pre>
It's not finish yet(maybe never do).
Too many template have to be done.
</pre>
*/

#ifndef _LUAPP_FUNCTION_EXT_HPP_
#define _LUAPP_FUNCTION_EXT_HPP_


#include "Lua.hpp"



namespace lua{

template<typename R,typename A>
struct FunctionExt{};

//------------------------------------------------------------

template<typename R1,typename R2>
struct FunctionExt<void(R1,R2),void(void)>
{
	void operator()(R1 *r1,R2 *r2) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		lua::PCall(hLua,0,2,0);

		CheckVarFromLua(hLua,r1,-2);
		CheckVarFromLua(hLua,r2,-1);

		lua::Pop(hLua,2);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename A1>
struct FunctionExt<void(R1,R2),void(A1)>
{
	void operator()(R1 *r1,R2 *r2,A1 a1) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		lua::PCall(hLua,1,2,0);

		CheckVarFromLua(hLua,r1,-2);
		CheckVarFromLua(hLua,r2,-1);

		lua::Pop(hLua,2);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename A1,typename A2>
struct FunctionExt<void(R1,R2),void(A1,A2)>
{
	void operator()(R1 *r1,R2 *r2,A1 a1,A2 a2) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		lua::PCall(hLua,2,2,0);

		CheckVarFromLua(hLua,r1,-2);
		CheckVarFromLua(hLua,r2,-1);

		lua::Pop(hLua,2);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename A1,typename A2,typename A3>
struct FunctionExt<void(R1,R2),void(A1,A2,A3)>
{
	void operator()(R1 *r1,R2 *r2,A1 a1,A2 a2,A3 a3) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		lua::PCall(hLua,3,2,0);

		CheckVarFromLua(hLua,r1,-2);
		CheckVarFromLua(hLua,r2,-1);

		lua::Pop(hLua,2);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename A1,typename A2,typename A3,typename A4>
struct FunctionExt<void(R1,R2),void(A1,A2,A3,A4)>
{
	void operator()(R1 *r1,R2 *r2,A1 a1,A2 a2,A3 a3,A4 a4) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		lua::PCall(hLua,4,2,0);

		CheckVarFromLua(hLua,r1,-2);
		CheckVarFromLua(hLua,r2,-1);

		lua::Pop(hLua,2);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename A1,typename A2,typename A3,typename A4,typename A5>
struct FunctionExt<void(R1,R2),void(A1,A2,A3,A4,A5)>
{
	void operator()(R1 *r1,R2 *r2,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		lua::PCall(hLua,5,2,0);

		CheckVarFromLua(hLua,r1,-2);
		CheckVarFromLua(hLua,r2,-1);

		lua::Pop(hLua,2);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct FunctionExt<void(R1,R2),void(A1,A2,A3,A4,A5,A6)>
{
	void operator()(R1 *r1,R2 *r2,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		PushVarToLua(hLua,a6);
		lua::PCall(hLua,6,2,0);

		CheckVarFromLua(hLua,r1,-2);
		CheckVarFromLua(hLua,r2,-1);

		lua::Pop(hLua,2);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

//------------------------------------------------------------

template<typename R1,typename R2,typename R3>
struct FunctionExt<void(R1,R2,R3),void(void)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		lua::PCall(hLua,0,3,0);

		CheckVarFromLua(hLua,r1,-3);
		CheckVarFromLua(hLua,r2,-2);
		CheckVarFromLua(hLua,r3,-1);

		lua::Pop(hLua,3);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename A1>
struct FunctionExt<void(R1,R2,R3),void(A1)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,A1 a1) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		lua::PCall(hLua,1,3,0);

		CheckVarFromLua(hLua,r1,-3);
		CheckVarFromLua(hLua,r2,-2);
		CheckVarFromLua(hLua,r3,-1);

		lua::Pop(hLua,3);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename A1,typename A2>
struct FunctionExt<void(R1,R2,R3),void(A1,A2)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,A1 a1,A2 a2) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		lua::PCall(hLua,2,3,0);

		CheckVarFromLua(hLua,r1,-3);
		CheckVarFromLua(hLua,r2,-2);
		CheckVarFromLua(hLua,r3,-1);

		lua::Pop(hLua,3);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename A1,typename A2,typename A3>
struct FunctionExt<void(R1,R2,R3),void(A1,A2,A3)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,A1 a1,A2 a2,A3 a3) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		lua::PCall(hLua,3,3,0);

		CheckVarFromLua(hLua,r1,-3);
		CheckVarFromLua(hLua,r2,-2);
		CheckVarFromLua(hLua,r3,-1);

		lua::Pop(hLua,3);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename A1,typename A2,typename A3,typename A4>
struct FunctionExt<void(R1,R2,R3),void(A1,A2,A3,A4)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,A1 a1,A2 a2,A3 a3,A4 a4) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		lua::PCall(hLua,4,3,0);

		CheckVarFromLua(hLua,r1,-3);
		CheckVarFromLua(hLua,r2,-2);
		CheckVarFromLua(hLua,r3,-1);

		lua::Pop(hLua,3);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename A1,typename A2,typename A3,typename A4,typename A5>
struct FunctionExt<void(R1,R2,R3),void(A1,A2,A3,A4,A5)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		lua::PCall(hLua,5,3,0);

		CheckVarFromLua(hLua,r1,-3);
		CheckVarFromLua(hLua,r2,-2);
		CheckVarFromLua(hLua,r3,-1);

		lua::Pop(hLua,3);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct FunctionExt<void(R1,R2,R3),void(A1,A2,A3,A4,A5,A6)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		PushVarToLua(hLua,a6);
		lua::PCall(hLua,6,3,0);

		CheckVarFromLua(hLua,r1,-3);
		CheckVarFromLua(hLua,r2,-2);
		CheckVarFromLua(hLua,r3,-1);

		lua::Pop(hLua,3);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

//------------------------------------------------------------

template<typename R1,typename R2,typename R3,typename R4>
struct FunctionExt<void(R1,R2,R3,R4),void(void)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		lua::PCall(hLua,0,4,0);

		CheckVarFromLua(hLua,r1,-4);
		CheckVarFromLua(hLua,r2,-3);
		CheckVarFromLua(hLua,r3,-2);
		CheckVarFromLua(hLua,r4,-1);

		lua::Pop(hLua,4);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename A1>
struct FunctionExt<void(R1,R2,R3,R4),void(A1)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,A1 a1) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		lua::PCall(hLua,1,4,0);

		CheckVarFromLua(hLua,r1,-4);
		CheckVarFromLua(hLua,r2,-3);
		CheckVarFromLua(hLua,r3,-2);
		CheckVarFromLua(hLua,r4,-1);

		lua::Pop(hLua,4);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename A1,typename A2>
struct FunctionExt<void(R1,R2,R3,R4),void(A1,A2)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,A1 a1,A2 a2) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		lua::PCall(hLua,2,4,0);

		CheckVarFromLua(hLua,r1,-4);
		CheckVarFromLua(hLua,r2,-3);
		CheckVarFromLua(hLua,r3,-2);
		CheckVarFromLua(hLua,r4,-1);

		lua::Pop(hLua,4);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename A1,typename A2,typename A3>
struct FunctionExt<void(R1,R2,R3,R4),void(A1,A2,A3)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,A1 a1,A2 a2,A3 a3) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		lua::PCall(hLua,3,4,0);

		CheckVarFromLua(hLua,r1,-4);
		CheckVarFromLua(hLua,r2,-3);
		CheckVarFromLua(hLua,r3,-2);
		CheckVarFromLua(hLua,r4,-1);

		lua::Pop(hLua,4);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename A1,typename A2,typename A3,typename A4>
struct FunctionExt<void(R1,R2,R3,R4),void(A1,A2,A3,A4)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,A1 a1,A2 a2,A3 a3,A4 a4) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		lua::PCall(hLua,4,4,0);

		CheckVarFromLua(hLua,r1,-4);
		CheckVarFromLua(hLua,r2,-3);
		CheckVarFromLua(hLua,r3,-2);
		CheckVarFromLua(hLua,r4,-1);

		lua::Pop(hLua,4);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename A1,typename A2,typename A3,typename A4,typename A5>
struct FunctionExt<void(R1,R2,R3,R4),void(A1,A2,A3,A4,A5)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		lua::PCall(hLua,5,4,0);

		CheckVarFromLua(hLua,r1,-4);
		CheckVarFromLua(hLua,r2,-3);
		CheckVarFromLua(hLua,r3,-2);
		CheckVarFromLua(hLua,r4,-1);

		lua::Pop(hLua,4);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct FunctionExt<void(R1,R2,R3,R4),void(A1,A2,A3,A4,A5,A6)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		PushVarToLua(hLua,a6);
		lua::PCall(hLua,6,4,0);

		CheckVarFromLua(hLua,r1,-4);
		CheckVarFromLua(hLua,r2,-3);
		CheckVarFromLua(hLua,r3,-2);
		CheckVarFromLua(hLua,r4,-1);

		lua::Pop(hLua,4);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

//------------------------------------------------------------

template<typename R1,typename R2,typename R3,typename R4,typename R5>
struct FunctionExt<void(R1,R2,R3,R4,R5),void(void)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		lua::PCall(hLua,0,5,0);

		CheckVarFromLua(hLua,r1,-5);
		CheckVarFromLua(hLua,r2,-4);
		CheckVarFromLua(hLua,r3,-3);
		CheckVarFromLua(hLua,r4,-2);
		CheckVarFromLua(hLua,r5,-1);

		lua::Pop(hLua,5);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename A1>
struct FunctionExt<void(R1,R2,R3,R4,R5),void(A1)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,A1 a1) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		lua::PCall(hLua,1,5,0);

		CheckVarFromLua(hLua,r1,-5);
		CheckVarFromLua(hLua,r2,-4);
		CheckVarFromLua(hLua,r3,-3);
		CheckVarFromLua(hLua,r4,-2);
		CheckVarFromLua(hLua,r5,-1);

		lua::Pop(hLua,5);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename A1,typename A2>
struct FunctionExt<void(R1,R2,R3,R4,R5),void(A1,A2)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,A1 a1,A2 a2) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		lua::PCall(hLua,2,5,0);

		CheckVarFromLua(hLua,r1,-5);
		CheckVarFromLua(hLua,r2,-4);
		CheckVarFromLua(hLua,r3,-3);
		CheckVarFromLua(hLua,r4,-2);
		CheckVarFromLua(hLua,r5,-1);

		lua::Pop(hLua,5);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename A1,typename A2,typename A3>
struct FunctionExt<void(R1,R2,R3,R4,R5),void(A1,A2,A3)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,A1 a1,A2 a2,A3 a3) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		lua::PCall(hLua,3,5,0);

		CheckVarFromLua(hLua,r1,-5);
		CheckVarFromLua(hLua,r2,-4);
		CheckVarFromLua(hLua,r3,-3);
		CheckVarFromLua(hLua,r4,-2);
		CheckVarFromLua(hLua,r5,-1);

		lua::Pop(hLua,5);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename A1,typename A2,typename A3,typename A4>
struct FunctionExt<void(R1,R2,R3,R4,R5),void(A1,A2,A3,A4)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,A1 a1,A2 a2,A3 a3,A4 a4) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		lua::PCall(hLua,4,5,0);

		CheckVarFromLua(hLua,r1,-5);
		CheckVarFromLua(hLua,r2,-4);
		CheckVarFromLua(hLua,r3,-3);
		CheckVarFromLua(hLua,r4,-2);
		CheckVarFromLua(hLua,r5,-1);

		lua::Pop(hLua,5);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename A1,typename A2,typename A3,typename A4,typename A5>
struct FunctionExt<void(R1,R2,R3,R4,R5),void(A1,A2,A3,A4,A5)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		lua::PCall(hLua,5,5,0);

		CheckVarFromLua(hLua,r1,-5);
		CheckVarFromLua(hLua,r2,-4);
		CheckVarFromLua(hLua,r3,-3);
		CheckVarFromLua(hLua,r4,-2);
		CheckVarFromLua(hLua,r5,-1);

		lua::Pop(hLua,5);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct FunctionExt<void(R1,R2,R3,R4,R5),void(A1,A2,A3,A4,A5,A6)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		PushVarToLua(hLua,a6);
		lua::PCall(hLua,6,5,0);

		CheckVarFromLua(hLua,r1,-5);
		CheckVarFromLua(hLua,r2,-4);
		CheckVarFromLua(hLua,r3,-3);
		CheckVarFromLua(hLua,r4,-2);
		CheckVarFromLua(hLua,r5,-1);

		lua::Pop(hLua,5);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

//------------------------------------------------------------

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename R6>
struct FunctionExt<void(R1,R2,R3,R4,R5,R6),void(void)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,R6 *r6) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		lua::PCall(hLua,0,6,0);

		CheckVarFromLua(hLua,r1,-6);
		CheckVarFromLua(hLua,r2,-5);
		CheckVarFromLua(hLua,r3,-4);
		CheckVarFromLua(hLua,r4,-3);
		CheckVarFromLua(hLua,r5,-2);
		CheckVarFromLua(hLua,r6,-1);

		lua::Pop(hLua,6);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename R6,typename A1>
struct FunctionExt<void(R1,R2,R3,R4,R5,R6),void(A1)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,R6 *r6,A1 a1) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		lua::PCall(hLua,1,6,0);

		CheckVarFromLua(hLua,r1,-6);
		CheckVarFromLua(hLua,r2,-5);
		CheckVarFromLua(hLua,r3,-4);
		CheckVarFromLua(hLua,r4,-3);
		CheckVarFromLua(hLua,r5,-2);
		CheckVarFromLua(hLua,r6,-1);

		lua::Pop(hLua,6);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename R6,typename A1,typename A2>
struct FunctionExt<void(R1,R2,R3,R4,R5,R6),void(A1,A2)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,R6 *r6,A1 a1,A2 a2) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		lua::PCall(hLua,2,6,0);

		CheckVarFromLua(hLua,r1,-6);
		CheckVarFromLua(hLua,r2,-5);
		CheckVarFromLua(hLua,r3,-4);
		CheckVarFromLua(hLua,r4,-3);
		CheckVarFromLua(hLua,r5,-2);
		CheckVarFromLua(hLua,r6,-1);

		lua::Pop(hLua,6);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename R6,typename A1,typename A2,typename A3>
struct FunctionExt<void(R1,R2,R3,R4,R5,R6),void(A1,A2,A3)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,R6 *r6,A1 a1,A2 a2,A3 a3) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		lua::PCall(hLua,3,6,0);

		CheckVarFromLua(hLua,r1,-6);
		CheckVarFromLua(hLua,r2,-5);
		CheckVarFromLua(hLua,r3,-4);
		CheckVarFromLua(hLua,r4,-3);
		CheckVarFromLua(hLua,r5,-2);
		CheckVarFromLua(hLua,r6,-1);

		lua::Pop(hLua,6);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename R6,typename A1,typename A2,typename A3,typename A4>
struct FunctionExt<void(R1,R2,R3,R4,R5,R6),void(A1,A2,A3,A4)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,R6 *r6,A1 a1,A2 a2,A3 a3,A4 a4) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		lua::PCall(hLua,4,6,0);

		CheckVarFromLua(hLua,r1,-6);
		CheckVarFromLua(hLua,r2,-5);
		CheckVarFromLua(hLua,r3,-4);
		CheckVarFromLua(hLua,r4,-3);
		CheckVarFromLua(hLua,r5,-2);
		CheckVarFromLua(hLua,r6,-1);

		lua::Pop(hLua,6);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename R6,typename A1,typename A2,typename A3,typename A4,typename A5>
struct FunctionExt<void(R1,R2,R3,R4,R5,R6),void(A1,A2,A3,A4,A5)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,R6 *r6,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		lua::PCall(hLua,5,6,0);

		CheckVarFromLua(hLua,r1,-6);
		CheckVarFromLua(hLua,r2,-5);
		CheckVarFromLua(hLua,r3,-4);
		CheckVarFromLua(hLua,r4,-3);
		CheckVarFromLua(hLua,r5,-2);
		CheckVarFromLua(hLua,r6,-1);

		lua::Pop(hLua,6);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

template<typename R1,typename R2,typename R3,typename R4,typename R5,typename R6,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct FunctionExt<void(R1,R2,R3,R4,R5,R6),void(A1,A2,A3,A4,A5,A6)>
{
	void operator()(R1 *r1,R2 *r2,R3 *r3,R4 *r4,R5 *r5,R6 *r6,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const
	{
		lua::GetGlobal(hLua,mFuncName.c_str());
		PushVarToLua(hLua,a1);
		PushVarToLua(hLua,a2);
		PushVarToLua(hLua,a3);
		PushVarToLua(hLua,a4);
		PushVarToLua(hLua,a5);
		PushVarToLua(hLua,a6);
		lua::PCall(hLua,6,6,0);

		CheckVarFromLua(hLua,r1,-6);
		CheckVarFromLua(hLua,r2,-5);
		CheckVarFromLua(hLua,r3,-4);
		CheckVarFromLua(hLua,r4,-3);
		CheckVarFromLua(hLua,r5,-2);
		CheckVarFromLua(hLua,r6,-1);

		lua::Pop(hLua,6);
	}
	lua::Handle      hLua;
	lua::Str         mFuncName;
};

//------------------------------------------------------------

}//namespace lua

#endif//_LUAPP_FUNCTION_EXT_HPP_
