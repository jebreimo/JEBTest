cmake_minimum_required(VERSION 2.8)

project(Unicode)

set(JEB_DIR JEB/${PROJECT_NAME})

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

add_library(${PROJECT_NAME} OBJECT ${SRC})

if (DEFINED JEB_INSTALL_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (DEFINED JEB_INCLUDE_UNIT_TESTS)
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(UnitTest)
endif(DEFINED JEB_INCLUDE_UNIT_TESTS)
