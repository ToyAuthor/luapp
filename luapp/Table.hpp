/**
 * @file   Table.hpp
 * @brief  It's a container looks like lua table.
 */

#pragma once

//----------------------Usage----------------------start
#if 0

#include <iostream>
#include "luapp/Standard.hpp"

int main()
{
	lua::Table  table;
//	lua::Var    table;     // It works too! lua::Var can support following usage.

	table["A"] = "A string";
	table["B"] = 3.14;
	table["C"]["D"] = true;
	table["C"]["E"] = 100;

	/*
	 * Now table structure looks like this
	 * -----------------------------------------
	 *
	 *            ___A :"A string"
	 *           |
	 *   table___|___B :3.14
	 *           |
	 *           |___C ___D :true
	 *                |
	 *                |___E :100
	 *
	 * -----------------------------------------
	 */

	lua::Var   var = table["A"];

	if ( lua::VarType<lua::Str>(var) )
	{
		std::cout << lua::VarCast<lua::Str>(var); // Print "A string"
	}

//	var = table["C"]["E"];      // Don't do this. It may change structure of table.
	var = table>>"C">>"E";      // I recommand you search value by this way.

	if ( lua::VarType<lua::Nil>(var) )
	{
		std::cout << "You search for nothing";
	}

	if ( lua::VarType<lua::Int>(var) )
	{
		std::cout << lua::VarCast<lua::Int>(var); // Print 100
	}

	return 0;
}
#endif
//----------------------Usage----------------------end



#include <map>
#include "luapp/Var.hpp"


namespace lua{


class Table
{
	public:

		class Iterator
		{
			public:

				enum Stage
				{
					INT_STAGE = 0,
					NUM_STAGE = 1,
					STR_STAGE = 2,
					END_STAGE = 3
				};

				~Iterator(){}

				Iterator(const Iterator &other)
				{
					copy_mykind(const_cast<Iterator&>(other));
				}

				// Only called by lua::Table
				Iterator( std::map<lua::Int,lua::Var>::iterator itInt,
				          std::map<lua::Num,lua::Var>::iterator itNum,
				          std::map<lua::Str,lua::Var>::iterator itStr,

				          std::map<lua::Int,lua::Var>::iterator endInt,
				          std::map<lua::Num,lua::Var>::iterator endNum,
				          std::map<lua::Str,lua::Var>::iterator endStr ):_stage(INT_STAGE)
				{
					_itInt = itInt;
					_itNum = itNum;
					_itStr = itStr;

					_endInt = endInt;
					_endNum = endNum;
					_endStr = endStr;

					_eableList[END_STAGE] = true;     // Always true

					_eableList[0] = ( itInt==endInt ) ? false : true;
					_eableList[1] = ( itNum==endNum ) ? false : true;
					_eableList[2] = ( itStr==endStr ) ? false : true;

					while ( ! _eableList[_stage] )
					{
						_stage++;
					}
				}

				Iterator operator = (const Iterator &other)
				{
					copy_mykind(const_cast<Iterator&>(other));
					return *this;
				}

				Iterator& operator ++(   ){it_offset_forward(); return *this;}  // ++i
				Iterator& operator ++(int){it_offset_forward(); return *this;}  // i++
				/*
				Iterator& operator --(   ){it_offset_backward();return *this;}  // --i
				Iterator& operator --(int){it_offset_backward();return *this;}  // i--
				*/

				void getKeyValue(lua::Var *key, lua::Var *value)
				{
					switch ( this->_stage )
					{
						case INT_STAGE:
							*key   = _itInt->first;
							*value = _itInt->second;
							break;
						case NUM_STAGE:
							*key   = _itNum->first;
							*value = _itNum->second;
							break;
						case STR_STAGE:
							*key   = _itStr->first;
							*value = _itStr->second;
							break;
						default:
							*key   = lua::Var();
							*value = lua::Var();
					}
				}

				bool isEnd()
				{
					while ( ! _eableList[_stage] )
					{
						_stage++;
					}

					if ( this->_stage==END_STAGE )
					{
						return true;
					}

					return false;
				}

			private:

				bool   _eableList[4];
				int    _stage;

