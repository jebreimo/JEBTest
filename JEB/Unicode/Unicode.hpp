#ifndef JEB_STRING_UNICODE_HPP
#define JEB_STRING_UNICODE_HPP

#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <utility>
#include "CharClass.hpp"
#include "UnicodeChars.hpp"

/** @file
  * @brief Defines several functions for identifying Unicode code points.
  */

namespace JEB {
/** @brief Groups together functions for working with Unicode code points.
  */
namespace Unicode
{

template <typename BiIt>
BiIt startOfCharacter(BiIt begin, BiIt end)
{
    if (begin == end)
        return end;

    while (end != begin)
    {
        if ((charClass(*(--end)) & CharClass::Mark) == 0)
            return end;
    }

    throw std::runtime_error("Invalid unicode character; it starts with a combining mark");
    return end;
}

template <typename FwdIt>
FwdIt endOfCharacter(FwdIt begin, FwdIt end)
{
    if (begin == end)
        return end;

    ++begin;
    while (begin != end && (charClass(*begin) & CharClass::Mark) != 0)
        ++begin;
    return begin;
}


template <typename FwdIt>
FwdIt advanceCharacters(FwdIt begin, FwdIt end, size_t n)
{
    while (n != 0 && begin != end)
    {
        begin = Unicode::endOfCharacter(begin, end);
        --n;
    }
    return begin;
}

template <typename BiIt>
BiIt retreatCharacters(BiIt begin, BiIt end,
                        size_t n)
{
    while (n != 0 && begin != end)
    {
        end = Unicode::startOfCharacter(begin, end);
        --n;
    }
    return end;
}

template <typename FwdIt>
std::pair<FwdIt, FwdIt> characterRange(FwdIt begin, FwdIt end, long pos)
{
    if (pos >= 0)
    {
        begin = advanceCharacters(begin, end, pos);
        end = Unicode::endOfCharacter(begin, end);
    }
    else
    {
        end = retreatCharacters(begin, end, -pos);
        begin = Unicode::startOfCharacter(begin, end);
    }
    return std::make_pair(end, end);
}

template <typename FwdIt>
size_t numberOfCharacters(FwdIt begin, FwdIt end)
{
    size_t len = 0;
    for (; begin != end; ++begin)
    {
        if ((charClass(*begin) & CharClass::Mark) == 0)
            ++len;
    }
    return len;
}

// template <typename FwdIt>
// FwdIt skipNewline(FwdIt begin, FwdIt end)
// {
//     if (begin != end)
//         return begin;

//     switch (*begin)
//     {
//     case '\n':
//     case '\v':
//     case '\f':
//     case JEB_CHAR_NEXT_LINE:
//     case JEB_CHAR_LINE_SEPARATOR:
//     case JEB_CHAR_PARAGRAPH_SEPARATOR:
//         ++begin;
//         break;
//     case '\r':
//         if (++begin != end && *begin == '\n')
//             ++begin;
//         break;
//     default:
//         break;
//     }
//     return begin;
// }

}}

#endif
