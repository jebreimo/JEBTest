cmake_minimum_required(VERSION 2.8)

project(JEB)

set(JEB_DISABLE_UNIT_TESTS 1)

add_subdirectory(Algorithms)
add_subdirectory(Bits)
add_subdirectory(Collections)
#add_subdirectory(Debug)
#add_subdirectory(Functional)
add_subdirectory(Iterators)
add_subdirectory(Math)
#add_subdirectory(Graphics)
#add_subdirectory(Geometry)
add_subdirectory(Unicode)
add_subdirectory(String)
#add_subdirectory(IO)
add_subdirectory(Sys)
#add_subdirectory(Text)
#add_subdirectory(ArgParser)
#add_subdirectory(Xml)

#set(PUBLIC_HEADERS
#    JEBDefinitions.hpp
#    )

#include(../CMakeConfig.cmake)
#install(FILES ${PUBLIC_HEADERS} DESTINATION include/JEB)
