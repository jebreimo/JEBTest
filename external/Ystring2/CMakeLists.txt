##****************************************************************************
## Copyright © 2020 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2020-05-04.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.13)
project(JEBTest_Ystring VERSION 2.1.1)

set(CMAKE_CXX_STANDARD 17)

add_library(JEBTest_Ystring OBJECT
    include/Ystring/Algorithms.hpp
    include/Ystring/CaseInsensitive.hpp
    include/Ystring/Char32Span.hpp
    include/Ystring/CharClass.hpp
    include/Ystring/CodePointConstants.hpp
    include/Ystring/CodePointPredicates.hpp
    include/Ystring/ConvertCase.hpp
    include/Ystring/DecodeUtf8.hpp
    include/Ystring/Subrange.hpp
    include/Ystring/TokenIterator.hpp
    include/Ystring/YstringDefinitions.hpp
    src/Ystring/Algorithms.cpp
    src/Ystring/AlgorithmUtilities.hpp
    src/Ystring/AlgorithmUtilities.cpp
    src/Ystring/CharClass.cpp
    src/Ystring/CharClassTables.hpp
    src/Ystring/ConvertCase.cpp
    src/Ystring/EncodeUtf8.hpp
    src/Ystring/LowerCaseTables.hpp
    src/Ystring/Subrange.cpp
    src/Ystring/TitleCaseTables.hpp
    src/Ystring/UpperCaseTables.hpp
    )

include(GNUInstallDirs)

target_include_directories(JEBTest_Ystring BEFORE
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    )

target_compile_definitions(JEBTest_Ystring
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:YSTRING_EXPORTS>
        ystring=JEBTest_Ystring
    )

target_compile_options(JEBTest_Ystring
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
    )

add_library(JEBTest::Ystring ALIAS JEBTest_Ystring)
