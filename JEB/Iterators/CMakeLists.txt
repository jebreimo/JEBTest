cmake_minimum_required(VERSION 2.8)

include(../../CMakeConfig.cmake)

project(Iterators)

set(PUBLIC_HEADERS
    CircularListIterator.hpp
    Iterators.hpp
    PairInserter.hpp
    )

install(FILES ${PUBLIC_HEADERS} DESTINATION include/JEB/Iterators)
#install(TARGETS Iterators ARCHIVE DESTINATION lib)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)