cmake_minimum_required(VERSION 2.8)

include(../../CMakeDirs.txt)
project(JEBMathTest)

if (MSVC)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif (MSVC)

set(SRC
    main.cpp
    testsuite_Binomial.cpp
    testsuite_Combinations.cpp
    testsuite_CubicFunction.cpp
    testsuite_CubicHermiteSpline.cpp
    testsuite_Fraction.cpp
    testsuite_Intersections.cpp
    testsuite_LineString.cpp
    testsuite_Matrix.cpp
    testsuite_Plane.cpp
    testsuite_Polygon.cpp
    testsuite_PolygonUnwinder.cpp
    testsuite_Primes.cpp
    testsuite_Profile.cpp
    testsuite_ProfileMerger.cpp
    testsuite_SortPoints.cpp
    testsuite_Vector.cpp
    )

add_executable(JEBMathTest ${SRC})

target_link_libraries(JEBMathTest JEBLib JEBMath JEBUnit)
add_test(JEBMath JEBMathTest)
