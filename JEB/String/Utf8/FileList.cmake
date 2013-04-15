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
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)
