project(luapp)
cmake_minimum_required(VERSION 2.8)



# Lua.hpp&Lua.cpp need to replaced by Lua.hpp.txt, if you turn on this option.
option(LUAPP_HEAD_FILE_ONLY "If you don't want to create luapp.lib" OFF)


set(CMAKE_BUILD_TYPE Release)

# Build lua.
add_subdirectory(lua)


if(LUAPP_HEAD_FILE_ONLY)
	set(LUAPP_INCLUDE_DIR ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lua)
	set(LUAPP_LIBRARY_NAME "lua")
	set(LUAPP_LIBRARY_DIR ${PROJECT_BINARY_DIR}/lua)
else()
	set(LUAPP_INCLUDE_DIR ${PROJECT_SOURCE_DIR})
	set(LUAPP_LIBRARY_NAME "luapp")
	set(LUAPP_LIBRARY_DIR ${PROJECT_BINARY_DIR})

	#---------Build luapp---------start

	set(SOURCE
		Lua.cpp
		)

	set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

	include_directories(${PROJECT_SOURCE_DIR}/lua)
	link_directories(   ${PROJECT_SOURCE_DIR}/lua)

	add_library(luapp STATIC ${SOURCE})

	target_link_libraries(luapp lua)

	#---------Build luapp---------end

	# Made Visual Studio stoping create debug directory or release directory.
	if(MSVC)
		set_target_properties(luapp PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
			LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
			LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
			RUNTIME_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
			RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
			RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
			ARCHIVE_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
			ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
			ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
		)
	endif()
endif()

file(COPY ${PROJECT_SOURCE_DIR}/examples/script DESTINATION ${PROJECT_BINARY_DIR}/examples)
add_subdirectory(examples)
