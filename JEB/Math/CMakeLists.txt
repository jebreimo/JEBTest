cmake_minimum_required(VERSION 2.8)

include(../../CMakeConfig.cmake)

project(Math)

set(PUBLIC_HEADERS
    ArrayMath.hpp
    Binomial.hpp
    Combinations.hpp
    Comparisons.hpp
    Constants.hpp
    CubicFunction.hpp
    Fraction.hpp
    Fraction_impl.hpp
    FresnelIntegrals.hpp
    Interval.hpp
    Limits.hpp
    Matrix.hpp
    Matrix_impl.hpp
    MatrixAlgorithms.hpp
    MatrixAlgorithms_impl.hpp
    Primes.hpp
    Rational.hpp
    Subset.hpp
    Utilities.hpp
    )

set(SRC
    CubicFunction.cpp
    FresnelIntegrals.cpp
    Subset.cpp
    )

add_library(JEBMath STATIC ${SRC})

install(FILES ${PUBLIC_HEADERS} DESTINATION include/JEB/Math)
install(TARGETS JEBMath ARCHIVE DESTINATION lib)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)