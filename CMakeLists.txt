cmake_minimum_required(VERSION 2.8)

project(JEB)

set(JEB_DISABLE_UNIT_TESTS 1)
set(BUILD_SHARED_LIBS true)

add_subdirectory(JEB)
add_subdirectory(JEBTest)

include(./CMakeConfig.cmake)
