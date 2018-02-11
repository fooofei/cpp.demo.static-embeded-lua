
cmake_minimum_required (VERSION 2.6)
project(test_liblua)


set(self test_liblua)


set(c_common  ${CMAKE_CURRENT_LIST_DIR}/../c_cpp_common)

add_executable(${self}
        luautils.cpp
        luautils.hpp
        main.cpp
		${c_common}/crt_dbg_leak.h
		${c_common}/crt_dbg_leak.c
		${c_common}/crt_dbg_leak.cpp
        )


if (NOT TARGET lua)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../  build_liblua)
endif ()
target_link_libraries(${self} lua)
target_include_directories(${self} PRIVATE ${c_common})

if(WIN32)
target_compile_options(${self} PRIVATE /source-charset:utf-8 /execution-charset:utf-8)
endif()

if(NOT WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}> ../)
endif()


