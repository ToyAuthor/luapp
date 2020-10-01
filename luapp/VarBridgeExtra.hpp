
#pragma once

#include <cstring>

#include "luapp/LuaAPI.hpp"
#include "luapp/TypeString.hpp"

namespace lua{

//------------------------------------------------------------------------------

template<typename T>
class _ClassZone
{
	public:

		_ClassZone(){}
		~_ClassZone(){}

		static int destructor(lua::NativeState L)
		{
			T* obj = static_cast<T*>(lua::CheckUserData(L, -1, lua::CreateBindingCoreName<T>()));

			obj->~T();

			return 0;
		}

		static void registerType(lua::NativeState hLua,lua::Str &userType)
		{
			lua::GetMetaTable(hLua,userType);                                // ... [?]

			if ( lua::IsType<lua::Nil>(hLua,-1) )
			{
				lua::NewMetaTable(hLua, userType);                           // ... [nil] [T]

				lua::PushString(hLua, "__gc");                               // ... [nil] [T] ["__gc"]
				lua::PushFunction(hLua, &lua::_ClassZone<T>::destructor);    // ... [nil] [T] ["__gc"] [F]
				lua::SetTable(hLua, -3);                                     // ... [nil] [T]
				lua::Pop(hLua,2);                                            // ...
			}
			else
			{
				lua::Pop(hLua,1);                                            // ...
			}
		}
};

inline void _PushCoreKey(lua::NativeState L)
{
	lua::PushInteger(L, 0);
//	lua::PushInteger(L, 1000);
//	lua::PushNumber(L, 0.0001f);
//	lua::PushString(L, "__object_from_cpp");
}

template<typename T>
inline void PushClassToLua(lua::NativeState hLua)
{
	lua::Str   userType = lua::CreateBindingCoreName<T>();

	lua::NewTable(hLua);                                             // ... [T]

	lua::_PushCoreKey(hLua);                                         // ... [T] [key]

	T*  ptr = static_cast<T*>(lua::NewUserData(hLua, sizeof(T)));    // ... [T] [key] [UD]

	new (ptr) T();

	lua::_ClassZone<T>::registerType(hLua,userType);

	lua::GetMetaTable(hLua, userType);                               // ... [T] [key] [UD] [MT]
	lua::SetMetaTable(hLua, -2);                                     // ... [T] [key] [UD]
	lua::SetTable(hLua, -3);                                         // ... [T]
}

template<typename T,typename A1>
inline void PushClassToLua(lua::NativeState hLua,A1 a1)
{
	lua::Str   userType = lua::CreateBindingCoreName<T>();

	lua::NewTable(hLua);                                             // ... [T]

	lua::_PushCoreKey(hLua);                                         // ... [T] [key]

	T*  ptr = static_cast<T*>(lua::NewUserData(hLua, sizeof(T)));    // ... [T] [key] [UD]

	new (ptr) T(a1);

	lua::_ClassZone<T>::registerType(hLua,userType);

	lua::GetMetaTable(hLua, userType);                               // ... [T] [key] [UD] [MT]
	lua::SetMetaTable(hLua, -2);                                     // ... [T] [key] [UD]
	lua::SetTable(hLua, -3);                                         // ... [T]
}

template<typename T,typename A1,typename A2>
inline void PushClassToLua(lua::NativeState hLua,A1 a1,A2 a2)
{
	lua::Str   userType = lua::CreateBindingCoreName<T>();

	lua::NewTable(hLua);                                             // ... [T]

	lua::_PushCoreKey(hLua);                                         // ... [T] [key]

	T*  ptr = static_cast<T*>(lua::NewUserData(hLua, sizeof(T)));    // ... [T] [key] [UD]

	new (ptr) T(a1,a2);

	lua::_ClassZone<T>::registerType(hLua,userType);

	lua::GetMetaTable(hLua, userType);                               // ... [T] [key] [UD] [MT]
	lua::SetMetaTable(hLua, -2);                                     // ... [T] [key] [UD]
	lua::SetTable(hLua, -3);                                         // ... [T]
}

template<typename T,typename A1,typename A2,typename A3>
inline void PushClassToLua(lua::NativeState hLua,A1 a1,A2 a2,A3 a3)
{
	lua::Str   userType = lua::CreateBindingCoreName<T>();

	lua::NewTable(hLua);                                             // ... [T]

	lua::_PushCoreKey(hLua);                                         // ... [T] [key]

	T*  ptr = static_cast<T*>(lua::NewUserData(hLua, sizeof(T)));    // ... [T] [key] [UD]

	new (ptr) T(a1,a2,a3);

	lua::_ClassZone<T>::registerType(hLua,userType);

	lua::GetMetaTable(hLua, userType);                               // ... [T] [key] [UD] [MT]
	lua::SetMetaTable(hLua, -2);                                     // ... [T] [key] [UD]
	lua::SetTable(hLua, -3);                                         // ... [T]
}

template<typename T,typename A1,typename A2,typename A3,typename A4>
inline void PushClassToLua(lua::NativeState hLua,A1 a1,A2 a2,A3 a3,A4 a4)
{
	lua::Str   userType = lua::CreateBindingCoreName<T>();

	lua::NewTable(hLua);                                             // ... [T]

	lua::_PushCoreKey(hLua);                                         // ... [T] [key]

	T*  ptr = static_cast<T*>(lua::NewUserData(hLua, sizeof(T)));    // ... [T] [key] [UD]

	new (ptr) T(a1,a2,a3,a4);

	lua::_ClassZone<T>::registerType(hLua,userType);

	lua::GetMetaTable(hLua, userType);                               // ... [T] [key] [UD] [MT]
	lua::SetMetaTable(hLua, -2);                                     // ... [T] [key] [UD]
	lua::SetTable(hLua, -3);                                         // ... [T]
}

// Not every class could copy new one. It's why output pointer here.
template<typename T>
inline void CheckClassFromLua(lua::NativeState hLua,T **t,int i)
{
	                               // ... [var] ...
	lua::_PushCoreKey(hLua);       // ... [var] ... [key]

	if (i<0)
	{
		lua::GetTable(hLua, i-1);  // ... [var] ... [UD]
	}
	else
	{
		lua::GetTable(hLua, i);    // ... [var] ... [UD]
	}

	T*  obj = static_cast<T*>(lua::CheckUserData(hLua, -1, lua::CreateBindingCoreName<T>()));
	*t = obj;

	lua::Pop(hLua, 1);             // ... [var] ...
}

//------------------------------------------------------------------------------

template<typename T>
inline void PushStructToLua(lua::NativeState hLua,const T &t)
{
	lua::Str   userType = lua::CreateUserType<T>();

	lua::GetMetaTable(hLua,userType);                              // ... [?]

	if ( lua::IsType<lua::Nil>(hLua,-1) )
	{
		lua::NewMetaTable(hLua, userType);                         // ... [nil] [T]
		lua::Pop(hLua,2);                                          // ...
	}
	else
	{
		lua::Pop(hLua,1);                                          // ...
	}

	T*  ptr = static_cast<T*>(lua::NewUserData(hLua, sizeof(T)));  // ... [UD]
	*ptr = t;
	lua::GetMetaTable(hLua, userType);                             // ... [UD] [MT]
	lua::SetMetaTable(hLua, -2);                                   // ... [UD]
}

template<typename T>
inline void CheckStructFromLua(lua::NativeState hLua,T *t,int i)
{
	T*  obj = static_cast<T*>(lua::CheckUserData(hLua, i, lua::CreateUserType<T>()));
	*t = *obj;
}

//------------------------------------------------------------------------------

inline void PushUserDataToLua(lua::NativeState hLua,void *input,size_t size,lua::Str userType)
{
	lua::GetMetaTable(hLua,userType);            // ... [?]

	if ( lua::IsType<lua::Nil>(hLua,-1) )
	{
		lua::NewMetaTable(hLua, userType);       // ... [nil] [T]
		lua::Pop(hLua,2);                        // ...
	}
	else
	{
		lua::Pop(hLua,1);                        // ...
	}

	void*  ptr = lua::NewUserData(hLua, size);   // ... [UD]

	std::memcpy(ptr,input,size);

	lua::GetMetaTable(hLua, userType);           // ... [UD] [MT]
	lua::SetMetaTable(hLua, -2);                 // ... [UD]
}

inline void CheckUserDataFromLua(lua::NativeState hLua,void *output,size_t size,int i,lua::Str userType)
{
	void*  obj = lua::CheckUserData(hLua, i, userType);

	std::memcpy(output,obj,size);
}

//------------------------------------------------------------------------------

// Type T must be able to copied by operator "=".
template<typename T>
class Type
{
	public:

