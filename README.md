# luapp
It's a useful tool for lua. To help you using lua in C++ style and work better with object-oriented programming.

### Features
- [x] Header file only.
- [x] To register C++ class into lua.
- [x] To register C++ global function or member function into lua.
- [x] Read/Write/Add/Remove lua global variable in C++ side.
- [x] Call lua global function in C++ side.
- [x] Be able to create extension module for lua with C++ style.
- [x] Design a C++ container to simulate lua table.
- [x] Design a class whose instances can hold instances of any type supported by luapp.
- [x] Let lua script embedded in C++.
- [x] Be able to require lua script by custom rule.
- [ ] Support C++11.(optional)

### Information
Item                      | Description
--------------------------|----------
**License**               | MIT
**Version**               | 1.2.0 (using Semantic Versioning 2.0.0)
**Supported lua version** | 5.3.0

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
