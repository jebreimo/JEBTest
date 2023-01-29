//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cmath>
#include <cstring>
#include <cwchar>
#include <sstream>
#include <string>

namespace JEBTest
{
    template <typename T, typename U>
    bool equal(T&& t, U&& u)
    {
        return t == u;
    }

    inline bool equal(char* t, char* u)
    {
        if (t == nullptr || u == nullptr)
            return t == u;
        return std::strcmp(t, u) == 0;
    }

    inline bool equal(const char* t, const char* u)
    {
        if (t == nullptr || u == nullptr)
            return t == u;
        return std::strcmp(t, u) == 0;
    }

    inline bool equal(char* t, const char* u)
    {
        if (t == nullptr || u == nullptr)
            return t == u;
        return std::strcmp(t, u) == 0;
    }

    inline bool equal(const char* t, char* u)
    {
        if (t == nullptr || u == nullptr)
            return t == u;
        return std::strcmp(t, u) == 0;
    }

    inline bool equal(wchar_t* t, wchar_t* u)
    {
        if (t == nullptr || u == nullptr)
            return t == u;
        return std::wcscmp(t, u) == 0;
    }

    inline bool equal(const wchar_t* t, const wchar_t* u)
    {
        if (t == nullptr || u == nullptr)
            return t == u;
        return std::wcscmp(t, u) == 0;
    }

    inline bool equal(wchar_t* t, const wchar_t* u)
    {
        if (t == nullptr || u == nullptr)
            return t == u;
        return std::wcscmp(t, u) == 0;
    }

    template <typename T, typename U>
    bool notEqual(T&& t, U&& u)
    {
        return !::JEBTest::equal(std::forward<T>(t), std::forward<U>(u));
    }

    template <typename T, typename U, typename V>
    bool equivalent(T&& a, U&& b, V margin)
    {
        using namespace std;
        return abs(a - b) <= margin;
    }

    template <typename T, typename U>
    bool lessThan(T&& a, U&& b)
    {
        return a < b;
    }

    template <typename T, typename U>
    bool greaterThan(T&& a, U&& b)
    {
        return b < a;
    }

    template <typename Range1, typename Range2>
    inline std::pair<bool, std::string> equalRanges(
            Range1&& a, Range2&& b,
            const std::string& aName, const std::string& bName)
    {
        using namespace std;
        auto itA = begin(a);
        auto itB = begin(b);
        size_t i = 0;
        for (; itA != end(a) && itB != end(b); ++itA, ++itB)
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
        if (itA != end(a))
        {
            std::stringstream ss;
            ss << aName << " != " << bName << ": the former has "
               << i + std::distance(itA, end(a))
               << " elements while the latter has " << i << " elements.";
            return std::make_pair(false, ss.str());
        }
        if (itB != end(b))
        {
            std::stringstream ss;
            ss << aName << " != " << bName << ": the former has " << i
               << " elements while the latter has "
               << i + std::distance(itB, end(b)) << " elements.";
            return std::make_pair(false, ss.str());
        }
        return std::make_pair(true, std::string());
    }

    template <typename Range1, typename Range2, typename Epsilon>
    inline std::pair<bool, std::string> equivalentRanges(
            Range1&& a, Range2&& b, Epsilon margin,
            const std::string& aName, const std::string& bName)
    {
        using namespace std;
        auto itA = begin(a);
        auto itB = begin(b);
        size_t i = 0;
        for (; itA != end(a) && itB != end(b); ++itA, ++itB)
        {
            if (!equivalent(*itA, *itB, margin))
            {
                std::stringstream ss;
                ss << aName << "[" << i << "] != " << bName << "[" << i
                << "]: \"" << *itA << "\" != \"" << *itB << "\".";
                return std::make_pair(false, ss.str());
            }
            ++i;
        }
        if (itA != end(a))
        {
            std::stringstream ss;
            ss << aName << " != " << bName << ": the former has "
            << i + std::distance(itA, end(a))
            << " elements while the latter has " << i << " elements.";
            return std::make_pair(false, ss.str());
        }
        if (itB != end(b))
        {
            std::stringstream ss;
            ss << aName << " != " << bName << ": the former has " << i
            << " elements while the latter has "
            << i + std::distance(itB, end(b)) << " elements.";
            return std::make_pair(false, ss.str());
        }
        return std::make_pair(true, std::string());
    }
}