		Type(){}
		~Type(){}

		T   data;
};

template<typename T>
inline void PushVarToLua(lua::NativeState hLua,lua::Type<T> t)
{
	lua::PushStructToLua(hLua,t.data);
}

template<typename T>
inline void CheckVarFromLua(lua::NativeState hLua,lua::Type<T> *t, int i)
{
	lua::CheckStructFromLua(hLua,&(t->data),i);
}

//------------------------------------------------------------------------------

template<typename T>
class Obj
{
	public:

		~Obj(){}

		Obj():_ptr((T*)0),_isComeFromLua(true)
		{
			;
		}

		Obj(T *pointerFromCppSide):_ptr(pointerFromCppSide),_isComeFromLua(false)
		{
			if ( _ptr==(T*)0 )
			{
				lua::Log<<"Error:the C++ object pull from lua can't push back to lua."<<lua::End;
			}
		}

		T* ptr()
		{
			return _ptr;
		}

		T* operator ->()
		{
			return _ptr;
		}

		T& ref()
		{
			return *_ptr;
		}

		bool isComeFromLua()
		{
			return _isComeFromLua;
		}

	private:

		T*     _ptr;
		bool   _isComeFromLua;

	public:

		T** _getPointerAddress()
		{
			return &_ptr;
		}
};

template<typename T>
inline void PushVarToLua(lua::NativeState hLua,lua::Obj<T> t)
{
	if (t.isComeFromLua())
	{
		lua::Log<<"Error:the C++ object pull from lua can't push back to lua."<<lua::End;
	}

	lua::NewTable(hLua);                                             // ... [T]

	lua::GetMetaTable(hLua, lua::CreateBindingMethodName<T>());      // ... [T] [?]

	if ( lua::IsType<lua::Nil>(hLua,-1) )
	{
		lua::Pop(hLua,1);
	}
	else
	{
		lua::SetMetaTable(hLua, -2);
	}

	lua::_PushCoreKey(hLua);                                         // ... [T] [key]

	T*  ptr = static_cast<T*>(lua::NewUserData(hLua, sizeof(T)));    // ... [T] [key] [UD]

	new (ptr) T();

	*ptr = t.ref();
	delete (t.ptr());

	lua::Str   userType = lua::CreateBindingCoreName<T>();

	lua::_ClassZone<T>::registerType(hLua,userType);

	lua::GetMetaTable(hLua, userType);                               // ... [T] [key] [UD] [MT]
	lua::SetMetaTable(hLua, -2);                                     // ... [T] [key] [UD]
	lua::SetTable(hLua, -3);                                         // ... [T]
}

template<typename C>
inline void CheckVarFromLua(lua::NativeState hLua,lua::Obj<C> *obj, int i)
{
	lua::CheckClassFromLua(hLua,obj->_getPointerAddress(),i);
}

//------------------------------------------------------------------------------

}//namespace lua
