set(JEB_DIR JEB/String/Utf8)
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/Decode.hpp
    ${JEB_DIR}/Decode_Impl.hpp
    ${JEB_DIR}/Encode.hpp
    ${JEB_DIR}/Encode_Impl.hpp
    ${JEB_DIR}/EscapedString.hpp
    ${JEB_DIR}/EscapedFwdIt.hpp
    ${JEB_DIR}/Utf8Chars.hpp
    )

set(JEB_SRC ${JEB_SRC}
    ${JEB_DIR}/Encode.cpp
    )

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/JEB/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(${JEB_DIR}/UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)
