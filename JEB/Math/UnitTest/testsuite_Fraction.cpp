#include "../Fraction.hpp"
#include <jeb/unit/JEBUnit.hpp>

using namespace JEB::Math;

typedef Fraction<int> F;

void test_Construction()
{
    JU_EQUAL(F(0, 1), F());
    JU_EQUAL(F(1, 1), F(1));
    JU_EQUAL(F(9, 63), F(1, 7));
    JU_EQUAL(F(21, -49), F(-3, 7));
}

void test_Math()
{
    F a(1, 3);
    F b(1, 6);
    JU_EQUAL(a + b, F(1, 2));
    JU_EQUAL(b + a, F(1, 2));
    JU_EQUAL(-a + -b, F(-1, 2));
    JU_EQUAL(a - b, F(1, 6));
    JU_EQUAL(b - a, F(-1, 6));
    JU_EQUAL(a * b, F(1, 18));
    JU_EQUAL(-a * b, F(-1, 18));
    JU_EQUAL(a / b, F(2, 1));
    JU_EQUAL(a / -b, F(-2, 1));
}

JU_TESTSUITE(test_Construction, test_Math);
