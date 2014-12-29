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

namespace JEB { namespace Test {

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
    return !::JEB::Test::equal(t, u);
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

}}

#endif