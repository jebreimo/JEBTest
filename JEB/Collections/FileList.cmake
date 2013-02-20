set(JEB_DIR JEB/Collections)
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/Array2D.hpp
    ${JEB_DIR}/Array2D_Impl.hpp
    ${JEB_DIR}/ArrayUtilities.hpp
    ${JEB_DIR}/Buffer2D.hpp
    ${JEB_DIR}/Buffer2D_Impl.hpp
    ${JEB_DIR}/FromString.hpp
    ${JEB_DIR}/Interval.hpp
    ${JEB_DIR}/IntervalMap.hpp
    ${JEB_DIR}/MapUtilities.hpp
    ${JEB_DIR}/PairUtilities.hpp
    # ${JEB_DIR}/PodArray2D.hpp
    ${JEB_DIR}/SetUtilities.hpp
    ${JEB_DIR}/ToString.hpp
    ${JEB_DIR}/UniquePairSet.hpp
    ${JEB_DIR}/VectorUtilities.hpp
    )

set(JEB_SRC ${JEB_SRC}
    ${JEB_DIR}/FromString.cpp
    )

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (DEFINED JEB_ENABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(${JEB_DIR}/UnitTest)
endif(DEFINED JEB_ENABLE_UNIT_TESTS)
