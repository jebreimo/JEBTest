#include "../Plane.hpp"
#include "../Types.hpp"
#include <cmath>
#include <JEB/Unit/JEBUnit.hpp>

using namespace JEB::Math;

static void test_Units()
{
    Plane3<double> plane1(d3::pointD(1, 1, 1), d3::vectorD(1, 1, 1));
    d3::VectorD u1, u2;
    JU_ASSERT(plane1.getUnitVectors(u1, u2));
    JU_ASSERT(equivalent(
            u1,
            d3::vectorD(-1 / std::sqrt(2.0),  1 / std::sqrt(2.0), 0),
            1e-10));
    JU_ASSERT(equivalent(
            u2,
            d3::vectorD(-1 / std::sqrt(6.0), -1 / std::sqrt(6.0), std::sqrt(2.0 / 3.0)),
            1e-10));
}

JU_TESTSUITE(test_Units);
