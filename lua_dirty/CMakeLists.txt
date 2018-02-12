
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

set(lua_home ${CMAKE_CURRENT_LIST_DIR}/../lua)

set(lua_sources
        ${lua_home}/ltable.h
        ${lua_home}/ltm.h
        ${lua_home}/lua.h
        #${lua_home}/lua.hpp
        ${lua_home}/luaconf.h
        ${lua_home}/lualib.h
        ${lua_home}/lundump.h
        ${lua_home}/lvm.h
        ${lua_home}/lzio.h
        #${lua_home}/Makefile
        ${lua_home}/lapi.c
        ${lua_home}/lauxlib.c
        ${lua_home}/lbaselib.c
        ${lua_home}/lbitlib.c
        ${lua_home}/lcode.c
        ${lua_home}/lcorolib.c
        ${lua_home}/lctype.c
        ${lua_home}/ldblib.c
        ${lua_home}/ldebug.c
        ${lua_home}/ldo.c
        ${lua_home}/ldump.c
        ${lua_home}/lfunc.c
        ${lua_home}/lgc.c
        ${lua_home}/linit.c
        ${lua_home}/liolib.c
        ${lua_home}/llex.c
        ${lua_home}/lmathlib.c
        ${lua_home}/lmem.c
        ${lua_home}/loadlib.c
        ${lua_home}/lobject.c
        ${lua_home}/lopcodes.c
        ${lua_home}/loslib.c
        ${lua_home}/lparser.c
        ${lua_home}/lstate.c
        ${lua_home}/lstring.c
        ${lua_home}/ltable.c
        ${lua_home}/ltablib.c
        ${lua_home}/ltm.c
        #${lua_home}/lua.c
        #${lua_home}/luac.c
        ${lua_home}/lundump.c
        ${lua_home}/lutf8lib.c
        ${lua_home}/lvm.c
        ${lua_home}/lzio.c
        ${lua_home}/lapi.h
        ${lua_home}/lauxlib.h
        ${lua_home}/lcode.h
        ${lua_home}/lctype.h
        ${lua_home}/ldebug.h
        ${lua_home}/ldo.h
        ${lua_home}/lfunc.h
        ${lua_home}/lgc.h
        ${lua_home}/llex.h
        ${lua_home}/llimits.h
        ${lua_home}/lmem.h
        ${lua_home}/lobject.h
        ${lua_home}/lopcodes.h
        ${lua_home}/lparser.h
        ${lua_home}/lprefix.h
        ${lua_home}/lstate.h
        ${lua_home}/lstring.h
        encode_string.c
        encode_string.h
        lstrlib.c
        )

set(self lua)
add_library (${self} STATIC ${lua_sources})

target_include_directories(${self} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../lua)
# other used lua project should include those header files
target_include_directories(${self} INTERFACE
        #${CMAKE_CURRENT_SOURCE_DIR}/src/lua.h
        #${CMAKE_CURRENT_SOURCE_DIR}/src/lua.hpp
        #${CMAKE_CURRENT_SOURCE_DIR}/src/luaconf.h
        #${CMAKE_CURRENT_SOURCE_DIR}/src/lualib.h
        #${CMAKE_CURRENT_SOURCE_DIR}/src/lauxlib.h
        ${CMAKE_CURRENT_LIST_DIR}/include
        )



if(WIN32)
    #target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
    # lua 5.3.4 has no warning compiled on Visual Studio 2017
endif()

if (UNIX)
    # for lua/src/loslib.c:111 use mkstemp instead of use tmpnam
    target_compile_definitions(${self} PRIVATE LUA_USE_POSIX)

    # compile error on CentOS release 5.11 (Final)
    # error message is:
    #  error: #error "Compiler does not support 'long long'.
    #  Use option '-DLUA_32BITS'   or '-DLUA_C89_NUMBERS' (see file 'luaconf.h' for details)"
    #target_compile_definitions(${PROJECT_NAME} PRIVATE LUA_C89_NUMBERS)
    # or
    # this is the lua official way in lua's source code makefile
    target_compile_options(${self} PRIVATE "-std=gnu99")

endif()
#target_compile_definitions(${PROJECT_NAME} PRIVATE LUA_COMPAT_5_2)

