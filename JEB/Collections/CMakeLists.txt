cmake_minimum_required(VERSION 2.8)

include(../../CMakeConfig.cmake)

project(Collections)

set(PUBLIC_HEADERS
    Array2D.hpp
    Array2D_Impl.hpp
    ArrayUtilities.hpp
    Buffer2D.hpp
    Buffer2D_Impl.hpp
    FromString.hpp
    IntervalMap.hpp
    MapUtilities.hpp
    PairUtilities.hpp
    # PodArray2D.hpp
    SetUtilities.hpp
    ToString.hpp
    UniquePairSet.hpp
    VectorUtlities.hpp
    )

set(SRC
    FromString.cpp
    )

add_library(JEBCollections STATIC ${SRC})

install(FILES ${PUBLIC_HEADERS} DESTINATION include/JEB/Collections)
install(TARGETS JEBCollections ARCHIVE DESTINATION lib)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)