/**
@file   Var.hpp
@brief  It works like boost::any.
*/


#pragma once

//-----------------Usage-----------------start
#if 0

#include <iostream>
#include "luapp/Standard.hpp"

template<typename T>
void PrintVar(lua::Var &var)
{
	if ( lua::VarType<lua::Nil>(var) )
	{
		std::cout << "Empty variable" << std::endl;
	}
	else
	{
		if ( lua::VarType<T>(var) ) // Always check the type. Always!
		{
			std::cout << lua::VarCast<T>(var) << std::endl;
		}
		else
		{
			std::cout << "Not correct type!" << std::endl;
		}
	}
}

int main()
{
	lua::Var  var;

	PrintVar<lua::Num>(var);    // Print "Empty variable"
	PrintVar<lua::Str>(var);    // Print "Empty variable"

	//-----------------------------------------------------------

	var = 3.14;

	PrintVar<lua::Num>(var);    // Print 3.14
	PrintVar<lua::Str>(var);    // Print "Not correct type!"

	//-----------------------------------------------------------

	var = "str";

	PrintVar<lua::Num>(var);    // Print "Not correct type!"
	PrintVar<lua::Str>(var);    // Print "str"

	//-----------------------------------------------------------

	var = lua::Nil();

	PrintVar<lua::Num>(var);    // Print "Empty variable"
	PrintVar<lua::Str>(var);    // Print "Empty variable"

	//-----------------------------------------------------------

	// Now this var is a number, not a table.
	var = 100;

	// This var is a table now.
	var[10] = "str";

	PrintVar<lua::Num>(var);    // Print "Not correct type!"
	PrintVar<lua::Str>(var);    // Print "Not correct type!"

	PrintVar<lua::Str>(var[10]);// Print "str"

	return 0;
}

#endif
//-----------------Usage-----------------end



#include <typeinfo>
#include <cstring>
#include "luapp/Config.hpp"
#include "luapp/DataType.hpp"

namespace lua{

//-----------------------------------------------------

#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_

struct _Map_Address;

#endif // _LUAPP_KEEP_LOCAL_LUA_VARIABLE_

//-----------------------------------------------------

struct _VarTypeBase
{
	virtual ~_VarTypeBase(){}
	virtual const std::type_info& getType() const = 0;
	virtual void* getPtr() = 0;
	virtual _VarTypeBase* newMyself() const = 0;
};

template<typename T>
struct _VarType : public _VarTypeBase
{
	_VarType(T t):var(t){}
	~_VarType(){}

	const std::type_info& getType() const
	{
		return typeid(T);
	}

	void* getPtr()
	{
		return reinterpret_cast<void*>(&var);
	}

	_VarTypeBase* newMyself() const
	{
		return new _VarType(this->var);
	}

	T   var;
};

//-----------------------------------------------------

class Var
{
	public:

		Var():_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Nil>(lua::Nil());
		}

		//---------------------nil---------------------
		Var(const lua::Nil t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Nil>(t);
		}
		Var& operator = (const lua::Nil t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Nil>(t);
			return *this;
		}

		//---------------------Integer---------------------
		Var(const int t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Int>(t);
		}
		Var& operator = (const int t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Int>(t);
			return *this;
		}
		Var(const long int t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Int>(t);
		}
		Var& operator = (const long int t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Int>(t);
			return *this;
		}
		Var(const long long t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Int>(t);
		}
		Var& operator = (const long long t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Int>(t);
			return *this;
		}

		//---------------------String---------------------
		Var(const lua::Str t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Str>(t);
		}
		Var& operator = (const lua::Str t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Str>(t);
			return *this;
		}
		Var(const char *t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Str>(lua::Str(t));
		}
		Var& operator = (const char *t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Str>(lua::Str(t));
			return *this;
		}

