# JEBTest: A C++ unit testing framework
# Copyright 2013 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(JEB)

set(JEB_DIR JEB)

add_subdirectory(Containers)
add_subdirectory(String)
add_subdirectory(Sys)
add_subdirectory(Test)
add_subdirectory(Text)
add_subdirectory(Unicode)
add_subdirectory(Xml)

set(PUBLIC_HEADERS
    JEBTest.hpp
    )

install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
