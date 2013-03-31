set(JEB_DIR JEB/Debug)
set(JEB_PUBLIC_HEADERS
    ${JEB_DIR}/CpuTimer.hpp
    ${JEB_DIR}/Debug.hpp
    ${JEB_DIR}/Profiler.hpp
    )

if (DEFINED JEB_INSTALL_API)
    install(FILES ${JEB_PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_API)

#if (NOT DEFINED JEB_DISABLE_UNIT_TESTS)
#    enable_testing()
#    set(CTEST_OUTPUT_ON_FAILURE 1)
#    add_subdirectory(${JEB_DIR}/UnitTest)
#endif(NOT DEFINED JEB_DISABLE_UNIT_TESTS)