				std::map<lua::Int,lua::Var>::iterator   _itInt;
				std::map<lua::Num,lua::Var>::iterator   _itNum;
				std::map<lua::Str,lua::Var>::iterator   _itStr;

				std::map<lua::Int,lua::Var>::iterator   _endInt;
				std::map<lua::Num,lua::Var>::iterator   _endNum;
				std::map<lua::Str,lua::Var>::iterator   _endStr;

				inline void copy_mykind(Iterator &other)
				{
					_itInt = other._itInt;
					_itNum = other._itNum;
					_itStr = other._itStr;
					_eableList[0] = other._eableList[0];
					_eableList[1] = other._eableList[1];
					_eableList[2] = other._eableList[2];
					_stage = other._stage;
				}

				void it_offset_forward()
				{
					switch ( this->_stage )
					{
						case INT_STAGE:
							_itInt++;
							if ( _itInt == _endInt )
							{
								_eableList[INT_STAGE] = false;
							}
							break;
						case NUM_STAGE:
							_itNum++;
							if ( _itNum == _endNum )
							{
								_eableList[NUM_STAGE] = false;
							}
							break;
						case STR_STAGE:
							_itStr++;
							if ( _itStr == _endStr )
							{
								_eableList[STR_STAGE] = false;
							}
							break;
						default:
							;  // Nothing have to do.
					}
				}
		};

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

		lua::Var& operator >> (lua::Int key)
		{
			return _mapInt[key];
		}

		lua::Var& operator >> (lua::Num key)
		{
			return _mapNum[key];
		}

		lua::Var& operator >> (lua::Str key)
		{
			return _mapStr[key];
		}

		bool isExist(lua::Int key)
		{
			std::map<lua::Int,lua::Var>::iterator it = _mapInt.find(key);

			if ( it == _mapInt.end() )
			{
				return true;
			}

			return false;
		}

		bool isExist(lua::Num key)
		{
			std::map<lua::Num,lua::Var>::iterator it = _mapNum.find(key);

			if ( it == _mapNum.end() )
			{
				return true;
			}

			return false;
		}

		bool isExist(lua::Str key)
		{
			std::map<lua::Str,lua::Var>::iterator it = _mapStr.find(key);

			if ( it == _mapStr.end() )
			{
				return true;
			}

			return false;
		}

		void swap(lua::Table &bro)
		{
			this->_mapInt.swap( bro._mapInt );
			this->_mapNum.swap( bro._mapNum );
			this->_mapStr.swap( bro._mapStr );
		}

		Iterator getBegin()
		{
			return Iterator( _mapInt.begin(), _mapNum.begin(), _mapStr.begin(),
			                 _mapInt.end(),   _mapNum.end(),   _mapStr.end() );
		}

	private:

		void copy_my_kind(const Table& _bro)
		{
			Table   &bro = const_cast<Table&>(_bro);
			this->_mapInt = bro._mapInt;
			this->_mapNum = bro._mapNum;
			this->_mapStr = bro._mapStr;
		}

		std::map<lua::Int,lua::Var>    _mapInt;
		std::map<lua::Num,lua::Var>    _mapNum;
		std::map<lua::Str,lua::Var>    _mapStr;
	//	std::map<lua::Bool,lua::Var>   _mapBool;  // I don't think we need boolean index.
};

inline lua::Var::Var(const ::lua::Table &t)
{
	this->_ptr = new ::lua::_VarType<lua::Table>(t);
}

inline lua::Var& lua::Var::operator = (const lua::Table &t)
{
	this->free_ptr();
	this->_ptr = new ::lua::_VarType<lua::Table>(t);
	return *this;
}

template<typename T>
lua::Var& ::lua::Var::operator [] (const T key)
{
	if ( ! VarType<lua::Table>(*this) )
	{
		*this = lua::Table();
	}

	return (*(reinterpret_cast<lua::Table*>(this->getPtr())))[key];
}

template<typename T>
const lua::Var& lua::Var::operator >> (const T key) const
{
	static lua::Var   empty_var;

	if ( ! VarType<lua::Table>(*this) )
	{
		return empty_var;
	}

	return (*const_cast<lua::Var*>(this))[key];
}

}//namespace lua
