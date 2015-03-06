#include "LuaWrapper.hpp"



namespace lua{
namespace wrapper{

PackList        gFuncList;

int gThunk(lua::Handle L)
{
	int i = (int)lua::ToNumber(L, lua::UpValueIndex(1));

	return gFuncList[i].mProxy->Do(L);
}

}//namespace wrapper
}//namespace lua
