#include "../CubicHermiteSpline.hpp"

#include "../Point.hpp"
#include "../Vector.hpp"
#include <jeb/unit/JEBUnit.hpp>

using namespace JEB::Math;

static void test_Dim2()
{
    typedef Point<double, 2> P;
    typedef Vector<double, 2> V;
    typedef CubicHermiteSpline<P, V> CHS;
    P p1 = point2<double>(1, 1);
    V v1 = vector2<double>(1, 1);
    P p2 = point2<double>(3, 1);
    V v2 = vector2<double>(1, -1);
    CHS spline(p1, v1, p2, v2);
    JU_EQUAL(spline.start(), p1);
    JU_EQUAL(spline.startTangent(), v1);
    JU_ASSERT(equivalent(spline.end(), p2, 1e-12));
    JU_ASSERT(equivalent(spline.endTangent(), v2, 1e-12));
    P mid = spline.pointAt(0.5);
    JU_EQUAL_REALS(x(mid), 2, 1e-12);
}

JU_TESTSUITE(test_Dim2);
