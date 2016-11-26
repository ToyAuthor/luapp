/**
 * @file   DataType.hpp
 * @brief  Only These date types could work in luapp and lua
 */

#pragma once

#include <string>

namespace lua{

typedef bool            Bool;
typedef double          Num;
typedef int             Int;
typedef std::string     Str;
typedef void*           Ptr;


struct Nil {};

/*
 * It implemented at luapp/Table.hpp
 * I try to made it looks like lua table.
 */
class Table;

/*
 * It implemented at luapp/Var.hpp
 * It works like boost::any.
 */
class Var;


// For function, userdata, thread
struct RestType {};

#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
class Func;
#endif

}//namespace lua
