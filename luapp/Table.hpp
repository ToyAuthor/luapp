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

				//Iterator():_stage(INT_STAGE){}   // Try to remove it
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

				void GetKeyValue(lua::Var *key, lua::Var *value)
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

				bool IsEnd()
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

		Iterator GetBegin()
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
