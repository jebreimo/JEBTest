set(JEB_DIR JEB/Unicode)
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/CaseConverter.hpp
    ${JEB_DIR}/CaseInsensitive.hpp
    ${JEB_DIR}/CaseInsensitive_Impl.hpp
    ${JEB_DIR}/CharClass.hpp
    ${JEB_DIR}/CharMap.hpp
    ${JEB_DIR}/CharMappingTypes.hpp
    ${JEB_DIR}/StandardLowerCase.hpp
    ${JEB_DIR}/StandardTitleCase.hpp
    ${JEB_DIR}/StandardUpperCase.hpp
    ${JEB_DIR}/Unicode.hpp
    ${JEB_DIR}/UnicodeChars.hpp
    )

set(JEB_SRC ${JEB_SRC}
    ${JEB_DIR}/CaseConverter.cpp
    ${JEB_DIR}/CaseInsensitive.cpp
    ${JEB_DIR}/CharClass.cpp
    ${JEB_DIR}/CharMap.cpp
    ${JEB_DIR}/CharMappingTypes.cpp
    )

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(${JEB_DIR}/UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)
