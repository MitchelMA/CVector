add_library(CVector)

file(GLOB VECTOR_HEADERS ./include/*.h)
file(GLOB VECTOR_SOURCES ./private/*.c)

target_sources(CVector
    PRIVATE
    ${VECTOR_SOURCES}
    PUBLIC
    ${VECTOR_HEADERS})

target_include_directories(CVector
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include)
