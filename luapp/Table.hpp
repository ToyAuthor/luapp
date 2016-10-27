/**
@file   Table.hpp
@brief  It's a container for copy lua table.
*/


#ifndef _LUAPP_TABLE_HPP_
#define _LUAPP_TABLE_HPP_

#include <map>
#include "luapp/Var.hpp"


namespace lua{


class Table
{
	public:

		Table()
		{
			;
		}

		~Table(){}

		Table(const Table& bro)
		{
			copy_my_kind(bro);
		}

		Table& operator = (const Table& bro)
		{
			copy_my_kind(bro);
			return *this;
		}

		lua::Var& operator [] (lua::Int key)
		{
			return _mapInt[key];
		}

		lua::Var& operator [] (lua::Num key)
		{
			return _mapNum[key];
		}

		lua::Var& operator [] (lua::Str key)
		{
			return _mapStr[key];
		}

		bool IsExist(lua::Int key)
		{
			std::map<lua::Int,lua::Var>::iterator it = _mapInt.find(key);

			if ( it == _mapInt.end() )
			{
				return true;
			}

			return false;
		}

		bool IsExist(lua::Num key)
		{
			std::map<lua::Num,lua::Var>::iterator it = _mapNum.find(key);

			if ( it == _mapNum.end() )
			{
				return true;
			}

			return false;
		}

		bool IsExist(lua::Str key)
		{
			std::map<lua::Str,lua::Var>::iterator it = _mapStr.find(key);

			if ( it == _mapStr.end() )
			{
				return true;
			}

			return false;
		}

		lua::Var ToVar()
		{
			return lua::Var(new ::lua::_VarType<lua::Table>(*this) );
		}

	private:

		void copy_my_kind(const Table& _bro)
		{
			Table   &bro = const_cast<Table&>(_bro);
			this->_mapStr = bro._mapStr;
		//	this->_mapInt = bro._mapInt;
		//	this->_mapNum = bro._mapNum;
		}

		std::map<lua::Int,lua::Var>    _mapInt;
		std::map<lua::Num,lua::Var>    _mapNum;
		std::map<lua::Str,lua::Var>    _mapStr;
	//	std::map<lua::Bool,lua::Var>   _mapBool;  // I don't think we need boolean index.
};


::lua::Var::Var(const ::lua::Table &t)
{
	this->_ptr = new ::lua::_VarType< ::lua::Table>(t);
}

::lua::Var& ::lua::Var::operator = (const ::lua::Table &t)
{
	this->free_ptr();
	this->_ptr = new ::lua::_VarType< ::lua::Table>(t);
	return *this;
}

::lua::Var& ::lua::Var::operator [] (const ::lua::Int key)
{
	static ::lua::Var  empty_var;

	if ( ! VarType< ::lua::Table>(*this) )
	{
		return empty_var;             // Return lua::Nil
	}

	return (*(reinterpret_cast< ::lua::Table*>(this->GetPtr())))[key];
}

::lua::Var& ::lua::Var::operator [] (const ::lua::Num key)
{
	static ::lua::Var  empty_var;

	if ( ! VarType< ::lua::Table>(*this) )
	{
		return empty_var;             // Return lua::Nil
	}

	return (*(reinterpret_cast< ::lua::Table*>(this->GetPtr())))[key];
}

::lua::Var& ::lua::Var::operator [] (const ::lua::Str key)
{
	static ::lua::Var  empty_var;

	if ( ! VarType< ::lua::Table>(*this) )
	{
		return empty_var;             // Return lua::Nil
	}

	return (*(reinterpret_cast< ::lua::Table*>(this->GetPtr())))[key];
}

}//namespace lua

#endif//_LUAPP_TABLE_HPP_
