cmake_minimum_required(VERSION 2.8)

set(JEB_LIB_DIR JEB)
include(${JEB_LIB_DIR}/Algorithms/FileList.cmake)
include(${JEB_LIB_DIR}/Bits/FileList.cmake)
include(${JEB_LIB_DIR}/Collections/FileList.cmake)
include(${JEB_LIB_DIR}/Iterators/FileList.cmake)
include(${JEB_LIB_DIR}/Math/FileList.cmake)
include(${JEB_LIB_DIR}/Unicode/FileList.cmake)
include(${JEB_LIB_DIR}/String/FileList.cmake)
include(${JEB_LIB_DIR}/Sys/FileList.cmake)

set(JEB_DIR ${JEB_LIB_DIR})

set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/JEBDefinitions.hpp
    )

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)
