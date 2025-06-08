cmake_minimum_required(VERSION 3.25)
project(CVector
    VERSION 1.00
    DESCRIPTION "A simple vector for dynamic memory in C"
    LANGUAGES C)

if (PROJECT_IS_TOP_LEVEL)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

add_subdirectory(libsrc)

target_compile_options(CVector
    PRIVATE
    -std=gnu17)

if (PROJECT_IS_TOP_LEVEL)
    target_compile_options(CVector
        PRIVATE
        -Wall -Wextra -Wpedantic -pedantic -Wundef
        $<$<STREQUAL:$<UPPER_CASE:${CMAKE_BUILD_TYPE}>,DEBUG>:-g -ggdb>
        $<$<STREQUAL:$<UPPER_CASE:${CMAKE_BUILD_TYPE}>,RELEASE>:-Werror -Ofast>)
endif()
