set(JEB_STRING_DIR JEB/String)
include(${JEB_STRING_DIR}/8Bit/FileList.cmake)
include(${JEB_STRING_DIR}/Generic/FileList.cmake)
include(${JEB_STRING_DIR}/Utf16/FileList.cmake)
include(${JEB_STRING_DIR}/Utf8/FileList.cmake)

set(JEB_DIR ${JEB_STRING_DIR})
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/StringPredicates.hpp
    ${JEB_DIR}/String.hpp
    ${JEB_DIR}/StringFlags.hpp
    )

set(JEB_SRC ${JEB_SRC}
    ${JEB_DIR}/StringPredicates.cpp
    ${JEB_DIR}/String.cpp
    )

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (DEFINED JEB_ENABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(${JEB_DIR}/UnitTest)
endif(DEFINED JEB_ENABLE_UNIT_TESTS)
