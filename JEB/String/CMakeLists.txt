cmake_minimum_required(VERSION 2.8)

include(../../CMakeConfig.cmake)

project(Geometry)

set(PUBLIC_HEADERS
    StringPredicates.hpp
    String.hpp
    StringFlags.hpp
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

set(SRC
    StringPredicates.cpp
    String.cpp
    Generic/CharRangeSet.cpp
    Generic/WildcardMatcher.cpp
    Generic/WildcardWord.cpp
    Utf8/Encode.cpp
    )

add_library(JEBString STATIC ${SRC})

if (DEFINED JEB_INSTALL_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/JEB/String)
    install(FILES ${PUBLIC_HEADERS_UTF8} DESTINATION include/JEB/String/Utf8)
    #install(TARGETS JEBString ARCHIVE DESTINATION lib)
endif(DEFINED JEB_INSTALL_API)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)