#ifndef JEB_STRING_FIND_HPP
#define JEB_STRING_FIND_HPP

#include <iterator>
#include "JEB/Algorithms/Algorithms.hpp"
#include "JEB/Unicode/CaseInsensitive.hpp"
#include "JEB/Unicode/UnicodeChars.hpp"
#include "JEB/String/StringFlags.hpp"

namespace JEB { namespace String { namespace Generic {

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt1> find(FwdIt1 begin, FwdIt1 end,
                               FwdIt2 cmpBegin, FwdIt2 cmpEnd,
                               FindFlags::Flags flags)
{
    if ((flags & FindFlags::CaseInsensitive) != 0)
    {
        return JEB::Algorithms::search(begin, end,
                                       cmpBegin, cmpEnd,
                                       Unicode::CaseInsensitiveEqual<uint32_t>());
    }
    else
    {
        return JEB::Algorithms::search(begin, end, cmpBegin, cmpEnd);
    }
}

template <typename FwdIt>
std::pair<FwdIt, FwdIt> findFirstNewline(FwdIt begin, FwdIt end)
{
    FwdIt it = begin;
    while (it != end)
    {
        switch (*it)
        {
        case '\n':
        case '\v':
        case '\f':
        case Unicode::NextLine:
        case Unicode::LineSeparator:
        case Unicode::ParagraphSeparator:
            begin = it;
            return std::make_pair(begin, ++it);
        case '\r':
            begin = it;
            if (++it != end && *it == '\n')
                ++it;
            return std::make_pair(begin, it);
        default:
            break;
        }
        ++it;
    }
    return std::make_pair(end, end);
}

template <typename FwdIt, typename UnaryFunc>
FwdIt findFirstWhere(FwdIt begin, FwdIt end,
                     UnaryFunc predicate)
{
  while (begin != end)
  {
    if (predicate(*begin))
      return begin;
    ++begin;
  }
  return end;
}

template <typename FwdIt, typename UnaryFunc>
FwdIt findFirstWhereNot(FwdIt begin, FwdIt end,
                        UnaryFunc predicate)
{
  while (begin != end)
  {
    if (!predicate(*begin))
      return begin;
    ++begin;
  }
  return end;
}

template <typename BiIt, typename UnaryFunc>
BiIt findLastWhere(BiIt begin, BiIt end,
                   UnaryFunc predicate,
                   const std::bidirectional_iterator_tag&)
{
    BiIt initialEnd = end;
    while (begin != end)
    {
        --end;
        if (predicate(*end))
            return end;
    }
    return initialEnd;
}

template <typename FwdIt, typename UnaryFunc>
FwdIt findLastWhere(FwdIt begin, FwdIt end,
                    UnaryFunc predicate,
                    const std::input_iterator_tag&)
{
    FwdIt lastMatch = end;
    while (begin != end)
    {
        if (predicate(*begin))
            lastMatch = begin;
        ++begin;
    }
    return lastMatch;
}

template <typename FwdIt, typename UnaryFunc>
FwdIt findLastWhere(FwdIt begin, FwdIt end,
                    UnaryFunc predicate)
{
    return findLastWhere(
                begin, end,
                predicate,
                typename std::iterator_traits<FwdIt>::iterator_category());
}

template <typename BiIt, typename UnaryFunc>
BiIt findLastWhereNot(BiIt begin, BiIt end,
                      UnaryFunc predicate,
                      const std::bidirectional_iterator_tag&)
{
    BiIt initialEnd = end;
    while (begin != end)
    {
        --end;
        if (!predicate(*end))
            return end;
    }
    return initialEnd;
}

template <typename FwdIt, typename UnaryFunc>
FwdIt findLastWhereNot(FwdIt begin, FwdIt end,
                       UnaryFunc predicate,
                       const std::input_iterator_tag&)
{
    FwdIt lastMatch = end;
    while (begin != end)
    {
        if (!predicate(*begin))
            lastMatch = begin;
        ++begin;
    }
    return lastMatch;
}

template <typename FwdIt, typename UnaryFunc>
FwdIt findLastWhereNot(FwdIt begin, FwdIt end,
                       UnaryFunc predicate)
{
    return findLastWhereNot(
                begin, end,
                predicate,
                typename std::iterator_traits<FwdIt>::iterator_category());
}

template <typename FwdIt1, typename FwdIt2>
FwdIt1 findFirstOf(FwdIt1 begin, FwdIt1 end,
                   FwdIt2 cmpBegin, FwdIt2 cmpEnd,
                   FindFlags::Flags flags)
{
    if ((flags & FindFlags::CaseInsensitive) != 0)
        return findFirstWhere(
                    begin, end,
                    isOneOf(cmpBegin, cmpEnd,
                            Unicode::CaseInsensitiveEqual<uint32_t>()));
    else
        return findFirstWhere(begin, end, isOneOf(cmpBegin, cmpEnd));
}

template <typename FwdIt1, typename FwdIt2>
FwdIt1 findFirstNotOf(FwdIt1 begin, FwdIt1 end,
                       FwdIt2 cmpBegin, FwdIt2 cmpEnd,
                       FindFlags::Flags flags)
{
    if ((flags & FindFlags::CaseInsensitive) != 0)
        return findFirstWhereNot(
                    begin, end,
                    isOneOf(cmpBegin, cmpEnd,
                            Unicode::CaseInsensitiveEqual<uint32_t>()));
    else
        return findFirstWhereNot(begin, end, isOneOf(cmpBegin, cmpEnd));
}

template <typename FwdIt1, typename FwdIt2>
FwdIt1 findLastOf(FwdIt1 begin, FwdIt1 end,
                  FwdIt2 cmpBegin, FwdIt2 cmpEnd,
                  FindFlags::Flags flags)
{
    if ((flags & FindFlags::CaseInsensitive) != 0)
        return findLastWhere(
                    begin, end,
                    isOneOf(cmpBegin, cmpEnd,
                            Unicode::CaseInsensitiveEqual<uint32_t>()));
    else
        return findLastWhere(begin, end, isOneOf(cmpBegin, cmpEnd));
}

template <typename FwdIt1, typename FwdIt2>
FwdIt1 findLastNotOf(FwdIt1 begin, FwdIt1 end,
                     FwdIt2 cmpBegin, FwdIt2 cmpEnd,
                     FindFlags::Flags flags)
{
    if ((flags & FindFlags::CaseInsensitive) != 0)
        return findLastWhereNot(
                    begin, end,
                    isOneOf(cmpBegin, cmpEnd,
                            Unicode::CaseInsensitiveEqual<uint32_t>()));
    else
        return findLastWhereNot(begin, end, isOneOf(cmpBegin, cmpEnd));
}

template <typename FwdIt1, typename FwdIt2, typename BinaryFunc>
bool endsWith(FwdIt1 begin, FwdIt1 end,
              FwdIt2 cmpBegin, FwdIt2 cmpEnd,
              BinaryFunc predicate,
              const std::bidirectional_iterator_tag&)
{
    while (end != begin && cmpEnd != cmpBegin)
    {
        if (!predicate(*--end, *--cmpBegin))
            return false;
    }
    return cmpEnd == cmpBegin;
}

template <typename FwdIt1, typename FwdIt2, typename BinaryFunc>
bool endsWith(FwdIt1 begin, FwdIt1 end,
              FwdIt2 cmpBegin, FwdIt2 cmpEnd,
              BinaryFunc predicate,
              const std::input_iterator_tag&)
{
    size_t len = std::distance(cmpBegin, cmpEnd);
    FwdIt1 it = begin;
    for (size_t i = 0; i < len; i++)
    {
        if (it == end)
            return false;
        ++it;
    }
    while (it != end)
    {
        ++it;
        ++begin;
    }
    return cmpEnd == std::mismatch(begin, end, cmpBegin).second;
}

template <typename FwdIt1, typename FwdIt2>
bool endsWith(FwdIt1 begin, FwdIt1 end,
              FwdIt2 cmpBegin, FwdIt2 cmpEnd,
              FindFlags::Flags flags)
{
    if ((flags & FindFlags::CaseInsensitive) == 0)
        return endsWith(
                    begin, end,
                    cmpBegin, cmpEnd,
                    std::equal_to<uint32_t>(),
                    typename std::iterator_traits<FwdIt1>::iterator_category());
    else
        return endsWith(
                    begin, end,
                    cmpBegin, cmpEnd,
                    Unicode::CaseInsensitiveEqual<uint32_t>(),
                    typename std::iterator_traits<FwdIt1>::iterator_category());
}

template <typename FwdIt1, typename FwdIt2>
bool startsWith(FwdIt1 begin, FwdIt1 end,
                FwdIt2 cmpBegin, FwdIt2 cmpEnd,
                FindFlags::Flags flags)
{
    if ((flags & FindFlags::CaseInsensitive) == 0)
        return cmpEnd == Algorithms::mismatch(
                    begin, end,
                    cmpBegin, cmpEnd).second;
    else
        return cmpEnd == Algorithms::mismatch(
                    begin, end,
                    cmpBegin, cmpEnd,
                    Unicode::CaseInsensitiveEqual<uint32_t>()).second;
}

}}}

#endif