set(JEB_DIR JEBTest)
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/AutoSuite.hpp
    ${JEB_DIR}/AutoSuiteRunner.hpp
    ${JEB_DIR}/Comparers.hpp
    ${JEB_DIR}/Error.hpp
    ${JEB_DIR}/Exceptions.hpp
    ${JEB_DIR}/Formatters.hpp
    ${JEB_DIR}/JEBTest.hpp
    ${JEB_DIR}/Macros.hpp
    ${JEB_DIR}/MacroUtilities.hpp
    ${JEB_DIR}/Session.hpp
    )

set(JEB_SRC ${JEB_SRC}
    ${JEB_DIR}/AutoSuite.cpp
    ${JEB_DIR}/AutoSuiteRunner.cpp
    ${JEB_DIR}/Comparers.cpp
    ${JEB_DIR}/Error.cpp
    ${JEB_DIR}/Exceptions.cpp
    ${JEB_DIR}/MacroUtilities.cpp
    ${JEB_DIR}/Session.cpp
    ${JEB_DIR}/Test.cpp
    ${JEB_DIR}/TestSuite.cpp
    )

install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/JEB/Test)
