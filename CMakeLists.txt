cmake_minimum_required(VERSION 2.8)

project(JEBTest)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories(${CMAKE_SOURCE_DIR})
add_definitions(-DJEB_USE_UNIT_TEST_NAMESPACE)

if (APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
    set(CMAKE_INSTALL_PREFIX "/Users/janeb/usr/local")
elseif (WIN32)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    set(CMAKE_INSTALL_PREFIX "D:/Libraries")
endif(APPLE)

add_subdirectory(JEB)
add_library(JEBTest
            $<TARGET_OBJECTS:Collections>
            $<TARGET_OBJECTS:String>
            $<TARGET_OBJECTS:Sys>
            $<TARGET_OBJECTS:Test>
            $<TARGET_OBJECTS:Unicode>
            )

install(TARGETS JEBTest DESTINATION lib)

FIND_PACKAGE(Doxygen)

IF (DOXYGEN_FOUND)
    SET(DOXYGEN_INPUT Doxyfile)
    SET(DOXYGEN_OUTPUT doc/html/index.html)

    ADD_CUSTOM_COMMAND(
      OUTPUT ${DOXYGEN_OUTPUT}
      COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
      COMMAND ${CMAKE_COMMAND} -E echo "Done."
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      DEPENDS ${DOXYGEN_INPUT}
      )

    ADD_CUSTOM_TARGET(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})

    ADD_CUSTOM_TARGET(apidoc_forced
      COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
      COMMAND ${CMAKE_COMMAND} -E echo "Done."
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      )

ENDIF (DOXYGEN_FOUND)
