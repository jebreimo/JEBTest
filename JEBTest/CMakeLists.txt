# JEBTest: A C++ unit testing framework
# Copyright 2013 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(JEBTest_Root)

set(JEB_DIR JEBTest)

add_subdirectory(Test)

set(PUBLIC_HEADERS
    JEBTest.hpp
    )

add_custom_target(${PROJECT_NAME} SOURCES ${PUBLIC_HEADERS})

install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
