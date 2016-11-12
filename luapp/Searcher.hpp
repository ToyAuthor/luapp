/**
@file   Searcher.hpp
@brief  To find script by custom way.
*/


#ifndef _LUAPP_SEARCHER_HPP_
#define _LUAPP_SEARCHER_HPP_

#include "luapp/LuaAPI.hpp"

namespace lua{

template<int N>
class Searcher
{
	public:

	//	static void setup(lua::Handle L,std::function<lua::Str&(lua::Str)> searcher)
		static void setup(lua::Handle L,lua::Str& (*searcher)(lua::Str))
		{
			Searcher<N>::_findScriptFromBuffer = searcher;
			lua::PushFunction(L,&Searcher<N>::thunk);
			lua::SetGlobal(L,"luapp_searcher");
			lua::DoString(L,"table.insert(package.searchers, 2, luapp_searcher) \n");
		}

	private:

		static int thunk(lua::Handle L)
		{
			lua::Str   name = lua::CheckString(L,1);

			lua::Str&  code = Searcher<N>::_findScriptFromBuffer(name);

			if ( code.empty() )
			{
				printf("error:script not find\n");
				return 1;
			}

			if ( ! lua::LoadScript(L,name,code) )
			{
				printf("%s\n",Searcher<N>::error(L).c_str());
			}

			return 1;
		}

		static lua::Str error(lua::Handle L)
		{
			lua::Var  var;
			lua::CheckVarFromLua(L,&var,-1);

			lua::Str  str("error message not found");

			if ( lua::VarType<lua::Str>(var) )
			{
				str = lua::VarCast<lua::Str>(var);
			//	lua::Pop(L,-1);    I can't make sure it is error message.
			}

			return str;
		}

		static lua::Str& (*_findScriptFromBuffer)(lua::Str);

	//	static std::function<lua::Str&(lua::Str)>   _findScriptFromBuffer;
};

template <int N> lua::Str&    (*Searcher<N>::_findScriptFromBuffer)(lua::Str);
//template <int N> std::function<lua::Str&(lua::Str)> Searcher<N>::_findScriptFromBuffer;

}//namespace lua

#endif//_LUAPP_SEARCHER_HPP_
