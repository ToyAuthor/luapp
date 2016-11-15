project(LuaCompiler)


if(MINGW)
	add_definitions(-O2 -g -Wall -Wextra -Werror)
elseif(UNIX)
	add_definitions(-O2 -g -Wall -Wextra -Werror -fPIC -DLUA_USE_POSIX -DLUA_USE_DLOPEN)
endif()


set(NAME "luacompiler")

include_directories(${LUAPP_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LUAPP_BINARY_DIR})

file(GLOB SOURCE ${LUAPP_INCLUDE_DIR}/*.c)

list(APPEND SOURCE luac.c)

add_executable(${NAME} ${SOURCE})

if(UNIX)
	target_link_libraries(${NAME} dl m)
endif()

if(MSVC)
	set_target_properties(${NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY            ${LUAPP_BINARY_DIR}
		RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${LUAPP_BINARY_DIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${LUAPP_BINARY_DIR}
	)
endif()
