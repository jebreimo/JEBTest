cmake_minimum_required(VERSION 2.8)

project(Containers)

set(JEB_DIR JEB/${PROJECT_NAME})

set(PUBLIC_HEADERS
    Interval.hpp
    SetUtilities.hpp
    VectorUtilities.hpp
    )

if (DEFINED JEB_INSTALL_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (DEFINED JEB_INCLUDE_UNIT_TESTS)
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(DEFINED JEB_INCLUDE_UNIT_TESTS)
