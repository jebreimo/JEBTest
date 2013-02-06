#include "../ProfileMerger.hpp"

#include <algorithm>
#include "../JEBMath.hpp"
#include "JEB/Unit/JEBUnit.hpp"

using namespace std;
using namespace JEB::Math;
using namespace JEB::Math::d2;

template <size_t N>
void fill(LineStringD& ls, double (&array)[N])
{
    for (size_t i = 0; i < N; i += 2)
        ls.push_back(point2<double>(array[i], array[i + 1]));
}

static void test_MergeBothEmpty()
{
    ProfileMerger merger;
    JU_ASSERT(!merger.nextResult());
}

static void CheckResult(const LineStringD& result,
                        const LineStringD& expected,
                        double precision)
{
    JU_EQUAL(result.size(), expected.size());
    LineStringD::const_iterator itR = result.begin();
    LineStringD::const_iterator itE = expected.begin();
    size_t i = 0;
    for (; itR != result.end(); ++itR, ++itE)
    {
        JU_ASSERT_MSG(equivalent(*itR, *itE, precision),
                      "Index " << i << ": got " << *itR <<
                      ", expected " << *itE);
        i++;
    }
}

static void TestMerging(const LineStringD& a,
                        const LineStringD& b,
                        const vector<LineStringD>& result,
                        double maxExtrapolation = 0,
                        double maxInterpolation = 0,
                        double precision = 1e-9)
{
    JU_ASSERT(a.size() < 2 || Profile::isProfile(a));
    JU_ASSERT(b.size() < 2 || Profile::isProfile(b));
    ProfileMerger merger;
    merger.setMaxExtrapolation(maxExtrapolation);
    JU_EQUAL(merger.maxExtrapolation(), maxExtrapolation);
    merger.setMaxInterpolation(maxInterpolation);
    JU_EQUAL(merger.maxInterpolation(), maxInterpolation);
    merger.setPrecision(precision);
    JU_EQUAL(merger.precision(), precision);

    merger.setProfiles(a, b);
    vector<LineStringD>::const_iterator it;
    for (it = result.begin(); it != result.end(); ++it)
    {
        JU_ASSERT_MSG(merger.nextResult(), "Expected: " << *it);
        CheckResult(merger.result(), *it, precision);
    }
    JU_ASSERT(!merger.nextResult());
}

static void test_MergeOneEmpty()
{
    double ap[] = {
        -1,  0,
         0, -2,
         1,  0
    };
    LineStringD a;
    fill(a, ap);

    LineStringD b;

    vector<LineStringD> result(1);
    fill(result[0], ap);

    TestMerging(a, b, result);
}

static void test_MergeSimple()
{
    double ap[] = {
        -1,  0,
         0, -2,
         1,  0
    };
    LineStringD a;
    fill(a, ap);

    double bp[] = {
        -5,  0,
         5,  0
    };
    LineStringD b;
    fill(b, bp);

    double rp[] = {
        -5,  0,
        -1,  0,
         0, -2,
         1,  0,
         5,  0
    };
    vector<LineStringD> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Merge_AB_B()
{
    double ap[] = {
         0,  1,
         2,  0
    };
    LineStringD a;
    fill(a, ap);

    double bp[] = {
         0,  2,
         2,  0,
         4,  1
    };
    LineStringD b;
    fill(b, bp);

    double rp[] = {
         0,  1,
         2,  0,
         4,  1
    };
    vector<LineStringD> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Merge_AB_A()
{
    double ap[] = {
         0,  1,
         2,  0,
         4,  1
    };
    LineStringD a;
    fill(a, ap);

    double bp[] = {
         0,  2,
         2,  0
    };
    LineStringD b;
    fill(b, bp);

    double rp[] = {
         0,  1,
         2,  0,
         4,  1
    };
    vector<LineStringD> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Merge_AB_BA()
{
    double ap[] = {
         0,  1,
         2,  0,
         4,  1
    };
    LineStringD a;
    fill(a, ap);

    double bp[] = {
         0,  2,
         2,  0,
         4, -1
    };
    LineStringD b;
    fill(b, bp);

    double rp[] = {
         0,  1,
         2,  0,
         4, -1
    };
    vector<LineStringD> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Vertical1()
{
    double ap[] = {
        0, 4,
        4, 2,
        8, 1
    };
    LineStringD a;
    fill(a, ap);

    double bp[] = {
        0, 2,
        4, 4,
        4, 0,
        8, 1
    };
    LineStringD b;
    fill(b, bp);

    double rp[] = {
         0,  2,
         2,  3,
         4,  2,
         4,  0,
         8,  1
    };
    vector<LineStringD> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Vertical2()
{
    double ap[] = {
        0, 4,
        2, 4,
        2, 0,
        4, 0
    };
    LineStringD a;
    fill(a, ap);

    double bp[] = {
        0, 3,
        2, 3,
        2, 1,
        4, 1
    };
    LineStringD b;
    fill(b, bp);

    double rp[] = {
         0,  3,
         2,  3,
         2,  0,
         4,  0
    };
    vector<LineStringD> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Vertical3()
{
    double ap[] = {
        0, 4,
        2, 4,
        2, 1,
        4, 1
    };
    LineStringD a;
    fill(a, ap);

    double bp[] = {
        0, 3,
        2, 3,
        2, 0,
        4, 0
    };
    LineStringD b;
    fill(b, bp);

    double rp[] = {
         0,  3,
         2,  3,
         2,  0,
         4,  0
    };
    vector<LineStringD> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Segments1()
{
    double ap[] = {
        0, 0,
        4, 5,
        8, 0
    };
    LineStringD a;
    fill(a, ap);

    double bp[] = {
        2, 2,
        6, 2
    };
    LineStringD b;
    fill(b, bp);

    double rp0[] = {
         0,  0,
         2,  2.5
    };
    double rp1[] = {
         2,  2,
         6,  2
    };
    double rp2[] = {
         6,  2.5,
         8,  0
    };
    vector<LineStringD> result(3);
    fill(result[0], rp0);
    fill(result[1], rp1);
    fill(result[2], rp2);

    TestMerging(a, b, result);
}

static void test_Extrapolation1()
{
    double ap[] = {
        0, 0,
        4, 5,
        8, 0
    };
    LineStringD a;
    fill(a, ap);

    double bp[] = {
        2, 2,
        6, 2
    };
    LineStringD b;
    fill(b, bp);

    double rp[] = {
         0,  0,
         1.6, 2,
         2, 2,
         6, 2,
         6.4, 2,
         8, 0
    };
    vector<LineStringD> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result, 0.4001);
}

JU_TESTSUITE(test_MergeBothEmpty,
             test_MergeOneEmpty,
             test_MergeSimple,
             test_Merge_AB_B,
             test_Merge_AB_A,
             test_Merge_AB_BA,
             test_Vertical1,
             test_Vertical2,
             test_Vertical3,
             test_Segments1,
             test_Extrapolation1);
