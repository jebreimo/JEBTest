cmake_minimum_required(VERSION 2.8)

include(../../CMakeConfig.cmake)

project(Bits)

set(PUBLIC_HEADERS
    BitIterator.hpp
    Bits.hpp
    Bits_Impl.hpp
    BitSet.hpp
    Endian.hpp
    SparseBitSet.hpp
    Union16.hpp
    Union32.hpp
    Union64.hpp
    )

set(SRC
    BitSet.cpp
    SparseBitSet.cpp
    )

add_library(JEBBits STATIC ${SRC})

install(FILES ${PUBLIC_HEADERS} DESTINATION include/JEB/Bits)
install(TARGETS JEBBits ARCHIVE DESTINATION lib)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)