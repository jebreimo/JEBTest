#include "../Binomial.hpp"
#include <JEB/Unit/JEBUnit.hpp>

using namespace JEB::Math;

static void test_Values()
{
    JU_EQUAL(binomial(0, 0), 0);
    JU_EQUAL(binomial(1, 0), 1);
    JU_EQUAL(binomial(10, 11), 0);
    JU_EQUAL(binomial(10, -1), 0);
    JU_EQUAL(binomial(10, 0), 1);
    JU_EQUAL(binomial(6, 3), 20);
    JU_EQUAL(binomial(7, 3), 35);
    JU_EQUAL(binomial(7, 2), binomial(7, 5));
}

JU_TESTSUITE(test_Values);
