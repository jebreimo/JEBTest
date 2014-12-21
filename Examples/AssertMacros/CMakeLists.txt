cmake_minimum_required(VERSION 2.8)

project(AssertMacros)

set(SRC
    main.cpp
    AssertMacroTest.cpp
    CriticalErrorTest.cpp
    FatalErrorTest.cpp
    WarningsTest.cpp
    )

find_package(Boost REQUIRED COMPONENTS filesystem system)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME}
                      JEBTest
                      ${Boost_LIBRARIES}
                     )
add_test(JEBTest ${PROJECT_NAME})
