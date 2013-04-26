cmake_minimum_required(VERSION 2.8)

set(JEB_PROJECT Test)
set(JEB_DIR JEB/${JEB_PROJECT})

project(${JEB_PROJECT})

set(SRC
    AutoSuite.cpp
    AutoSuiteRunner.cpp
    Comparers.cpp
    Error.cpp
    Exceptions.cpp
    MacroUtilities.cpp
    Session.cpp
    Test.cpp
    TestSuite.cpp
    )

set(PUBLIC_HEADERS
    AutoSuite.hpp
    AutoSuiteRunner.hpp
    Comparers.hpp
    Error.hpp
    Exceptions.hpp
    Formatters.hpp
    JEBTest.hpp
    Macros.hpp
    MacroUtilities.hpp
    Session.hpp
    )

add_library(${JEB_PROJECT} OBJECT ${SRC})
install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
