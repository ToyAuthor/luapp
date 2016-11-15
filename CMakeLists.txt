project(luapp)
cmake_minimum_required(VERSION 2.8)


set(CMAKE_BUILD_TYPE Release)

set(LUAPP_BINARY_DIR  ${PROJECT_BINARY_DIR}/bin)

# Build lua.
add_subdirectory(lua)

add_definitions(-DLUAPP_SCRIPT_PATH="${PROJECT_SOURCE_DIR}/script/")

set(LUAPP_INCLUDE_DIR ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lua)
set(LUAPP_LIBRARY_NAME "lua")
set(LUAPP_LIBRARY_DIR ${PROJECT_BINARY_DIR}/lua)


add_subdirectory(examples)