		//---------------------Pointer---------------------
		Var(const lua::Ptr t):_ptr(0)
		{
			#ifdef _LUAPP_CPP11_
			if ( t==nullptr ) {
			#else
			if ( t==NULL ) {
			#endif
				this->_ptr = new lua::_VarType<lua::Nil>(lua::Nil());
			}
			else{
				this->_ptr = new lua::_VarType<lua::Ptr>(t);
			}
		}
		Var& operator = (const lua::Ptr t)
		{
			free_ptr();
			#ifdef _LUAPP_CPP11_
			if ( t==nullptr ) {
			#else
			if ( t==NULL ) {
			#endif
				this->_ptr = new lua::_VarType<lua::Nil>(lua::Nil());
			}
			else {
				this->_ptr = new lua::_VarType<lua::Ptr>(t);
			}
			return *this;
		}

		//---------------------Real---------------------
		Var(const float t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Num>(t);
		}
		Var& operator = (const float t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Num>(t);
			return *this;
		}
		Var(const double t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Num>(t);
		}
		Var& operator = (const double t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Num>(t);
			return *this;
		}

		//---------------------Table---------------------
		// They are implemented at luapp/Table.hpp
		Var(const lua::Table &t);
		Var& operator = (const lua::Table &t);

		//---------------------Boolean---------------------
		Var(const lua::Bool t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Bool>(t);
		}
		Var& operator = (const ::lua::Bool t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Bool>(t);
			return *this;
		}

		//---------------------Map---------------------
		#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
		// They implemented at luapp/Map.hpp
		Var(const lua::Map &t);
		Var& operator = (const lua::Map &t);

		// They implemented at luapp/MorePushAndPull.hpp
		Var& operator = (lua::_Map_Address &t);
		Var(lua::_Map_Address &t);
		#endif

		//---------------------Func---------------------
		#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
		// They are implemented at luapp/Func.hpp
		Var(const lua::Func &t);
		Var& operator = (const lua::Func &t);
		#else
		Var(const lua::Func t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Func>(t);
		}
		Var& operator = (const ::lua::Func t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Func>(t);
			return *this;
		}
		#endif

		//---------------------Thread---------------------
		#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
		// They are implemented at luapp/Task.hpp
		Var(const lua::Task &t);
		Var& operator = (const lua::Task &t);
		#else
		Var(const lua::Task t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::Task>(t);
		}
		Var& operator = (const ::lua::Task t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::Task>(t);
			return *this;
		}
		#endif

		//---------------------User data---------------------
		#ifdef _LUAPP_KEEP_LOCAL_LUA_VARIABLE_
		// They are implemented at luapp/User.hpp
		Var(const lua::User &t);
		Var& operator = (const lua::User &t);
		#else
		Var(const lua::User t):_ptr(0)
		{
			this->_ptr = new lua::_VarType<lua::User>(t);
		}
		Var& operator = (const ::lua::User t)
		{
			free_ptr();
			this->_ptr = new lua::_VarType<lua::User>(t);
			return *this;
		}
		#endif

		Var(const Var& bro):_ptr(0)
		{
			copy_my_kind(bro);
		}

		Var& operator = (const Var& bro)
		{
			copy_my_kind(bro);
			return *this;
		}

		~Var()
		{
			free_ptr();
		};

		/*
		 * It's implemented at luapp/Table.hpp
		 * A shortcut for enter value to this object.
		 * Don't use it to checkout element exist or not.
		 */
		template<typename T>
		Var& operator [] (const T key);

		Var& operator [] (const char* key);

		/*
		 * It's implemented at luapp/Table.hpp
		 * A shortcut for finding value when this is a Table.
		 * Return lua::Nil if this is not a Table or the value not found.
		 */
		template<typename T>
		const Var& operator >> (const T key) const;

		const Var& operator >> (const char* key) const;

		const std::type_info& getType() const
		{
			return _ptr->getType();
		}

		void* getPtr()
		{
			return _ptr->getPtr();
		}

		_VarTypeBase* clone() const
		{
			return _ptr->newMyself();
		}

	private:

		void free_ptr()
		{
			if ( this->_ptr )
			{
				delete _ptr;
				this->_ptr = 0;
			}
		}

		void copy_my_kind(const Var& _bro)
		{
			free_ptr();
			Var   &bro = const_cast<Var&>(_bro);
			this->_ptr  = bro.clone();
		}

		_VarTypeBase*   _ptr;
};

//-----------------------------------------------------

template<typename T>
inline bool VarType(const lua::Var &var)
{
	if ( var.getType()!=typeid(T) )
	{
		return false;
	}

	return true;
}

template<typename T>
inline T VarCast(const lua::Var &var)
{
	if ( ! lua::VarType<T>(var) )
	{
		lua::Log<<"error: see luapp/Var.hpp"<<lua::End;
		return T();
	}

	return *(reinterpret_cast<T*>(const_cast<lua::Var&>(var).getPtr()));
}

//-----------------------------------------------------

}//namespace lua
