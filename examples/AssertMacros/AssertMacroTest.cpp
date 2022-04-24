#include "JEBTest/JEBTest.hpp"
#include <stdexcept>
#include <vector>

namespace {

void testEqual()
{
    std::string str = "ABCD";
    const char* cstr = "ABCD";
    const char* cstr2 = "ABCD";
    char mutCstr[] = "ABCD";
    char mutCstr2[] = "ABCD";

    JT_EQUAL(str, cstr);
    JT_EQUAL(cstr, str);
    JT_EQUAL(cstr, cstr);
    JT_EQUAL(cstr, cstr2);
    JT_EQUAL(mutCstr, mutCstr);
    JT_EQUAL(mutCstr, mutCstr2);
    JT_EQUAL(cstr, mutCstr);
    JT_EQUAL(mutCstr, cstr);
}

double divide(double a, double b)
{
    if (b == 0)
        throw std::invalid_argument("division by zero");
    return a / b;
}

void throwsSuccessful()
{
    JT_THROWS(divide(1, 0), std::logic_error);
}

void throwsUnsuccessful()
{
    JT_THROWS(divide(5, 2.5), std::logic_error);
}

void assertSuccessful()
{
    std::vector<int> foo;
    JT_ASSERT(foo.empty());
}

void assertUnsuccessful()
{
    std::vector<int> foo(2);
    JT_ASSERT(foo.empty());
}

void assertMsgSuccessful()
{
    std::vector<int> foo;
    JT_ASSERT_MSG(foo.empty(), "Vector isn't empty!");
}

void assertMsgUnsuccessful()
{
    std::vector<int> foo(2);
    JT_ASSERT_MSG(foo.empty(), "Vector isn't empty!");
}

void equalSuccessful()
{
    JT_EQUAL(divide(10, 2), 5);
}

void equalUnsuccessful()
{
    JT_EQUAL(divide(10, 3), 3.333);
}

void equivalentSuccessful()
{
    JT_EQUIVALENT(divide(10, 3), 3.333, 0.001);
}

void equivalentUnsuccessful()
{
    JT_EQUIVALENT(divide(10, 3), 3.333, 0.0001);
}

void notEqualSuccessful()
{
    JT_NOT_EQUAL(divide(10, 2), 4.999);
}

void notEqualUnsuccessful()
{
    JT_NOT_EQUAL(divide(10, 2), 5);
}

void equalRangesSuccessful()
{
  std::vector<double> v;
  v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);
  std::vector<int> u;
  u.push_back(1); u.push_back(2); u.push_back(3); u.push_back(4);
  JT_EQUAL_RANGES(v, u);
}

void equalRangesUnsuccessful_not_equal()
{
  std::vector<double> v;
  v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);
  std::vector<int> u;
  u.push_back(1); u.push_back(2); u.push_back(4);
  JT_EQUAL_RANGES(v, u);
}

void equalRangesUnsuccessful_longer_left()
{
  std::vector<double> v;
  v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);
  std::vector<int> u;
  u.push_back(1); u.push_back(2); u.push_back(3);
  JT_EQUAL_RANGES(v, u);
}

void equalRangesUnsuccessful_longer_right()
{
  std::vector<double> v;
  v.push_back(1); v.push_back(2); v.push_back(3);
  std::vector<int> u;
  u.push_back(1); u.push_back(2); u.push_back(3); u.push_back(4);
  JT_EQUAL_RANGES(v, u);
}

void failure()
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
        v.push_back(i * i);
    if (v.size() != 11)
        JT_FAILURE("Added 10 elements, should have been 11.");
}

void subtest(const std::string& s, char c, size_t count)
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

void subSuccessful()
{
    JT_CALL(subtest("abcdabcdabcd", 'a', 3));
    JT_CALL(subtest("abcdabcdabcd", 'b', 3));
    JT_CALL(subtest("abcdabcdabcd", 'f', 0));
}

void subUnsuccessful()
{
    JT_CALL(subtest("abcdabcdabcd", 'a', 3));
    JT_CALL(subtest("abcdabcdabcd", 'b', 3));
    JT_CALL(subtest("abcdabcdabcd", 'f', 3)); // This test fails
}

JT_TEST(throwsSuccessful,
        testEqual,
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
        equalRangesSuccessful,
        equalRangesUnsuccessful_not_equal,
        equalRangesUnsuccessful_longer_left,
        equalRangesUnsuccessful_longer_right,
        failure,
        subSuccessful,
        subUnsuccessful);

}