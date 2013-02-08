set(JEB_DIR JEB/Sys)
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/Console.hpp
    ${JEB_DIR}/Directory.hpp
    ${JEB_DIR}/DirectoryIterator.hpp
    ${JEB_DIR}/Environment.hpp
    ${JEB_DIR}/Path.hpp
    ${JEB_DIR}/Users.hpp
    )

set(JEB_SRC ${JEB_SRC}
    ${JEB_DIR}/Console.cpp
    ${JEB_DIR}/Directory.cpp
    ${JEB_DIR}/Environment.cpp
    ${JEB_DIR}/EnvironmentIterator.cpp
    ${JEB_DIR}/Path.cpp
    )

if (WIN32)
    set(JEB_PUBLIC_HEADERS ${JEB_PUBLIC_HEADERS}
        ${JEB_DIR}/DirectoryIterator.Win.hpp
        ${JEB_DIR}/Path.Win.hpp
        )
    set(JEB_SRC ${JEB_SRC}
        ${JEB_DIR}/DirectoryIterator.Win.cpp
        ${JEB_DIR}/Path.Win.cpp
        ${JEB_DIR}/Users.Win.cpp
        )
else (WIN32)
    set(JEB_PUBLIC_HEADERS ${JEB_PUBLIC_HEADERS}
        ${JEB_DIR}/DirectoryIterator.Posix.hpp
        ${JEB_DIR}/Path.Posix.hpp
        )
    set(JEB_SRC ${JEB_SRC}
        ${JEB_DIR}/DirectoryIterator.Posix.cpp
        ${JEB_DIR}/Environment.Posix.cpp
        ${JEB_DIR}/Path.Posix.cpp
        ${JEB_DIR}/Users.Posix.cpp
        )
endif (WIN32)

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(${JEB_DIR}/UnitTest)
endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)
