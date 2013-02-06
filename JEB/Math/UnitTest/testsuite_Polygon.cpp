#include "../Polygon.hpp"
#include "../Types.hpp"
#include <JEB/Iterators.hpp>
#include <JEB/Unit/JEBUnit.hpp>

using namespace JEB::Math;

static void test_IsPolygon()
{
    d2::PointD vertices1[] = {
        d2::pointD(-3, 0),
        d2::pointD(3, 0),
        d2::pointD(0, 4),
        d2::pointD(-3, 0)
    };
    JU_ASSERT(Polygon::isPolygon(std::begin(vertices1), std::end(vertices1)));

    d2::PointD vertices2[] = {
        d2::pointD(-3, 0),
        d2::pointD(0, 4),
        d2::pointD(-3, 0)
    };
    JU_ASSERT(!Polygon::isPolygon(std::begin(vertices2), std::end(vertices2)));

    d2::PointD vertices3[] = {
        d2::pointD(-3, 0),
        d2::pointD(3, 0),
        d2::pointD(0, 4),
        d2::pointD(-3, 4),
    };
    JU_ASSERT(!Polygon::isPolygon(std::begin(vertices3), std::end(vertices3)));
}

static void test_IsInside()
{
    d2::PointD vertices[] = {
        d2::pointD(-3, 0),
        d2::pointD(3, 0),
        d2::pointD(0, 4),
        d2::pointD(-3, 0)
    };
    d2::PolygonD poly(std::begin(vertices), std::end(vertices));
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(0, 2)),
             Polygon::PolygonPosition::Inside);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(-1, 3)),
             Polygon::PolygonPosition::Outside);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(1, 3)),
             Polygon::PolygonPosition::Outside);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(-1, 8.0 / 3.0)),
             Polygon::PolygonPosition::OnBorder);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(0, 4)),
             Polygon::PolygonPosition::OnBorder);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(0, 0)),
             Polygon::PolygonPosition::OnBorder);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(-4, 0)),
             Polygon::PolygonPosition::Outside);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(4, 0)),
             Polygon::PolygonPosition::Outside);
}

static void test_IsInsideConcave()
{
    d2::PointD vertices[] = {
        d2::pointD(-3, 0),
        d2::pointD(-1, 0),
        d2::pointD(-1, 1),
        d2::pointD(1, 1),
        d2::pointD(1, 0),
        d2::pointD(3, 0),
        d2::pointD(0, 3),
        d2::pointD(-3, 0)
    };
    d2::PolygonD poly(std::begin(vertices), std::end(vertices));
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(0, 2)),
             Polygon::PolygonPosition::Inside);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(0, 1)),
             Polygon::PolygonPosition::OnBorder);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(0, 0.5)),
             Polygon::PolygonPosition::Outside);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(0, 0)),
             Polygon::PolygonPosition::Outside);
    JU_EQUAL(Polygon::isInside(poly, d2::pointD(1.5, 1)),
             Polygon::PolygonPosition::Inside);
}

static void test_IsConvex()
{
    d2::PointD convex[] = {
        d2::pointD(-2, -1),
        d2::pointD(2, -1),
        d2::pointD(2, 1),
        d2::pointD(-2, 1),
        d2::pointD(-2, -1)
    };
    d2::PolygonD convexPoly(std::begin(convex), std::end(convex));
    JU_ASSERT(Polygon::isConvex(convexPoly));

    d2::PointD concave[] = {
        d2::pointD(-2, -1),
        d2::pointD(0, 0),
        d2::pointD(2, -1),
        d2::pointD(0, 2),
        d2::pointD(-2, -1)
    };
    d2::PolygonD concavePoly(std::begin(concave), std::end(concave));
    JU_ASSERT(!Polygon::isConvex(concavePoly));
}

static void test_Rotation()
{
    d2::PointD p0 = d2::pointD(1.1, 1.1);
    d2::PointD p1 = d2::pointD(3.3, 3.3);
    d2::PointD p2 = d2::pointD(6.6, 6.6);
    d2::PointD p3 = d2::pointD(3.3, 5.7);
    d2::PointD p4 = d2::pointD(3.3, 1.7);

    double tol = 1e-9;
    JU_EQUAL(Polygon::direction(p0, p1, p2, tol), Polygon::Ahead);
    JU_EQUAL(Polygon::direction(p1, p2, p0, tol), Polygon::Behind);
    JU_EQUAL(Polygon::direction(p2, p2, p1, tol), Polygon::Undetermined);
    JU_EQUAL(Polygon::direction(p0, p1, p3, tol), Polygon::Left);
    JU_EQUAL(Polygon::direction(p0, p1, p4, tol), Polygon::Right);
}

static void test_Angle()
{
    d2::PointD p0 = d2::pointD(0, 0);
    d2::PointD p1 = d2::pointD(1, 0);
    d2::PointD p2 = d2::pointD(1, 1);

    JU_EQUAL_REALS(Polygon::angle(p0, p1, p2), Pi / 2, 1e-9);
    JU_EQUAL_REALS(Polygon::angle(p2, p1, p0), Pi / 2, 1e-9);
    JU_EQUAL_REALS(Polygon::angleCCW(p0, p1, p2), Pi / 2, 1e-9);
    JU_EQUAL_REALS(Polygon::angleCCW(p2, p1, p0), 3 * Pi / 2, 1e-9);

    JU_EQUAL_REALS(Polygon::angle(p0, p2, p1), Pi / 4, 1e-9);
    JU_EQUAL_REALS(Polygon::angle(p1, p2, p0), Pi / 4, 1e-9);
    JU_EQUAL_REALS(Polygon::angleCCW(p0, p2, p1), 7 * Pi / 4, 1e-9);
    JU_EQUAL_REALS(Polygon::angleCCW(p1, p2, p0), Pi / 4, 1e-9);
}

