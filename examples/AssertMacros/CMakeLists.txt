cmake_minimum_required(VERSION 3.16)

project(AssertMacros)

set(SRC
    main.cpp
    AssertMacroTest.cpp
    CriticalErrorTest.cpp
    FatalErrorTest.cpp
    WarningsTest.cpp
    )

add_executable(AssertMacros ${SRC})

target_link_libraries(AssertMacros JEBTest::JEBTest)
