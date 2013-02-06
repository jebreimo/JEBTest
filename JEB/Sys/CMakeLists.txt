cmake_minimum_required(VERSION 2.8)

include(../../CMakeConfig.cmake)

project(Sys)

set(PUBLIC_HEADERS
    Console.hpp
    Directory.hpp
    DirectoryIterator.hpp
    Environment.hpp
    Path.hpp
    Users.hpp
    )

set(SRC
    Console.cpp
    Directory.cpp
    Environment.cpp
    EnvironmentIterator.cpp
    Path.cpp
    )

if (WIN32)
    set(PUBLIC_HEADERS_SYSDEP
        DirectoryIterator.Win.hpp
        Path.Win.hpp
        )
    set(SRC_SYSDEP
        DirectoryIterator.Win.cpp
        Path.Win.cpp
        Users.Win.cpp
        )
else (WIN32)
    set(PUBLIC_HEADERS_SYSDEP
        DirectoryIterator.Posix.hpp
        Path.Posix.hpp
        )
    set(SRC_SYSDEP
        DirectoryIterator.Posix.cpp
        Environment.Posix.cpp
        Path.Posix.cpp
        Users.Posix.cpp
        )
endif (WIN32)

add_library(JEBSys STATIC ${SRC} ${SRC_SYSDEP})

install(FILES ${PUBLIC_HEADERS} ${PUBLIC_HEADERS_SYSDEP} DESTINATION include/JEB/Sys)
install(TARGETS JEBSys ARCHIVE DESTINATION lib)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)
