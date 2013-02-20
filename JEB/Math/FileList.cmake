set(JEB_DIR JEB/Math)
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/ArrayMath.hpp
    ${JEB_DIR}/Binomial.hpp
    ${JEB_DIR}/Combinations.hpp
    ${JEB_DIR}/Comparisons.hpp
    ${JEB_DIR}/Constants.hpp
    ${JEB_DIR}/CubicFunction.hpp
    ${JEB_DIR}/Fraction.hpp
    ${JEB_DIR}/Fraction_impl.hpp
    ${JEB_DIR}/FresnelIntegrals.hpp
    ${JEB_DIR}/Limits.hpp
    ${JEB_DIR}/Matrix.hpp
    ${JEB_DIR}/Matrix_impl.hpp
    ${JEB_DIR}/MatrixAlgorithms.hpp
    ${JEB_DIR}/MatrixAlgorithms_impl.hpp
    ${JEB_DIR}/Primes.hpp
    ${JEB_DIR}/Rational.hpp
    ${JEB_DIR}/Subset.hpp
    ${JEB_DIR}/Utilities.hpp
    )

set(JEB_SRC ${JEB_SRC}
    ${JEB_DIR}/CubicFunction.cpp
    ${JEB_DIR}/FresnelIntegrals.cpp
    ${JEB_DIR}/Subset.cpp
    )

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (DEFINED JEB_ENABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(${JEB_DIR}/UnitTest)
endif(DEFINED JEB_ENABLE_UNIT_TESTS)
