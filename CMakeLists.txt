##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-08-06.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.16)
project(JEBTest VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)

# Set YTEST_MASTER_PROJECT to ON if Ystring is the root level project.
if (NOT DEFINED YTEST_MASTER_PROJECT)
    if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(YTEST_MASTER_PROJECT ON)
    else ()
        set(YTEST_MASTER_PROJECT OFF)
    endif ()
endif ()

# Install option
option(YTEST_INSTALL "Generate the install target" ${YTEST_MASTER_PROJECT})

# Install option
option(YTEST_BUILD_EXAMPLES "Build the examples" ${YTEST_MASTER_PROJECT})

add_subdirectory(external/Ystring2)
add_subdirectory(external/Yconvert)

add_library(JEBTest STATIC
    include/JEBTest/AutoTest.hpp
    include/JEBTest/AutoTestRunner.hpp
    include/JEBTest/Comparers.hpp
    include/JEBTest/Error.hpp
    include/JEBTest/Exceptions.hpp
    include/JEBTest/Formatters.hpp
    include/JEBTest/Macros.hpp
    include/JEBTest/MacroUtilities.hpp
    include/JEBTest/Session.hpp
    include/JEBTest/TestScope.hpp
    include/JEBTest/JEBTest.hpp
    include/JEBTest/JEBTestMain.hpp
    src/JEBTest/AutoTest.cpp
    src/JEBTest/AutoTestRunner.cpp
    src/JEBTest/Error.cpp
    src/JEBTest/Formatters.cpp
    src/JEBTest/Indentation.cpp
    src/JEBTest/Indentation.hpp
    src/JEBTest/JUnitReport.cpp
    src/JEBTest/JUnitReport.hpp
    src/JEBTest/MacroUtilities.cpp
    src/JEBTest/ParseArguments.cpp
    src/JEBTest/ParseArguments.hpp
    src/JEBTest/PathFilter.cpp
    src/JEBTest/PathFilter.hpp
    src/JEBTest/Session.cpp
    src/JEBTest/StreamRedirection.cpp
    src/JEBTest/StreamRedirection.hpp
    src/JEBTest/Test.cpp
    src/JEBTest/Test.hpp
    src/JEBTest/TextReport.cpp
    src/JEBTest/TextReport.hpp
    src/JEBTest/VisualStudioReport.cpp
    src/JEBTest/VisualStudioReport.hpp
    src/JEBTest/XmlWriter.cpp
    src/JEBTest/XmlWriter.hpp
    $<TARGET_OBJECTS:JEBTest::Ystring>
    $<TARGET_OBJECTS:JEBTest::Yconvert>
    )

target_compile_definitions(JEBTest
    PRIVATE
    $<$<BOOL:${MSVC}>:_SCL_SECURE_NO_WARNINGS>
    Yconvert=JEBTest_Yconvert
    Ystring=JEBTest_Ystring
    )

set_target_properties(JEBTest
    PROPERTIES
    DEBUG_OUTPUT_NAME "JEBTest.debug"
    )

include(GNUInstallDirs)

target_include_directories(JEBTest
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/Yconvert/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/Ystring2/include
    )

add_library(JEBTest::JEBTest ALIAS JEBTest)

if (YTEST_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

export(TARGETS JEBTest
    NAMESPACE
    JEBTest::
    FILE
    JEBTestConfig.cmake
    )

if (YTEST_INSTALL)
    install(TARGETS JEBTest
        EXPORT JEBTestConfig
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

    install(EXPORT JEBTestConfig
        FILE
        JEBTestConfig.cmake
        NAMESPACE
        JEBTest::
        DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/JEBTest
        )

    install(
        DIRECTORY
        include/
        DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
    )

    include(CMakePackageConfigHelpers)

    write_basic_package_version_file(JEBTestConfigVersion.cmake
        COMPATIBILITY SameMajorVersion
        )

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/JEBTestConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/JEBTest
        )
endif ()
