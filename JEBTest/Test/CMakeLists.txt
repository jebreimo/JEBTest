# JEBTest: A C++ unit testing framework
# Copyright 2013 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(Test)

set(JEB_DIR JEBTest/${PROJECT_NAME})

set(SRC
    AutoTest.cpp
    AutoTestRunner.cpp
    Error.cpp
    Exceptions.cpp
    Formatters.cpp
    JUnitReport.cpp
    MacroUtilities.cpp
    ParseArguments.cpp
    Session.cpp
    Test.cpp
    TextReport.cpp
    VisualStudioReport.cpp
    )

set(PRIVATE_HEADERS
    JUnitReport.hpp
    Test.hpp
    TextReport.hpp
    VisualStudioReport.hpp
    )

set(PUBLIC_HEADERS
    AutoTest.hpp
    AutoTestRunner.hpp
    Comparers.hpp
    Error.hpp
    Exceptions.hpp
    Formatters.hpp
    Macros.hpp
    MacroUtilities.hpp
    ParseArguments.hpp
    Session.hpp
    TestScope.hpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS} ${PRIVATE_HEADERS})
install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
