cmake_minimum_required(VERSION 2.8)

set(JEB_PROJECT String)
set(JEB_DIR JEB/${JEB_PROJECT})

project(${JEB_PROJECT})

set(PUBLIC_HEADERS
    String.hpp
    StringConversion.hpp
    StringFlags.hpp
    StringPredicates.hpp
   )

set(SRC
    String.cpp
    StringConversion.cpp
    StringPredicates.cpp
    Generic/CharRangeSet.cpp
    Generic/WildCardMatcher.cpp
    Generic/WildCardWord.cpp
    Utf8/Encode.cpp
   )

set(PUBLIC_HEADERS_UTF8
    Utf8/Decode.hpp
    Utf8/Decode_Impl.hpp
    Utf8/Encode.hpp
    Utf8/Encode_Impl.hpp
    Utf8/EscapedString.hpp
    Utf8/EscapedFwdIt.hpp
    Utf8/Utf8Chars.hpp
   )

add_library(${JEB_PROJECT} OBJECT ${SRC})

if (DEFINED JEB_INSTALL_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
    install(FILES ${PUBLIC_HEADERS_UTF8} DESTINATION include/${JEB_DIR}/Utf8)
endif(DEFINED JEB_INSTALL_API)

if (DEFINED JEB_INCLUDE_UNIT_TESTS)
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(DEFINED JEB_INCLUDE_UNIT_TESTS)
