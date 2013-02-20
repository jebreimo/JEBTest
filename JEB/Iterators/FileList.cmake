set(JEB_DIR JEB/Iterators)
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/CircularListIterator.hpp
    ${JEB_DIR}/Iterators.hpp
    ${JEB_DIR}/PairInserter.hpp
    )

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (DEFINED JEB_ENABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(${JEB_DIR}/UnitTest)
endif(DEFINED JEB_ENABLE_UNIT_TESTS)
