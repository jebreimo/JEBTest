set(JEB_DIR JEB/Sys)
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/Environment.hpp
    ${JEB_DIR}/Path.hpp
    ${JEB_DIR}/Users.hpp
    )

set(JEB_SRC ${JEB_SRC}
    ${JEB_DIR}/Environment.cpp
    ${JEB_DIR}/EnvironmentIterator.cpp
    )

if (WIN32)
    set(JEB_PUBLIC_HEADERS ${JEB_PUBLIC_HEADERS}
        ${JEB_DIR}/Path.Win.hpp
        )
    set(JEB_SRC ${JEB_SRC}
        ${JEB_DIR}/Path.Win.cpp
        ${JEB_DIR}/Users.Win.cpp
        )
else (WIN32)
    set(JEB_PUBLIC_HEADERS ${JEB_PUBLIC_HEADERS}
        ${JEB_DIR}/Path.Posix.hpp
        )
    set(JEB_SRC ${JEB_SRC}
        ${JEB_DIR}/Environment.Posix.cpp
        ${JEB_DIR}/Path.Posix.cpp
        ${JEB_DIR}/Users.Posix.cpp
        )
endif (WIN32)

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

if (DEFINED JEB_ENABLE_UNIT_TESTS)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE 1)
    add_subdirectory(${JEB_DIR}/UnitTest)
endif(DEFINED JEB_ENABLE_UNIT_TESTS)
