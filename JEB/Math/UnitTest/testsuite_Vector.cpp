#include "../JEBMath.hpp"
#include <jeb/unit/JEBUnit.hpp>

using namespace JEB::Math;

typedef Vector<double, 2> V2;
typedef Point<double, 2> P2;

static void test_Basics()
{
    V2 u = vector2<double>(2, 1);
    V2 v = vector2<double>(3, 4);
    JU_EQUAL(x(u), 2);
    JU_EQUAL(y(u), 1);
    JU_EQUAL(x(v), 3);
    JU_EQUAL(y(v), 4);
    JU_EQUAL(dot(u, v), 10);
    JU_EQUAL_REALS(length(v), 5, 1e-10);
}

static void test_Point()
{
    P2 a = point2<double>(3, 12);
    P2 b = point2<double>(8, -11);
    JU_EQUAL(b - a, vector2<double>(5, -23));
}

JU_TESTSUITE(test_Basics, test_Point);

