project(LuaCompiler)


if(MINGW)
	add_definitions(-O2 -g -Wall -Wextra -Werror)
elseif(UNIX)
	add_definitions(-O2 -g -Wall -Wextra -Werror)
endif()


set(NAME "luacompiler")

include_directories(${LUAPP_INCLUDE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

file(GLOB SOURCE ${LUAPP_INCLUDE_DIR}/*.c)

list(APPEND SOURCE luac.c)

add_executable(${NAME} ${SOURCE})

if(MSVC)
	set_target_properties(${NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
		RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
	)
endif()
