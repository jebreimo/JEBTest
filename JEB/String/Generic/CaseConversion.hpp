#ifndef JEB_STRING_CASECONVERSION_HPP
#define JEB_STRING_CASECONVERSION_HPP

#include <algorithm>
#include "JEB/Unicode/CaseConverter.hpp"
#include "JEB/String/StringPredicates.hpp"

namespace JEB { namespace String { namespace Generic {

template <typename FwdIt, typename OutIt>
OutIt lower(FwdIt begin, FwdIt end, OutIt out)
{
    return std::transform(begin, end, out, Unicode::lower);
}

template <typename FwdIt, typename OutIt>
OutIt title(FwdIt begin, FwdIt end, OutIt out)
{
    bool capNext = true;
    for (; begin != end; ++begin)
    {
        if (!Unicode::isCasedLetter(*begin))
        {
            *out++ = *begin;
            capNext = !Unicode::isAlphaNumeric(*begin);
        }
        else if (capNext)
        {
            *out++ = Unicode::title(*begin);
            capNext = false;
        }
        else
        {
            *out++ = Unicode::lower(*begin);
        }
    }
    return out;
}

template <typename FwdIt, typename OutIt>
OutIt upper(FwdIt begin, FwdIt end, OutIt out)
{
    return std::transform(begin, end, out, Unicode::upper);
}

}}}

#endif