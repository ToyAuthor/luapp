project(EditTable)


if(MINGW)
	add_definitions(-O2 -g -Wall -Wextra -Werror -std=c++11 -Wno-sizeof-pointer-div)
elseif(UNIX)
	add_definitions(-O2 -g -Wall -Wextra -Werror -std=c++11)
endif()


set(NAME "EditTable")

include_directories(${LUAPP_INCLUDE_DIR})
link_directories(   ${LUAPP_LIBRARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LUAPP_BINARY_DIR})

add_executable(${NAME} EditTable.cpp)

target_link_libraries(${NAME} ${LUAPP_LIBRARY_NAME})


if(MSVC)
	set_target_properties(${NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY            ${LUAPP_BINARY_DIR}
		RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${LUAPP_BINARY_DIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${LUAPP_BINARY_DIR}
	)
endif()
