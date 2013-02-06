#include "../Combinations.hpp"
#include <JEB/Unit/JEBUnit.hpp>

using namespace JEB::Math;

static void test_Index()
{
    JU_EQUAL(Combinations::index(0), 0);
    JU_EQUAL(Combinations::index(1), 1);
    JU_EQUAL(Combinations::index(0x10), 5);
    JU_EQUAL(Combinations::index(0x80000000u), 32);
    JU_EQUAL(Combinations::index(3), 33);
    JU_EQUAL(Combinations::index(5), 34);
    JU_EQUAL(Combinations::index(0x80000001u), 63);
    JU_EQUAL(Combinations::index(0x80000002u), 93);
    JU_EQUAL(Combinations::index(3, 6), 7);
    JU_EQUAL(Combinations::index(0x30, 6), 21);
    JU_EQUAL(Combinations::index(7, 6), 22);
}

static void test_LocalIndex()
{
    JU_EQUAL(Combinations::localIndex(0x7, 7), 0);
    JU_EQUAL(Combinations::localIndex(0xB, 7), 1);
    JU_EQUAL(Combinations::localIndex(0xE, 7), 15);
}

JU_TESTSUITE(test_Index, test_LocalIndex);
