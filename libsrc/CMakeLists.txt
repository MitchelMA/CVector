add_library(CVector)

file(GLOB VECTOR_SOURCES ./private/*.c)

target_sources(CVector
    PRIVATE
    ${VECTOR_SOURCES})

target_include_directories(CVector
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include)

target_compile_options(CVector
    PRIVATE
    -std=gnu17)
