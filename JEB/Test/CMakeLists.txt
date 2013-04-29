cmake_minimum_required(VERSION 2.8)

project(Test)

set(JEB_DIR JEB/${PROJECT_NAME})

set(SRC
    AutoSuite.cpp
    AutoSuiteRunner.cpp
    Comparers.cpp
    Error.cpp
    Exceptions.cpp
    MacroUtilities.cpp
    Report.cpp
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
    Macros.hpp
    MacroUtilities.hpp
    Session.hpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
