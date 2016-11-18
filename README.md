# luapp
It's a useful tool for lua. To help you use lua in C++ style and work better with object-oriented programming.

### Features
- [x] Header file only.
- [x] To register C++ class into lua.
- [x] To register C++ global function or member function into lua.
- [x] Read/Write/Add/Remove lua global variable at C++ side.
- [x] Call lua global function at C++ side.
- [x] Be able to create extension module for lua in C++ style.
- [x] Design a C++ container to simulate lua table.
- [x] Design a class whose instances can hold instances of any type supported by luapp.
- [x] Let lua script embedded in C++.
- [x] Be able to require lua script by custom rule.
- [ ] Support C++11.(optional)

### Requirements
- CMake 2.8+
- Lua 5.3+

### Information
Item        | Description
------------|----------
**License** | MIT
**Version** | 1.3.0.x (using Semantic Versioning 2.0.0)

### Example

```lua
-- ClassIntoLua.lua

object = NewObject()

num = object:count(3,4)

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

	lua::Int count( lua::Int num01,
	                lua::Int num02)
	{
		return num01 + num02;
	}
};

int main()
{
	lua::State<>    lua;

	lua.bindMethod("count",&MyClass::count);

	lua.bindClassEx<MyClass>("NewObject");

	lua.run("ClassIntoLua.lua");

	return 0;
}
```
