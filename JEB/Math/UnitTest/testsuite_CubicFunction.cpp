#include "../CubicFunction.hpp"
#include <jeb/unit/JEBUnit.hpp>
#include <utility>

using namespace JEB::Math;
using namespace std;

static void sortValues(double& a, double& b)
{
    if (a > b)
        swap(a, b);
}

static void sortValues(double& a, double& b, double& c)
{
    sortValues(a, b);
    sortValues(b, c);
    sortValues(a, b);
}

static void testRoots(double root1, double root2, double root3, double epsilon = 1e-12)
{
    sortValues(root1, root2, root3);

    double a = 1;
    double b = -(root1 + root2 + root3);
    double c = root1 * (root2 + root3) + root2 * root3;
    double d = -root1 * root2 * root3;
    CubicFunction cf(a, b, c, d);
    JU_EQUAL(cf.a(), a);
    JU_EQUAL(cf.b(), b);
    JU_EQUAL(cf.c(), c);
    JU_EQUAL(cf.d(), d);
    size_t expectedSolutions = 1
                             + (root1 != root2 ? 1 : 0)
                             + (root2 != root3 ? 1 : 0);
    double t[3];
    size_t solutions = cf.roots(t);
    JU_EQUAL(solutions, expectedSolutions);
    if (solutions == 2)
        sortValues(t[0], t[1]);
    if (solutions == 3)
        sortValues(t[0], t[1], t[2]);
    size_t i = 0;
    JU_EQUAL_REALS(t[i], root1, epsilon);
    i++;
    if (solutions > i && root2 != root1)
    {
        JU_EQUAL_REALS(t[i], root2, epsilon);
        i++;
    }
    if (solutions > i && root3 != root2)
        JU_EQUAL_REALS(t[i], root3, epsilon);
    JU_ASSERT(cf.root(0, t[0]));
    JU_ASSERT(cf.root(1, t[1]));
    JU_ASSERT(cf.root(2, t[2]));
    sortValues(t[0], t[1], t[2]);
    JU_EQUAL_REALS(t[0], root1, epsilon);
    JU_EQUAL_REALS(t[1], root2, epsilon);
    JU_EQUAL_REALS(t[2], root3, epsilon);
}

static void test_Roots()
{
    testRoots(0, 0, 0);
    testRoots(-1, 2, 2);
    testRoots(1, 2, 3);
    testRoots(1, 200, 39876, 1e-9);
}

JU_TESTSUITE(test_Roots);
