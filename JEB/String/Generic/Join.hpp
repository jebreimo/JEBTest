//***************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#ifndef JEB_STRING_JOIN_HPP
#define JEB_STRING_JOIN_HPP

#include <iterator>
#include <numeric>
#include <string>
#include <vector>
#include "JEB/JEBDefinitions.hpp"

/** @file
  * @brief Defines functions for joining strings.
  */
namespace JEB { namespace String { namespace Generic {

template <typename StrContainerIt, typename String>
String join(StrContainerIt begin, StrContainerIt end,
            const String& sep,
            std::input_iterator_tag)
{
    if (begin == end)
        return String();

    String result;
    result += *begin;
    while (++begin != end)
    {
        result += sep;
        result += *begin;
    }
    return result;
}

template <typename StrContainerIt, typename String>
String join(StrContainerIt begin, StrContainerIt end,
            const String& sep,
            std::random_access_iterator_tag)
{
    if (begin == end)
        return String();

    size_t length = std::accumulate(
            begin, end,
            (size_t)0,
            [](size_t sum, const std::string& s){return sum + s.size();});
    length += (std::distance(begin, end) - 1) * sep.size();
    String result;
    result.reserve(length);
    result += *begin;
    while (++begin != end)
    {
        result += sep;
        result += *begin;
    }
    return result;
}

template <typename StrContainerIt, typename String>
String join(StrContainerIt begin, StrContainerIt end,
            const String& sep)
{
    return join(begin, end,
                sep,
                typename std::iterator_traits<StrContainerIt>::iterator_category());
}

}}}

#endif
