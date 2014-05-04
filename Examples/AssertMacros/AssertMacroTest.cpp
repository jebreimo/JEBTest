#include "JEBTest/JEBTest.hpp"
#include <stdexcept>
#include <vector>

static double divide(double a, double b)
{
    if (b == 0)
        throw std::invalid_argument("division by zero");
    return a / b;
}

static void throwsSuccessful()
{
    JT_THROWS(divide(1, 0), std::logic_error);
}

static void throwsUnsuccessful()
{
    JT_THROWS(divide(5, 2.5), std::logic_error);
}

static void assertSuccessful()
{
    std::vector<int> foo;
    JT_ASSERT(foo.empty());
}

static void assertUnsuccessful()
{
    std::vector<int> foo(2);
    JT_ASSERT(foo.empty());
}

static void assertMsgSuccessful()
{
    std::vector<int> foo;
    JT_ASSERT_MSG(foo.empty(), "Vector isn't empty!");
}

static void assertMsgUnsuccessful()
{
    std::vector<int> foo(2);
    JT_ASSERT_MSG(foo.empty(), "Vector isn't empty!");
}

static void equalSuccessful()
{
    JT_EQUAL(divide(10, 2), 5);
}

static void equalUnsuccessful()
{
    JT_EQUAL(divide(10, 3), 3.333);
}

static void equivalentSuccessful()
{
    JT_EQUIVALENT(divide(10, 3), 3.333, 0.001);
}

static void equivalentUnsuccessful()
{
    JT_EQUIVALENT(divide(10, 3), 3.333, 0.0001);
}

static void notEqualSuccessful()
{
    JT_NOT_EQUAL(divide(10, 2), 4.999);
}

static void notEqualUnsuccessful()
{
    JT_NOT_EQUAL(divide(10, 2), 5);
}

static void failure()
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
        v.push_back(i * i);
    if (v.size() != 11)
        JT_FAILURE("Added 10 elements, should have been 11.");
}

static void subtest(const std::string& s, char c, size_t count)
{
    JT_ASSERT(!s.empty());
    size_t pos = 0;
    size_t actualCount = 0;
    while (true)
    {
        pos = s.find_first_of(c, pos);
        if (pos == std::string::npos)
            break;
        ++pos;
        ++actualCount;
    }
    JT_EQUAL(actualCount, count);
}

static void subSuccessful()
{
    JT_CALL(subtest("abcdabcdabcd", 'a', 3));
    JT_CALL(subtest("abcdabcdabcd", 'b', 3));
    JT_CALL(subtest("abcdabcdabcd", 'f', 0));
}

static void subUnsuccessful()
{
    JT_CALL(subtest("abcdabcdabcd", 'a', 3));
    JT_CALL(subtest("abcdabcdabcd", 'b', 3));
    JT_CALL(subtest("abcdabcdabcd", 'f', 3)); // This test fails
}

JT_TEST(throwsSuccessful,
        throwsUnsuccessful,
        assertSuccessful,
        assertUnsuccessful,
        assertMsgSuccessful,
        assertMsgUnsuccessful,
        equalSuccessful,
        equalUnsuccessful,
        equivalentSuccessful,
        equivalentUnsuccessful,
        notEqualSuccessful,
        notEqualUnsuccessful,
        failure,
        subSuccessful,
        subUnsuccessful);
