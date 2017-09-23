
# only use lua for static link embeded in c/c++

# base on lua version 5.3.4
# download from https://www.lua.org/ftp/lua-5.3.4.tar.gz

# I make the file CMakeLists.txt and the directory include/lua for static link lua
# before use the lua library, you should use the helper file  make_includes.py to
# make the include/lua

cmake_minimum_required (VERSION 2.6)

#project (lua c) # error on Windows,  No CMAKE_c_COMPILER could be found.
project(lua)



if (APPLE)
    set(CMAKE_MACOSX_RPATH 0)
endif ()

set(LUA_SOURCE
        src/ltable.h
        src/ltm.h
        src/lua.h
        src/lua.hpp
        src/luaconf.h
        src/lualib.h
        src/lundump.h
        src/lvm.h
        src/lzio.h
        #src/Makefile
        src/lapi.c
        src/lauxlib.c
        src/lbaselib.c
        src/lbitlib.c
        src/lcode.c
        src/lcorolib.c
        src/lctype.c
        src/ldblib.c
        src/ldebug.c
        src/ldo.c
        src/ldump.c
        src/lfunc.c
        src/lgc.c
        src/linit.c
        src/liolib.c
        src/llex.c
        src/lmathlib.c
        src/lmem.c
        src/loadlib.c
        src/lobject.c
        src/lopcodes.c
        src/loslib.c
        src/lparser.c
        src/lstate.c
        src/lstring.c
        src/lstrlib.c
        src/ltable.c
        src/ltablib.c
        src/ltm.c
        #src/lua.c
        #src/luac.c
        src/lundump.c
        src/lutf8lib.c
        src/lvm.c
        src/lzio.c
        src/lapi.h
        src/lauxlib.h
        src/lcode.h
        src/lctype.h
        src/ldebug.h
        src/ldo.h
        src/lfunc.h
        src/lgc.h
        src/llex.h
        src/llimits.h
        src/lmem.h
        src/lobject.h
        src/lopcodes.h
        src/lparser.h
        src/lprefix.h
        src/lstate.h
        src/lstring.h
        )


add_library (${PROJECT_NAME} STATIC ${LUA_SOURCE})

# other used lua project should include those header files
target_include_directories(${PROJECT_NAME} INTERFACE
        #${CMAKE_CURRENT_SOURCE_DIR}/src/lua.h
        #${CMAKE_CURRENT_SOURCE_DIR}/src/lua.hpp
        #${CMAKE_CURRENT_SOURCE_DIR}/src/luaconf.h
        #${CMAKE_CURRENT_SOURCE_DIR}/src/lualib.h
        #${CMAKE_CURRENT_SOURCE_DIR}/src/lauxlib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

if(WIN32)
    #target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
    # lua 5.3.4 has no warning compiled on Visual Studio 2017
endif()

if (UNIX)
    # for lua/src/loslib.c:111 use mkstemp instead of use tmpnam
    target_compile_definitions(${PROJECT_NAME} PRIVATE LUA_USE_POSIX)
endif()

#target_compile_definitions(${PROJECT_NAME} PRIVATE LUA_COMPAT_5_2)

