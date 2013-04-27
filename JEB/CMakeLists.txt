cmake_minimum_required(VERSION 2.8)

project(JEB)

set(JEB_DIR JEB)

add_subdirectory(Collections)
add_subdirectory(String)
add_subdirectory(Sys)
add_subdirectory(Test)
add_subdirectory(Unicode)


set(PUBLIC_HEADERS
    JEBTest.hpp
    )

install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
