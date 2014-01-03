#ifndef JEB_STRING_UNICODE_HPP
#define JEB_STRING_UNICODE_HPP

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <utility>
#include "UnicodePredicates.hpp"

/** @file
  * @brief Defines several functions for identifying Unicode code points.
  */

namespace JEB {
/** @brief Groups together functions for working with Unicode code points.
  */
namespace Unicode
{

template <typename BiIt>
BiIt prevCharacter(BiIt first, BiIt last)
{
    while (last != first)
    {
        --last;
        if (!isMark(*last))
            break;
    }
    return last;
}

template <typename FwdIt>
FwdIt nextCharacter(FwdIt first, FwdIt last)
{
    if (first == last)
        return last;

    return std::find_if(++first, last, [](uint32_t c){return !isMark(c);});
}

template <typename FwdIt>
FwdIt nextCharacter(FwdIt first, FwdIt last, size_t n)
{
    while (n != 0 && first != last)
    {
        first = nextCharacter(first, last);
        --n;
    }
    return first;
}

template <typename BiIt>
BiIt prevCharacter(BiIt first, BiIt last, size_t n,
                   std::bidirectional_iterator_tag)
{
    while (n != 0 && first != last)
    {
        last = prevCharacter(first, last);
        --n;
    }
    return last;
}

template <typename FwdIt>
FwdIt prevCharacter(FwdIt first, FwdIt last, size_t n,
                    std::forward_iterator_tag)
{
    FwdIt it = first;
    for (; n != 0; n--)
    {
        if (first == last)
            return first;
        first = nextCharacter(first, last);
    }
    for (; first != last; first = nextCharacter(first, last))
        it = nextCharacter(it, last);
    return it;
}

template <typename FwdIt>
FwdIt prevCharacter(FwdIt first, FwdIt last, size_t n)
{
    return prevCharacter(first, last, n,
            typename std::iterator_traits<FwdIt>::iterator_category());
}

template <typename FwdIt>
std::pair<FwdIt, FwdIt> characterRange(FwdIt first, FwdIt last, long pos)
{
    if (pos >= 0)
    {
        first = nextCharacter(first, last, pos);
        last = nextCharacter(first, last);
    }
    else
    {
        last = prevCharacter(first, last, -pos);
        first = prevCharacter(first, last);
    }
    return std::make_pair(last, last);
}

template <typename FwdIt>
size_t numberOfCharacters(FwdIt first, FwdIt last)
{
    return std::count_if(first, last, [](uint32_t c){return !isMark(c);});
}

}}

#endif