static void test_Area()
{
    d2::PointD points[] = {
        d2::pointD(-4, 2),
        d2::pointD(-1, 8),
        d2::pointD(-1, 2),
        d2::pointD(-4, 2),
    };
    JU_EQUAL_REALS(Polygon::area(std::begin(points), std::end(points)),
                   -9, 1e-9);
}

template <typename PointIt1, typename PointIt2>
static void testOverlap(PointIt1 beg, PointIt1 end, double offset,
                        PointIt2 cmpBeg, PointIt1 cmpEnd, double cmpOffset,
                        PointIt1 exp, double expOffset,
                        PointIt2 expCmp, double expCmpOffset)
{
    auto m = Polygon::overlap(beg, end, offset, cmpBeg, cmpEnd, cmpOffset, 1e-9);
    JU_ASSERT(m.first.first == exp);
    JU_EQUAL(m.first.second, expOffset);
    JU_ASSERT(m.second.first == expCmp);
    JU_EQUAL(m.second.second, expCmpOffset);
}

static void test_Overlap()
{
    using namespace d2;
    testOverlap<PointD*, PointD*>(NULL, NULL, 0.5,
                                  NULL, NULL, 0.25,
                                  NULL, 0.5,
                                  NULL, 0.25);
    PointD p1[] = {pointD(-2, -1)};
    testOverlap<PointD*, PointD*>(std::begin(p1), std::end(p1), 0.5,
                                  NULL, NULL, 0.25,
                                  std::begin(p1), 0.5,
                                  NULL, 0.25);
    testOverlap<PointD*, PointD*>(NULL, NULL, 0.25,
                                  std::begin(p1), std::end(p1), 0.5,
                                  NULL, 0.25,
                                  std::begin(p1), 0.5);
    PointD p2[] = {pointD(-2, -1)};
    PointD p3[] = {pointD(-2, -2)};
    testOverlap<PointD*, PointD*>(std::begin(p1), std::end(p1), 0.5,
                                  std::begin(p2), std::end(p2), 0.5,
                                  std::begin(p1), 0.5,
                                  std::begin(p2), 0.5);
    testOverlap<PointD*, PointD*>(std::begin(p1), std::end(p1), 0.5,
                                  std::begin(p3), std::end(p3), 0.5,
                                  std::begin(p1), 0.5,
                                  std::begin(p3), 0.5);
    PointD p4[] = {pointD(0, 0), pointD(2, 0)};
    PointD p5[] = {pointD(0, 0), pointD(1, 0), pointD(2, 0)};
    testOverlap<PointD*, PointD*>(std::begin(p4), std::end(p4), 0,
                                  std::begin(p5), std::end(p5), 0,
                                  &p4[1], 0,
                                  &p5[2], 0);
    PointD p6[] = {pointD(0.5, 0), pointD(1.5, 0), pointD(2.5, 0)};
    testOverlap<PointD*, PointD*>(std::begin(p5), std::end(p5), 0.5,
                                  std::begin(p6), std::end(p6), 0,
                                  &p5[2], 0,
                                  &p6[1], 0.5);
    PointD p7[] = {pointD(0, 0), pointD(1, 0), pointD(1, 0), pointD(2, 0)};
    testOverlap<PointD*, PointD*>(std::begin(p5), std::end(p5), 0,
                                  std::begin(p7), std::end(p7), 0,
                                  &p5[2], 0,
                                  &p7[3], 0);
    PointD p8[] = {pointD(0, 0), pointD(1, 0), pointD(0.9, 0), pointD(2, 0)};
    testOverlap<PointD*, PointD*>(std::begin(p5), std::end(p5), 0,
                                  std::begin(p8), std::end(p8), 0,
                                  &p5[1], 0,
                                  &p8[1], 0);
}

static void test_AreEquivalent()
{
    using namespace d2;
    PointD poly1[] = {
        pointD( 0, 0),
        pointD( 3, 4),
        pointD( 6, 0),
        pointD( 6, 0),
        pointD( 0, 0),
        pointD( 6, 8),
        pointD(12, 0),
        pointD( 0, 0)
    };
    PointD poly2[] = {
        pointD( 0, 0),
        pointD( 4.5, 6),
        pointD( 6, 8),
        pointD(12, 0),
        pointD( 6, 0),
        pointD( 0, 0),
        pointD( 3, 4),
        pointD( 6, 0),
        pointD( 0, 0)
    };
    JU_ASSERT(Polygon::equivalent(std::begin(poly1), std::end(poly1),
                                  std::begin(poly2), std::end(poly2),
                                  1e-9));
    PointD poly3[] = {
        pointD( 0, 0),
        pointD( 1.5, 2),
        pointD( 3, 0),
        pointD( 0, 0),
        pointD( 0, 0),
        pointD( 6, 8),
        pointD(12, 0),
        pointD( 0, 0),
        pointD( 3, 4),
        pointD( 6, 0),
        pointD( 0, 0)
    };
    JU_ASSERT(!Polygon::equivalent(std::begin(poly1), std::end(poly1),
                                   std::begin(poly3), std::end(poly3),
                                   1e-9));
}

JU_TESTSUITE(test_IsPolygon,
             test_IsInside,
             test_IsInsideConcave,
             test_IsConvex,
             test_Rotation,
             test_Angle,
             test_Area,
             test_Overlap,
             test_AreEquivalent);
