set(JEB_DIR JEB/Bits)
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/BitIterator.hpp
    ${JEB_DIR}/Bits.hpp
    ${JEB_DIR}/Bits_Impl.hpp
    ${JEB_DIR}/BitSet.hpp
    ${JEB_DIR}/Endian.hpp
    ${JEB_DIR}/SparseBitSet.hpp
    ${JEB_DIR}/Union16.hpp
    ${JEB_DIR}/Union32.hpp
    ${JEB_DIR}/Union64.hpp
    )

set(JEB_SRC ${JEB_SRC}
    ${JEB_DIR}/BitSet.cpp
    ${JEB_DIR}/SparseBitSet.cpp
    )

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(${JEB_DIR}/UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)
