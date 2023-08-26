cmake_minimum_required(VERSION 3.25)
project(CVector
    VERSION 1.00
    DESCRIPTION "A simple vector for dynamic memory in C"
    LANGUAGES C)

set(CMAKE_C_STANDARD 17)

add_subdirectory(libsrc)
