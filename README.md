# luapp
It's a simple tool for lua.
To help you using lua in C++ style.
There are few features in luapp.

- To register the class and member function from C++ into lua.
- To register the global function from C++ into lua.
- Get global variable of lua script from C++.
- Call global function of lua script from C++.

### Version
0.1.6

### License
MIT  
Copyright (c) 2015 ToyAuthor  
Actually,I don't care if you follow license or not.
You can just only keep lua's copyright.
I'd appreciate it if you keep my name in your project.

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
	lua::State<>    lua;

	lua.Init();

	lua.RegisterClass<MyClass>("MyClass");

	lua.RegisterMemberFunction("Count",&MyClass::Count);

	lua.DoScript("ClassIntoLua.lua");

	return 0;
}
```
