//***************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#ifndef JEB_STRING_TRIM_HPP
#define JEB_STRING_TRIM_HPP

#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include "Find.hpp"
#include "JEB/String/StringFlags.hpp"

namespace JEB { namespace String { namespace Generic {

template <typename BiIt, typename UnaryFunc>
std::pair<BiIt, BiIt> trim(BiIt beg, BiIt end,
                           UnaryFunc predicate)
{
    BiIt tbeg = findFirstWhereNot(beg, end, predicate);
    BiIt tend = findLastWhereNot(tbeg, end, predicate);
    if (tend != end)
        ++tend;
    return std::make_pair(tbeg, tend);
}

template <typename BiIt, typename UnaryFunc>
std::pair<BiIt, BiIt> trimStart(BiIt beg, BiIt end,
                                UnaryFunc predicate)
{
    BiIt tbeg = findFirstWhereNot(beg, end, predicate);
    return std::make_pair(tbeg, end);
}

template <typename BiIt, typename UnaryFunc>
std::pair<BiIt, BiIt> trimEnd(BiIt beg, BiIt end,
                              UnaryFunc predicate)
{
    BiIt tend = findLastWhereNot(beg, end, predicate);
    if (tend == end)
        return std::make_pair(end, end);
    else
        return std::make_pair(beg, ++tend);
}

}}}

#endif
