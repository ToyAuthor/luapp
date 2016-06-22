
project(lua)

if(WIN32)
	add_definitions(-DLUA_BUILD_AS_DLL)
endif()

if(MINGW)
	add_definitions(-O2 -g -Wall -Wextra -Werror)
elseif(UNIX)
	# You need use dlopen if you want to create C extension module.
	#add_definitions(-O2 -g -Wall -Wextra -Werror -fPIC -DLUA_USE_LINUX)
	add_definitions(-O2 -g -Wall -Wextra -Werror -fPIC -DLUA_USE_POSIX -DLUA_USE_DLOPEN)
	include_directories(/usr/include)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		link_directories(/usr/lib/x86_64-linux-gnu)
	else()
		link_directories(/usr/lib)
	endif()
endif()

set(SOURCE
	lapi.c
	lauxlib.c
	lbaselib.c
	lbitlib.c
	lcode.c
	lcorolib.c
	lctype.c
	ldblib.c
	ldebug.c
	ldo.c
	ldump.c
	lfunc.c
	lgc.c
	linit.c
	liolib.c
	llex.c
	lmathlib.c
	lmem.c
	loadlib.c
	lobject.c
	lopcodes.c
	loslib.c
	lparser.c
	lstate.c
	lstring.c
	lstrlib.c
	ltable.c
	ltablib.c
	ltm.c
	lundump.c
	lutf8lib.c
	lvm.c
	lzio.c
	)


set_source_files_properties(${SOURCE} PROPERTIES LANGUAGE C)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_library(lua SHARED ${SOURCE})

if(UNIX)
	# Link them if you want to create C extension module.
	target_link_libraries(lua dl m)
endif()

if(MSVC)
	set_target_properties( lua PROPERTIES
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
