cmake_minimum_required(VERSION 2.8)

include(../../CMakeConfig.cmake)

project(Algorithms)

set(PUBLIC_HEADERS
    Algorithms.hpp
    Sort.hpp
    )

install(FILES ${PUBLIC_HEADERS} DESTINATION include/JEB/Algorithms)
#install(TARGETS Algorithms ARCHIVE DESTINATION lib)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)