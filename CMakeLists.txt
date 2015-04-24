project(luapp)
cmake_minimum_required(VERSION 2.8)


set(CMAKE_BUILD_TYPE Release)

# Build lua.
add_subdirectory(lua)


set(LUAPP_INCLUDE_DIR ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lua)
set(LUAPP_LIBRARY_NAME "lua")
set(LUAPP_LIBRARY_DIR ${PROJECT_BINARY_DIR}/lua)


file(COPY ${PROJECT_SOURCE_DIR}/examples/script DESTINATION ${PROJECT_BINARY_DIR}/examples)
add_subdirectory(examples)
