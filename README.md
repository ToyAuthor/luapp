# luapp
It's a useful tool for lua. To help you use lua in C++ style and work better with object-oriented programming.

### Features
- [x] Header file only.
- [x] To register C++ class into lua.
- [x] C++ and lua could call each other's function.
- [x] Read/Write/Add/Remove lua global variable at C++ side.
- [x] Lua could send any variable to C++, and C++ could send them back.
- [x] Support to create C extension module.
- [x] Implement a C++ container to simulate lua table.
- [x] Implement a class whose instances can hold instances of any type supported by luapp.
- [x] Let lua script embedded in C++.
- [x] Be able to search lua script by custom rule.
- [ ] Support to call lua function that has multiple return value.

### Requirements
- CMake 2.8+
- Lua 5.3+

### Information
Item        | Description
------------|-------------
**Author**  | Yan Xin Wu
**License** | MIT
**Version** | 2.2.0 (using Semantic Versioning 2.0.0)

### Example

```lua
-- ClassIntoLua.lua

object = NewObject()

num = object:count(3,4)

print("3 + 4 = " .. num)
```

```c++
// main.cpp

#include <luapp.hpp>

class MyClass
{
public:

	MyClass(){}

	~MyClass(){}

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
