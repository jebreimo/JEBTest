##****************************************************************************
## Copyright © 2020 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2020-05-04.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.16)
project(JEBTest_Yconvert VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

add_library(JEBTest_Yconvert OBJECT
    include/Yconvert/Convert.hpp
    include/Yconvert/Converter.hpp
    include/Yconvert/ConversionException.hpp
    include/Yconvert/Encoding.hpp
    include/Yconvert/ErrorPolicy.hpp
    include/Yconvert/YconvertDefinitions.hpp
    include/Yconvert/YconvertException.hpp
    src/Yconvert/CodePageDecoder.cpp
    src/Yconvert/CodePageDecoder.hpp
    src/Yconvert/CodePageDefinitions.hpp
    src/Yconvert/Convert.cpp
    src/Yconvert/Converter.cpp
    src/Yconvert/DecoderBase.cpp
    src/Yconvert/DecoderBase.hpp
    src/Yconvert/EncoderBase.hpp
    src/Yconvert/EncoderBase.cpp
    src/Yconvert/Encoding.cpp
    src/Yconvert/Utf8Decoder.cpp
    src/Yconvert/Utf8Decoder.hpp
    src/Yconvert/Utf8Encoder.cpp
    src/Yconvert/Utf8Encoder.hpp
    src/Yconvert/Utf16Decoder.hpp
    src/Yconvert/Utf16Encoder.hpp
    src/Yconvert/Utf32Encoder.hpp
    src/Yconvert/Utf32Decoder.hpp
    src/Yconvert/CodePageEncoder.cpp
    src/Yconvert/CodePageEncoder.hpp
    src/Yconvert/YconvertThrow.hpp
    )

target_include_directories(JEBTest_Yconvert BEFORE
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

target_compile_definitions(JEBTest_Yconvert
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
        Yconvert=JEBTest_Yconvert
    )

add_library(JEBTest::Yconvert ALIAS JEBTest_Yconvert)
