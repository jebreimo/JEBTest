cmake_minimum_required(VERSION 2.8)

include(../../CMakeConfig.cmake)

project(Unicode)

set(PUBLIC_HEADERS
    CaseConverter.hpp
    CaseInsensitive.hpp
    CaseInsensitive_Impl.hpp
    CharClass.hpp
    CharMap.hpp
    CharMappingTypes.hpp
    StandardLowerCase.hpp
    StandardTitleCase.hpp
    StandardUpperCase.hpp
    Unicode.hpp
    UnicodeChars.hpp
    )

set(SRC
    CaseConverter.cpp
    CaseInsensitive.cpp
    CharClass.cpp
    CharMap.cpp
    CharMappingTypes.cpp
    )

add_library(JEBUnicode STATIC ${SRC})

install(FILES ${PUBLIC_HEADERS} DESTINATION include/JEB/Unicode)
install(TARGETS JEBUnicode ARCHIVE DESTINATION lib)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)