/**
@file   Var.hpp
@brief  It works like boost::any.
*/


//-----------------Usage-----------------start
#if 0

lua::Var  var("str");
lua::Str  str;

if ( lua::VarType<lua::Str>(var) )
{
	str = lua::VarCast<lua::Str>(var);
}

#endif
//-----------------Usage-----------------end



#ifndef _LUAPP_VAR_HPP_
#define _LUAPP_VAR_HPP_

#include <typeinfo>
#include <cstring>
#include "luapp/DataType.hpp"

namespace lua{

//-----------------------------------------------------

struct _VarTypeBase
{
	virtual ~_VarTypeBase(){}
	virtual const std::type_info& GetType()=0;
	virtual void* GetPtr()=0;
	virtual _VarTypeBase* NewMyself()=0;
};

template<typename T>
struct _VarType : public _VarTypeBase
{
	_VarType(T t):var(t){}
	~_VarType(){}

	const std::type_info& GetType()
	{
		return typeid(T);
	}

	void* GetPtr()
	{
		return reinterpret_cast<void*>(&var);
	}

	_VarTypeBase* NewMyself()
	{
		_VarType  *ptr = new _VarType(T());
		ptr->var = this->var;
		return ptr;
	}

	T   var;
};

//-----------------------------------------------------

class Var
{
	public:

		Var()
		{
			this->_ptr = new ::lua::_VarType<lua::Nil>(lua::Nil());
		}

		Var(::lua::Int t)
		{
			this->_ptr = new ::lua::_VarType<lua::Int>(t);
		}

		Var(::lua::Str t)
		{
			this->_ptr = new ::lua::_VarType<lua::Str>(t);
		}

		Var(const char *t)
		{
			lua::Str   str = t;
			this->_ptr = new ::lua::_VarType<lua::Str>(str);
		}

		Var(::lua::Ptr t)
		{
			this->_ptr = new ::lua::_VarType<lua::Ptr>(t);
		}

		Var(::lua::Num t)
		{
			this->_ptr = new ::lua::_VarType<lua::Num>(t);
		}

		Var(::lua::Bool t)
		{
			this->_ptr = new ::lua::_VarType<lua::Bool>(t);
		}

	//	Var(::lua::Table t)    It's hard to implement this.
		Var(::lua::_VarTypeBase *t)
		{
			this->_ptr = t;
		}

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

		const std::type_info& GetType()
		{
			return _ptr->GetType();
		}

		void* GetPtr()
		{
			return _ptr->GetPtr();
		}

		_VarTypeBase* Clone()
		{
			return _ptr->NewMyself();
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
			this->_ptr  = bro.Clone();
		}

		_VarTypeBase*   _ptr;
};

//-----------------------------------------------------

template<typename T>
inline T VarCast(Var var)
{
	/*
	if ( var.GetType()!=typeid(T) )
	{
		printf("error: see luapp/Var.hpp\n");
		return T();
	}
	*/

	return *(reinterpret_cast<T*>(var.GetPtr()));
}

template<typename T>
inline bool VarType(Var var)
{
	if ( var.GetType()!=typeid(T) )
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------


}//namespace lua

#endif//_LUAPP_VAR_HPP_
