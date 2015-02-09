/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBTEST_TEST_COMPARERS_HPP
#define JEBTEST_TEST_COMPARERS_HPP

#include <cmath>
#include <cstring>
#include <sstream>
#include <string>

namespace JEBTest {

template <typename T, typename U>
bool equal(T t, U u)
{
    return t == u;
}

template <>
inline bool equal<char*, char*>(char* t, char* u)
{
    if (t == nullptr || u == nullptr)
        return t == u;
    return std::strcmp(t, u) == 0;
}

template <>
inline bool equal<const char*, const char*>(const char* t, const char* u)
{
    if (t == nullptr || u == nullptr)
        return t == u;
    return std::strcmp(t, u) == 0;
}

template <>
inline bool equal<char*, const char*>(char* t, const char* u)
{
    if (t == nullptr || u == nullptr)
        return t == u;
    return std::strcmp(t, u) == 0;
}

template <typename T, typename U>
bool notEqual(T t, U u)
{
    return !::JEBTest::equal(t, u);
}

template <typename T, typename U, typename V>
bool equivalent(T a, U b, V epsilon)
{
    return std::abs(a - b) <= epsilon;
}

template <typename T, typename U>
bool lessThan(T a, U b)
{
    return a < b;
}

template <typename T, typename U>
bool greaterThan(T a, U b)
{
    return b < a;
}

template <typename Range1, typename Range2>
inline std::pair<bool, std::string> equalRanges(
        Range1&& a, Range2&& b,
        const std::string& aName, const std::string& bName)
{
    auto itA = a.begin();
    auto itB = b.begin();
    size_t i = 0;
    for (; itA != a.end() && itB != b.end(); ++itA, ++itB)
    {
        if (!equal(*itA, *itB))
        {
            std::stringstream ss;
            ss << aName << "[" << i << "] != " << bName << "[" << i
               << "]: \"" << *itA << "\" != \"" << *itB << "\".";
            return std::make_pair(false, ss.str());
        }
        ++i;
    }
    if (itA != a.end())
    {
        std::stringstream ss;
        ss << aName << " != " << bName << ": the former has "
           << i + std::distance(itA, a.end())
           << " elements while the latter has " << i << " elements.";
        return std::make_pair(false, ss.str());
    }
    if (itB != b.end())
    {
        std::stringstream ss;
        ss << aName << " != " << bName << ": the former has " << i
           << " elements while the latter has "
           << i + std::distance(itB, b.end()) << " elements.";
        return std::make_pair(false, ss.str());
    }
    return std::make_pair(true, std::string());
}

}

#endif
