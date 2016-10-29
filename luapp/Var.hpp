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
#include "luapp/Define.hpp"
#include "luapp/DataType.hpp"

namespace lua{

//-----------------------------------------------------

struct _VarTypeBase
{
	virtual ~_VarTypeBase(){}
	virtual const std::type_info& GetType() const = 0;
	virtual void* GetPtr() = 0;
	virtual _VarTypeBase* NewMyself() const = 0;
};

template<typename T>
struct _VarType : public _VarTypeBase
{
	_VarType(T t):var(t){}
	~_VarType(){}

	const std::type_info& GetType() const
	{
		return typeid(T);
	}

	void* GetPtr()
	{
		return reinterpret_cast<void*>(&var);
	}

	_VarTypeBase* NewMyself() const
	{
		return new _VarType(this->var);
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

		//---------------------nil---------------------
		Var(const ::lua::Nil t)
		{
			this->_ptr = new ::lua::_VarType<lua::Nil>(t);
		}
		Var& operator = (const ::lua::Nil t)
		{
			free_ptr();
			this->_ptr = new ::lua::_VarType<lua::Nil>(t);
			return *this;
		}

		//---------------------Integer---------------------
		Var(const ::lua::Int t)
		{
			this->_ptr = new ::lua::_VarType<lua::Int>(t);
		}
		Var& operator = (const ::lua::Int t)
		{
			free_ptr();
			this->_ptr = new ::lua::_VarType<lua::Int>(t);
			return *this;
		}

		//---------------------String---------------------
		Var(const ::lua::Str t)
		{
			this->_ptr = new ::lua::_VarType<lua::Str>(t);
		}
		Var& operator = (const ::lua::Str t)
		{
			free_ptr();
			this->_ptr = new ::lua::_VarType<lua::Str>(t);
			return *this;
		}
		Var(const char *t)
		{
			this->_ptr = new ::lua::_VarType<lua::Str>(lua::Str(t));
		}
		Var& operator = (const char *t)
		{
			free_ptr();
			this->_ptr = new ::lua::_VarType<lua::Str>(lua::Str(t));
			return *this;
		}

		//---------------------Pointer---------------------
		Var(const ::lua::Ptr t)
		{
			#ifdef _LUAPP_USING_CPP11_
			if ( t==nullptr ) {
			#else
			if ( t==NULL ) {
			#endif
				this->_ptr = new ::lua::_VarType<lua::Nil>(lua::Nil());
			}
			else{
				this->_ptr = new ::lua::_VarType<lua::Ptr>(t);
			}
		}
		Var& operator = (const ::lua::Ptr t)
		{
			free_ptr();
			#ifdef _LUAPP_USING_CPP11_
			if ( t==nullptr ) {
			#else
			if ( t==NULL ) {
			#endif
				this->_ptr = new ::lua::_VarType<lua::Nil>(lua::Nil());
			}
			else {
				this->_ptr = new ::lua::_VarType<lua::Ptr>(t);
			}
			return *this;
		}

		//---------------------Double---------------------
		Var(const ::lua::Num t)
		{
			this->_ptr = new ::lua::_VarType<lua::Num>(t);
		}
		Var& operator = (const ::lua::Num t)
		{
			free_ptr();
			this->_ptr = new ::lua::_VarType<lua::Num>(t);
			return *this;
		}

		//---------------------Table---------------------
		// They are implemented at luapp/Table.hpp
		Var(const ::lua::Table &t);
		Var& operator = (const ::lua::Table &t);

		//---------------------Boolean---------------------
		Var(const ::lua::Bool t)
		{
			this->_ptr = new ::lua::_VarType<lua::Bool>(t);
		}
		Var& operator = (const ::lua::Bool t)
		{
			free_ptr();
			this->_ptr = new ::lua::_VarType<lua::Bool>(t);
			return *this;
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

		/*
		 * It's implemented at luapp/Table.hpp
		 * A shortcut for enter value to this object.
		 * Don't use it to checkout element exist or not.
		 */
		template<typename T>
		Var& operator [] (const T key);

		const std::type_info& GetType() const
		{
			return _ptr->GetType();
		}

		void* GetPtr()
		{
			return _ptr->GetPtr();
		}

		_VarTypeBase* Clone() const
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
inline bool VarType(const ::lua::Var &var)
{
	if ( var.GetType()!=typeid(T) )
	{
		return false;
	}

	return true;
}

template<typename T>
inline T VarCast(const ::lua::Var &var)
{
	if ( ! ::lua::VarType<T>(var) )
	{
		printf("error: see luapp/Var.hpp\n");
		return T();
	}

	return *(reinterpret_cast<T*>(const_cast< ::lua::Var&>(var).GetPtr()));
}

//-----------------------------------------------------

}//namespace lua

#endif//_LUAPP_VAR_HPP_
