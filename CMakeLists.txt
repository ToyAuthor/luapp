project(luapp)
cmake_minimum_required(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

set(LUAPP_BINARY_DIR  ${PROJECT_BINARY_DIR}/bin)

# Build lua.
add_subdirectory(lua)

# Just for demo.
add_definitions(-DLUAPP_SCRIPT_PATH="${PROJECT_SOURCE_DIR}/script")

set(LUAPP_INCLUDE_DIR ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lua)
set(LUAPP_LIBRARY_NAME "lua")
set(LUAPP_LIBRARY_DIR ${PROJECT_BINARY_DIR}/lua)

file(COPY ${PROJECT_SOURCE_DIR}/script/ExtensionModule.lua DESTINATION ${PROJECT_BINARY_DIR}/bin/)

add_subdirectory(examples)
