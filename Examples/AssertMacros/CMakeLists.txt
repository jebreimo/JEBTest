cmake_minimum_required(VERSION 2.8)

project(AssertMacros)

set(SRC
    main.cpp
    AssertMacroTest.cpp
    FatalErrorTest.cpp
    CriticalErrorTest.cpp
    )

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} JEBTest)
add_test(JEBTest ${PROJECT_NAME})
