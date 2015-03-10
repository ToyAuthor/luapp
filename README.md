# luapp
It's a simple tool for lua.
To help you using lua in C++ style.
There are few features in luapp.

- To register the class and member function into lua.
- To register the global function into lua.
- Get global variable of lua script.
- Call global function of lua script in C++.

### Version
0.1.5

### License
MIT  
Copyright (c) 2015 ToyAuthor

### Example

```lua
-- ClassIntoLua.lua

object = MyClass()

num = object:Count(3,4)

print("3 +4 = " .. num)
```

```c++
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
	lua::State    lua;

	lua.Init();

	lua.RegisterClass<MyClass>("MyClass");

	lua.RegisterMemberFunction("Count",&MyClass::Count);

	lua.DoScript("ClassIntoLua.lua");

	return 0;
}
```
