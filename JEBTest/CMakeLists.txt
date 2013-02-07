cmake_minimum_required(VERSION 2.8)

include(../CMakeConfig.cmake)

project(JEBTest)

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
    JEBUnit.hpp
    Macros.hpp
    MacroUtilities.hpp
    Session.hpp
    )

add_library(JEBTest ${SRC})
target_link_libraries(JEBTest
    JEBBits
    JEBCollections
    JEBMath
    JEBString
    JEBSys
    JEBUnicode)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/JEB/Test)
#install(TARGETS JEBTest ARCHIVE DESTINATION lib)
install(TARGETS JEBTest DESTINATION lib)
