# luapp
It's a simple tool for lua.  
To help you using lua in C++ style.

### Features
- [x] Header file only.
- [x] To register the class from C++ into lua.
- [x] To register the global function or member function from C++ into lua.
- [x] Read/Add global variable of lua script from C++.
- [x] Call global function of lua script from C++.
- [x] Create lua module support.
- [ ] Let lua script embedded in C++.
- [ ] Design a C++ container to simulate lua table.

### Version
1.1.0

### Example

```lua
-- ClassIntoLua.lua

object = MyClass()

num = object:Count(3,4)

print("3 + 4 = " .. num)
```

```c++
// main.cpp

#include "luapp.hpp"

class MyClass
{
public:

	MyClass()
	{
		printf("do MyClass::MyClass()\n");
	}

	~MyClass()
	{
		printf("do MyClass::~MyClass()\n");
	}

	lua::Int Count( lua::Int num01,
	                lua::Int num02)
	{
		return num01+num02;
	}
};

int main()
{
	lua::State<>    lua;

	lua.Init();

	lua.RegisterMemberFunction("Count",&MyClass::Count);

	lua.RegisterClassEx<MyClass>("MyClass");

	lua.DoScript("ClassIntoLua.lua");

	return 0;
}
```
