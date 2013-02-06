#include "../JEBMath.hpp"
#include <jeb/unit/JEBUnit.hpp>

using namespace JEB::Math;

static void test_Basics()
{
    std::vector<Point<int, 2>> ls;
    //typedef Point<int, 2> P;
    ls.push_back(point2<int>(-1, 3));
    ls.push_back(point2<int>(3, 5));
    ls.push_back(point2<int>(7, -4));
    JU_EQUAL(ls.size(), 3);
    JU_EQUAL(segmentCount(ls), 2);
    JU_EQUAL(ls[0], point2<int>(-1, 3));
    JU_EQUAL(ls[2], point2<int>(7, -4));
}

JU_TESTSUITE(test_Basics);
