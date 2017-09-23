
cmake_minimum_required (VERSION 2.6)
project(test_liblua)



add_executable(${PROJECT_NAME}
        luautils.cpp
        luautils.hpp
        main.cpp
        )


if (NOT TARGET lua)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../  build_liblua)
endif ()
target_link_libraries(${PROJECT_NAME} lua)

if(NOT WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}> ../)
endif()


