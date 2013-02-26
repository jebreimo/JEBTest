cmake_minimum_required(VERSION 2.8)

project(JEBTest)

if (APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
    add_definitions(-DJEB_USE_UNIT_TEST_NAMESPACE)
    set(CMAKE_INSTALL_PREFIX "/Users/janeb/usr/local")
elseif (WIN32)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-DJEB_USE_UNIT_TEST_NAMESPACE)
    set(CMAKE_INSTALL_PREFIX "C:/Users/JEB/Projects/Workspace/usr/local")
endif(APPLE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories(${CMAKE_SOURCE_DIR})

include(JEB/FileList.cmake)
include(JEBTest/FileList.cmake)

add_library(JEBTest ${JEB_SRC})

install(TARGETS JEBTest DESTINATION lib)
