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

//class Func;   Not support yet.

}//namespace lua
