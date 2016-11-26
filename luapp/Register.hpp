
#pragma once

#include "luapp/Var.hpp"
#include "luapp/LuaAPI.hpp"
#include "luapp/stl/memory.hpp"

namespace lua{


// Only work inside lua::HandleClass.
class Register
{
	public:

		class ItemClass
		{
			public:

				ItemClass(lua::Int id,Register *r):_id(id),_mgr(r)
				{
					;
				}

				~ItemClass()
				{
					_mgr->_remove(_id);
				}

				void setVar()
				{
					_mgr->_setVar(_id);
				}

				void getVar()
				{
					_mgr->_getVar(_id);
				}

				lua::Int   _id;
				Register*  _mgr;
		};

		typedef std::shared_ptr<ItemClass> Item;

		Register(lua::NativeState h):_lua(h)
		{
			buildDataBase();
		}

		~Register(){}

		std::shared_ptr<ItemClass> newItem()
		{
			return std::shared_ptr<ItemClass>(new ItemClass(createUniqueID(),this));
		}

		void _setVar(lua::Int id)
		{
			                                            // ... [V]
			lua::GetGlobal(_lua, "_luapp_data");        // ... [V] [data]
			lua::GetField(_lua,-1, "temp_variable");    // ... [V] [data] [temp]
			lua::PushInteger(_lua,id);                  // ... [V] [data] [temp] [id]
			lua::PushValue(_lua,-4);                    // ... [V] [data] [temp] [id] [V]
			lua::SetTable(_lua,-3);                     // ... [V] [data] [temp]
			lua::Pop(_lua,3);                           // ...
		}

		void _getVar(lua::Int id)
		{
			lua::GetGlobal(_lua, "_luapp_data");        // ... [data]
			lua::GetField(_lua,-1, "temp_variable");    // ... [data] [temp]

			lua::PushInteger(_lua,id);                  // ... [data] [temp] [id]
			lua::GetTable(_lua,-2);                     // ... [data] [temp] [value]

			lua::Replace(_lua,-3);                      // ... [value] [temp]
			lua::Pop(_lua,1);                           // ... [value]
		}

		void _remove(lua::Int id)
		{
			if ( id>=(lua::Int)_list.size() )
			{
				lua::log::Cout<<"error:can't remove a id that doesn't exist."<<lua::log::End;
				return;
			}

			lua::GetGlobal(_lua, "_luapp_data");        // ... [data]
			lua::GetField(_lua,-1, "temp_variable");    // ... [data] [temp]

			lua::PushInteger(_lua,id);                  // ... [data] [temp] [id]
			lua::PushNil(_lua);                         // ... [data] [temp] [id] [nil]
			lua::SetTable(_lua,-3);                     // ... [data] [temp]
			lua::Pop(_lua,2);                           // ...

			_list[id] = false;
		}

	private:

		void buildDataBase()
		{
			lua::NewTable(_lua);                       // ... [T]
			lua::PushString(_lua,"temp_variable");     // ... [T] [temp]
			lua::NewTable(_lua);                       // ... [T] [temp] [value]
			lua::SetTable(_lua,-3);                    // ... [T]
			lua::SetGlobal(_lua, "_luapp_data");       // ...
		}

		lua::Int createUniqueID()
		{
			const lua::Int   ID_NOT_FOUND = -1;

			lua::Int    id = ID_NOT_FOUND;
			lua::Int    size = _list.size();

			if ( size!=0 )
			{
				for ( lua::Int i=0 ; i<size ; i++ )
				{
					if ( _list[i]==false )
					{
						_list[i] = true;
						id = i;
						break;
					}
				}
			}

			if ( id==ID_NOT_FOUND )
			{
				_list.push_back(true);
				id = size;
			}

			#ifdef _LUAPP_CHECK_CAREFUL_
			if ( nameExist(id) )
			{
				lua::log::Cout<<"error:create name already exist."<<lua::log::End;
			}
			#endif

			return id;
		}

		#ifdef _LUAPP_CHECK_CAREFUL_
		bool isNil()
		{
			lua::Var   var;
			lua::CheckVarFromLua(_lua,&var,-1);

			if ( lua::VarType<lua::Nil>(var) )
			{
				return true;
			}

			return false;
		}

		bool nameExist(lua::Int id)
		{
			lua::GetGlobal(_lua, "_luapp_data");        // ... [data]

			if ( isNil() )
			{
				lua::log::Cout<<"error:_G._luapp_data not exist."<<lua::log::End;
				lua::Pop(_lua,1);
				return false;
			}

			lua::GetField(_lua,-1, "temp_variable");    // ... [data] [temp]

			if ( isNil() )
			{
				lua::log::Cout<<"error:_G._luapp_data.temp_variable not exist."<<lua::log::End;
				lua::Pop(_lua,2);
				return false;
			}

			lua::PushInteger(_lua,id);                  // ... [data] [temp] [id]
			lua::GetTable(_lua,-2);                     // ... [data] [temp] [value]

			if ( isNil() )
			{
				lua::Pop(_lua,3);
				return false;
			}

			lua::Pop(_lua,3);
			return true;
		}
		#endif

		lua::NativeState    _lua;
		lua::Str            _name;  // Globle name
		std::vector<bool>   _list;
};



}//namespace lua
