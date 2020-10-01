/**
 * @file   ToBeClose.cpp
 * @brief  Release resource when table variable quit scope.
 */


#include <cstdlib>
#include <string>
#include <iostream>
#include "luapp.hpp"


/* ToBeClose.lua
-----------------------------------------------------

do
	local object<close> = NewObject()

	object:show()

	print("Quit scope soon")
end

print("Just quit scope")

-----------------------------------------------------
*/

class MyClass
{
	public:

		MyClass()
		{
			_name = new std::string("MyClass");
		}

		~MyClass()
		{
			drop();
		}

		void show()
		{
			if ( _name != NULL )
			{
				std::cout<< *_name <<std::endl;
			}
			else
			{
				std::cout<< "error!" <<std::endl;
			}
		}

		void drop()
		{
			if ( _name != NULL )  // Make sure to free memory only once.
			{
				delete _name;
				_name = NULL;
				std::cout<< "free memory" <<std::endl;
			}
		}

	private:

		std::string   *_name;
};

int main()
{
	lua::State<>    lua;

	lua.bindMethod("show",   &MyClass::show);   // Lua script has member function now.
	lua.bindMethod("__close",&MyClass::drop);   // Setup function to release resource.

	lua.bindClassEx<MyClass>("NewObject");      // Lua script has object now.

	lua.run(LUAPP_SCRIPT_PATH,"ToBeClose.lua");

	return EXIT_SUCCESS;
}
