cmake_minimum_required(VERSION 2.8)

project(Sys)

set(JEB_DIR JEB/${PROJECT_NAME})

set(PUBLIC_HEADERS
    StreamRedirection.hpp
    )

set(SRC
    PathFilter.cpp
    StreamRedirection.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})

if (DEFINED JEB_INSTALL_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)
