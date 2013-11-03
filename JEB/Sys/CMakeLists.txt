cmake_minimum_required(VERSION 2.8)

project(Sys)

set(JEB_DIR JEB/${PROJECT_NAME})

set(PUBLIC_HEADERS
    Environment.hpp
    Path.hpp
    Users.hpp
    )

set(SRC
    Environment.cpp
    EnvironmentIterator.cpp
    PathFilter.cpp
    )

if (WIN32)
    set(PUBLIC_HEADERS
        ${PUBLIC_HEADERS}
        Path.Win.hpp
        )
    set(SRC
        ${SRC}
        Path.Win.cpp
        Users.Win.cpp
        )
else (WIN32)
    set(PUBLIC_HEADERS
        ${PUBLIC_HEADERS}
        Path.Posix.hpp
        )
    set(SRC
        ${SRC}
        Environment.Posix.cpp
        Path.Posix.cpp
        Users.Posix.cpp
        )
endif (WIN32)

add_library(${PROJECT_NAME} OBJECT ${SRC})

if (DEFINED JEB_INSTALL_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (DEFINED JEB_INCLUDE_UNIT_TESTS)
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(DEFINED JEB_INCLUDE_UNIT_TESTS)
