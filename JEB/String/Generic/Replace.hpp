//***************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#ifndef JEB_STRING_REPLACE_HPP
#define JEB_STRING_REPLACE_HPP

#include <algorithm>
#include <cstdint>
#include <string>
#include "JEB/Algorithms/Algorithms.hpp"
#include "JEB/String/StringFlags.hpp"
#include "JEB/Unicode/CaseInsensitive.hpp"

namespace JEB { namespace String { namespace Generic {

template <typename FwdIt, typename OutIt>
OutIt replaceCS(FwdIt beg, FwdIt end,
                FwdIt cmpBeg, FwdIt cmpEnd,
                FwdIt replBeg, FwdIt replEnd,
                OutIt out,
                size_t max)
{
    std::pair<FwdIt, FwdIt> match;
    match = Algorithms::search(beg, end, cmpBeg, cmpEnd);
    while (match.first != end)
    {
        std::copy(beg, match.first, out);
        std::copy(replBeg, replEnd, out);
        beg = match.second;
        if (--max == 0)
            break;
        match = Algorithms::search(beg, end, cmpBeg, cmpEnd);
    }
    std::copy(beg, end, out);
    return out;
}

template <typename FwdIt, typename OutIt>
OutIt replaceCI(FwdIt beg, FwdIt end,
                FwdIt cmpBeg, FwdIt cmpEnd,
                FwdIt replBeg, FwdIt replEnd,
                OutIt out,
                size_t max)
{
    std::pair<FwdIt, FwdIt> match;
    match = Algorithms::search(beg, end,
                               cmpBeg, cmpEnd,
                               Unicode::CaseInsensitiveEqual<uint32_t>());
    while (match.first != end)
    {
        std::copy(beg, match.first, out);
        std::copy(replBeg, replEnd, out);
        beg = match.second;
        if (--max == 0)
            break;
        match = Algorithms::search(beg, end,
                                   cmpBeg, cmpEnd,
                                   Unicode::CaseInsensitiveEqual<uint32_t>());
    }
    std::copy(beg, end, out);
    return out;
}

template <typename FwdIt, typename OutIt>
OutIt replace(FwdIt beg, FwdIt end,
              FwdIt cmpBeg, FwdIt cmpEnd,
              FwdIt replBeg, FwdIt replEnd,
              OutIt out,
              size_t max,
              FindFlags::Flags flags)
{
    if ((flags & FindFlags::CaseInsensitive) != 0)
        return replaceCI(beg, end, cmpBeg, cmpEnd, replBeg, replEnd, out, max);
    else
        return replaceCS(beg, end, cmpBeg, cmpEnd, replBeg, replEnd, out, max);
}

}}}

#endif
