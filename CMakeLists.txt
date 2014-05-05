# JEBTest: A C++ unit testing framework
# Copyright 2013 Jan Erik Breimo
# All rights reserved.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
cmake_minimum_required(VERSION 2.8)

project(JEBTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories(${CMAKE_SOURCE_DIR})
add_definitions(-DJEB_USE_UNIT_TEST_NAMESPACE)

if (APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -Wall")
elseif (WIN32)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif (APPLE)

add_subdirectory(JEB)
add_subdirectory(JEBTest)
add_library(JEBTest
            $<TARGET_OBJECTS:String>
            $<TARGET_OBJECTS:Sys>
            $<TARGET_OBJECTS:Test>
            $<TARGET_OBJECTS:Text>
            $<TARGET_OBJECTS:Unicode>
            $<TARGET_OBJECTS:Xml>
            )
add_subdirectory(Examples)

install(TARGETS JEBTest DESTINATION lib)
# 
# find_package(Doxygen)
# 
# if (DOXYGEN_FOUND)
#     set(DOXYGEN_INPUT Doxyfile)
#     set(DOXYGEN_OUTPUT doc/html/index.html)
# 
#     add_custom_command(
#       OUTPUT ${DOXYGEN_OUTPUT}
#       COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
#       COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
#       COMMAND ${CMAKE_COMMAND} -E echo "Done."
#       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#       DEPENDS ${DOXYGEN_INPUT}
#       )
# 
#     add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})
# 
#     add_custom_target(apidoc_forced
#       COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
#       COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
#       COMMAND ${CMAKE_COMMAND} -E echo "Done."
#       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#       )
# endif (DOXYGEN_FOUND)
