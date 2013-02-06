//***************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#include "String.hpp"

#include <iterator>
#include "JEB/Iterators/Iterators.hpp"
#include "JEB/Unicode/CaseInsensitive.hpp"
#include "JEB/Unicode/CaseConverter.hpp"
#include "JEB/Unicode/Unicode.hpp"
#include "Generic/CaseConversion.hpp"
#include "Generic/Find.hpp"
#include "Generic/Join.hpp"
#include "Generic/Replace.hpp"
#include "Generic/Trim.hpp"
#include "Generic/WildcardMatcher.hpp"
#include "Utf8/BiIterator.hpp"
#include "Utf8/Encode.hpp"
#include "Utf8/OutIterator.hpp"
#include "Utf8/Split.hpp"
#include "Utf16/BiIterator.hpp"
#include "StringPredicates.hpp"

namespace JEB { namespace String {

using namespace ::JEB::Iterator;

typedef Utf8::BiIterator<std::string::const_iterator> Utf8Iterator;

namespace detail
{
    std::string string(const Utf8Iterator& begin,
                       const Utf8Iterator& end)
    {
        return std::string(begin.beginCodePoint(), end.beginCodePoint());
    }

    std::string string(const std::pair<Utf8Iterator, Utf8Iterator>& its)
    {
      return std::string(its.first.beginCodePoint(), its.second.beginCodePoint());
    }

    Range range(const Utf8Iterator& it)
    {
      return Range(it.beginCodePoint(), it.endCodePoint());
    }

    // Range range(const Utf8Iterator& beg, const Utf8Iterator& end)
    // {
    //   return Range(beg.beginCodePoint(), end.beginCodePoint());
    // }

    Range range(const std::pair<Utf8Iterator, Utf8Iterator>& its)
    {
      return Range(its.first.beginCodePoint(), its.second.beginCodePoint());
    }

    bool hasFlag(unsigned flags, unsigned flag)
    {
        return (flags & flag) == flag;
    }
}

bool empty(const Range& range)
{
  return range.first == range.second;
}

size_t index(const std::string& str, const Range& range)
{
    return std::distance(str.begin(), range.first);
}

std::pair<size_t, size_t> indexes(const std::string& str, const Range& range)
{
    return std::make_pair(std::distance(str.begin(), range.first),
                          std::distance(str.begin(), range.second));
}

size_t length(const Range& range)
{
    return std::distance(range.first, range.second);
}

Range range(const std::string& str)
{
    return Range(str.begin(), str.end());
}

std::string toString(const Range& range)
{
    return std::string(range.first, range.second);
}

std::string append(const std::string& str, uint32_t chr)
{
    std::string result;
    Utf8::add(std::back_inserter(result), chr);
    return result;
}

void appendInPlace(std::string& str, uint32_t chr)
{
    Utf8::add(std::back_inserter(str), chr);
}

int32_t caseInsensitiveCompare(const std::string& a, const std::string& b)
{
    return Unicode::caseInsensitiveCompare(Utf8::begin(a), Utf8::end(a),
                                           Utf8::begin(b), Utf8::end(b));
}

bool caseInsensitiveEqual(const std::string& a, const std::string& b)
{
    return Unicode::caseInsensitiveEqual(Utf8::begin(a), Utf8::end(a),
                                         Utf8::begin(b), Utf8::end(b));
}

bool caseInsensitiveLess(const std::string& a, const std::string& b)
{
    return Unicode::caseInsensitiveLess(Utf8::begin(a), Utf8::end(a),
                                        Utf8::begin(b), Utf8::end(b));
}

Range characterRange(const std::string& str, long pos)
{
    return detail::range(Unicode::characterRange(
            Utf8::begin(str), Utf8::end(str), pos));
}

uint32_t chr(const std::string& str, long pos)
{
    Utf8Iterator it = Throwing::nth(Utf8::begin(str), Utf8::end(str), pos);
    if (it.empty())
        throw std::range_error("index is out if range");
    return *it;
}

Range chrRange(const std::string& str, long pos)
{
    return nth(Utf8::begin(str), Utf8::end(str), pos).range();
}

size_t distance(const char* begin, const char* end)
{
    return std::distance(Utf8::begin(begin, end), Utf8::end(begin, end));
}

size_t distance(std::string::iterator begin, std::string::iterator end)
{
    return std::distance(Utf8::begin(begin, end), Utf8::end(begin, end));
}

size_t distance(std::string::const_iterator begin, std::string::const_iterator end)
{
    return std::distance(Utf8::begin(begin, end), Utf8::end(begin, end));
}

bool endsWith(const std::string& str,
              const std::string& cmp,
              FindFlags::Flags flags)
{
    return Generic::endsWith(Utf8::begin(str), Utf8::end(str),
                             Utf8::begin(cmp), Utf8::end(cmp),
                             flags);
}

Range find(const std::string& str,
           const std::string& sub,
           FindFlags::Flags flags)
{
    return find(str.begin(), str.end(), sub, flags);
}

Range find(Iterator begin, Iterator end,
           const std::string& cmp,
           FindFlags::Flags flags)
{
    return detail::range(Generic::find(
            Utf8::begin(begin, end), Utf8::end(begin, end),
            Utf8::begin(cmp), Utf8::end(cmp),
            flags));
}

Range findFirstNewline(const std::string& str)
{
    return findFirstNewline(str.begin(), str.end());
}

Range findFirstNewline(Iterator begin, Iterator end)
{
    return detail::range(Generic::findFirstNewline(
            Utf8::begin(begin, end), Utf8::end(begin, end)));
}

Range findFirstOf(const std::string& str,
                  const std::string& chars,
                  FindFlags::Flags flags)
{
    return findFirstOf(str.begin(), str.end(), chars, flags);
}

Range findFirstOf(Iterator begin, Iterator end,
                  const std::string& chars,
                  FindFlags::Flags flags)
{
    return detail::range(Generic::findFirstOf(
                Utf8::begin(begin, end), Utf8::end(begin, end),
                Utf8::begin(chars), Utf8::end(chars),
                flags));
}

Range findFirstNotOf(const std::string& str,
                     const std::string& chars,
                     FindFlags::Flags flags)
{
    return findFirstNotOf(str.begin(), str.end(), chars, flags);
}

Range findFirstNotOf(Iterator begin, Iterator end,
                     const std::string& chars,
                     FindFlags::Flags flags)
{
    return detail::range(Generic::findFirstNotOf(
                Utf8::begin(begin, end), Utf8::end(begin, end),
                Utf8::begin(chars), Utf8::end(chars),
                flags));
}

Range findLastOf(const std::string& str,
                 const std::string& chars,
                 FindFlags::Flags flags)
{
    return findLastOf(str.begin(), str.end(), chars, flags);
}

Range findLastOf(Iterator begin, Iterator end,
                 const std::string& chars,
                 FindFlags::Flags flags)
{
    return detail::range(Generic::findLastOf(
                Utf8::begin(begin, end), Utf8::end(begin, end),
                Utf8::begin(chars), Utf8::end(chars),
                flags));
}

Range findLastNotOf(const std::string& str,
                    const std::string& chars,
                    FindFlags::Flags flags)
{
    return findLastNotOf(str.begin(), str.end(), chars, flags);
}

Range findLastNotOf(Iterator begin, Iterator end,
                    const std::string& chars,
                    FindFlags::Flags flags)
{
    return detail::range(Generic::findLastNotOf(
                Utf8::begin(begin, end), Utf8::end(begin, end),
                Utf8::begin(chars), Utf8::end(chars),
                flags));
}

Range findFirstWhere(const std::string& str,
                     std::function<bool(uint32_t)> predicate)
{
    return findFirstWhere(str.begin(), str.end(), predicate);
}

Range findFirstWhere(Iterator begin, Iterator end,
                     std::function<bool(uint32_t)> predicate)
{
  return detail::range(Generic::findFirstWhere(
          Utf8::begin(begin, end), Utf8::end(begin, end),
          predicate));
}

Range findFirstWhereNot(const std::string& str,
                        std::function<bool(uint32_t)> predicate)
{
    return findFirstWhereNot(str.begin(), str.end(), predicate);
}

Range findFirstWhereNot(Iterator begin, Iterator end,
                        std::function<bool(uint32_t)> predicate)
{
  return detail::range(Generic::findFirstWhereNot(
          Utf8::begin(begin, end), Utf8::end(begin, end),
          predicate));
}

Range findLastWhere(const std::string& str,
                    std::function<bool(uint32_t)> predicate)
{
    return findLastWhere(str.begin(), str.end(), predicate);
}

Range findLastWhere(Iterator begin, Iterator end,
                    std::function<bool(uint32_t)> predicate)
{
  return detail::range(Generic::findLastWhere(
          Utf8::begin(begin, end), Utf8::end(begin, end),
          predicate));
}

Range findLastWhereNot(const std::string& str,
                       std::function<bool(uint32_t)> predicate)
{
    return findLastWhereNot(str.begin(), str.end(), predicate);
}

Range findLastWhereNot(Iterator begin, Iterator end,
                       std::function<bool(uint32_t)> predicate)
{
  return detail::range(Generic::findLastWhereNot(
          Utf8::begin(begin, end), Utf8::end(begin, end),
          predicate));
}

bool hasWildcards(const std::string& str)
{
    return Generic::hasWildcards(Utf8::begin(str), Utf8::end(str));
}

void insertInPlace(std::string& str,
                   long pos,
                   const std::string& sub)
{
    Range r = chrRange(str, pos);
    str.insert(index(str, r), sub);
}

std::string insert(const std::string& str,
                   long pos,
                   const std::string& sub)
{
    Range r = chrRange(str, pos);
    std::string result(str.begin(), r.first);
    result.append(sub);
    result.append(r.first, str.end());
    return result;
}

std::string insert(const std::string& str,
                   long pos,
                   uint32_t chr)
{
    Range r = chrRange(str, pos);
    std::string result(str.begin(), r.first);
    appendInPlace(result, chr);
    result.append(r.first, str.end());
    return result;
}

bool isValidUtf8(const std::string& str)
{
    return Utf8::isValid(str.begin(), str.end());
}

std::string join(const std::vector<std::string>& parts,
                 const std::string& separator)
{
    return Generic::join(parts.begin(), parts.end(), separator);
}

size_t length(const std::string& str)
{
    return std::distance(Utf8::begin(str), Utf8::end(str));
}

std::string lower(const std::string& str)
{
    std::string result;
    Generic::lower(Utf8::begin(str), Utf8::end(str),
                   Utf8::backInserter(result));
    return result;
}

size_t numberOfCharacters(const std::string& str)
{
    return Unicode::numberOfCharacters(Utf8::begin(str), Utf8::end(str));
}

std::string replace(const std::string& str,
                    const std::string& from,
                    const std::string& to,
                    size_t max,
                    FindFlags::Flags flags)
{
    std::string result;
    Generic::replace(Utf8::begin(str), Utf8::end(str),
                     Utf8::begin(from), Utf8::end(from),
                     Utf8::begin(to), Utf8::end(to),
                     Utf8::backInserter(result),
                     max,
                     flags);
    return result;
}

std::string replace(const std::string& s,
                    uint32_t fromChar,
                    uint32_t toChar,
                    size_t max)
{
    std::string from = toString(fromChar);
    std::string to = toString(toChar);
    std::string result;
    Generic::replace(s.begin(), s.end(),
                     from.cbegin(), from.cend(),
                     to.cbegin(), to.cend(),
                     std::back_inserter(result),
                     max,
                     FindFlags::Defaults);
    return result;
}

std::string replaceInvalidUtf8(const std::string& str, uint32_t chr)
{
    std::string result;
    result.reserve(str.size());
    std::string::const_iterator beg = str.begin();
    std::string::const_iterator it = str.begin();
    while (it != str.end())
    {
        uint32_t cp;
        if (!Utf8::nextCodePoint(cp, it, str.end()) && it != str.end())
        {
            result.append(beg, it);
            beg = ++it;
            append(result, chr);
        }
    }
    result.append(beg, str.end());
    return result;
}

void replaceInvalidUtf8InPlace(std::string& str, char chr)
{
    assert(chr > 0);
    std::string::iterator it = str.begin();
    while (it != str.end())
    {
        uint32_t cp;
        if (!Utf8::nextCodePoint(cp, it, str.end()) && it != str.end())
            *it++ = chr;
    }
}

std::vector<std::string> split(
        const std::string& str,
        size_t maxSplits,
        SplitFlags::Flags flags)
{
    std::vector<std::string> parts;
    Utf8::split(parts, str, maxSplits, flags);
    return parts;
}

std::vector<std::string> split(
        const std::string& str,
        const std::string& sep,
        size_t maxSplits,
        SplitFlags::Flags flags)
{
    std::vector<std::string> parts;
    Utf8::split(parts, str, sep, maxSplits, flags);
    return parts;
}

std::vector<std::string> splitToken(
        const std::string& str,
        uint32_t sep,
        size_t maxSplits,
        SplitFlags::Flags flags)
{
    if (!SplitFlags::caseInsensitive(flags))
        return splitWhere(str, isCharacter(sep), maxSplits, flags);
    else
        return splitWhere(
                str,
                isCharacter(sep, Unicode::CaseInsensitiveEqual<uint32_t>()),
                maxSplits,
                flags);
}

std::vector<std::string> splitToken(
        const std::string& str,
        const std::string& seps,
        size_t maxSplits,
        SplitFlags::Flags flags)
{
    if (!SplitFlags::caseInsensitive(flags))
        return splitWhere(
                str,
                isOneOf(Utf8::begin(seps), Utf8::end(seps)),
                maxSplits,
                flags);
    else
        return splitWhere(
                str,
                isOneOf(Utf8::begin(seps), Utf8::end(seps),
                        Unicode::CaseInsensitiveEqual<uint32_t>()),
                maxSplits,
                flags);
}

std::vector<std::string> splitWhere(
        const std::string& str,
        const std::function<bool(uint32_t)> predicate,
        size_t maxSplits,
        SplitFlags::Flags flags)
{
    std::vector<std::string> parts;
    Utf8::splitWithFinder(
            parts,
            str,
            Utf8::tokenFinder(predicate, SplitFlags::mergeTokens(flags)),
            maxSplits,
            SplitFlags::ignoreEmpty(flags));
    return parts;
}

std::pair<std::string, std::string> splitFirst(
        const std::string& str,
        SplitFlags::Flags flags)
{
    return Utf8::splitPairWithFinder(
            str,
            Utf8::tokenFinder(isWhitespace(),
                        SplitFlags::mergeTokens(flags)));
}

std::pair<std::string, std::string> splitFirst(
        const std::string& str,
        const std::string& sep,
        SplitFlags::Flags flags)
{
    if (!SplitFlags::caseInsensitive(flags))
        return Utf8::splitPairWithFinder(str, Utf8::firstFinder(sep));
    else
        return Utf8::splitPairWithFinder(
                str,
                Utf8::firstFinder(sep, Unicode::CaseInsensitiveEqual<uint32_t>()));
}

std::pair<std::string, std::string> splitFirstToken(
        const std::string& str,
        uint32_t sep,
        SplitFlags::Flags flags)
{
    if (!SplitFlags::caseInsensitive(flags))
        return splitFirstWhere(str, isCharacter(sep), flags);
    else
        return splitFirstWhere(
                str,
                isCharacter(sep, Unicode::CaseInsensitiveEqual<uint32_t>()),
                flags);
}

std::pair<std::string, std::string> splitFirstToken(
        const std::string& str,
        const std::string& seps,
        SplitFlags::Flags flags)
{
    if (!SplitFlags::caseInsensitive(flags))
        return splitFirstWhere(
                str,
                isOneOf(Utf8::begin(seps), Utf8::end(seps)),
                flags);
    else
        return splitFirstWhere(
                str,
                isOneOf(Utf8::begin(seps), Utf8::end(seps),
                        Unicode::CaseInsensitiveEqual<uint32_t>()),
                flags);
}

std::pair<std::string, std::string> splitFirstWhere(
        const std::string& str,
        const std::function<bool(uint32_t)>& predicate,
        SplitFlags::Flags flags)
{
    return Utf8::splitPairWithFinder(
            str,
            Utf8::tokenFinder(predicate, SplitFlags::mergeTokens(flags)));
}

std::pair<std::string, std::string> splitLast(
        const std::string& str,
        SplitFlags::Flags flags)
{
    return Utf8::splitPairWithFinder(
            str,
            Utf8::lastTokenFinder(isWhitespace(),
                                  SplitFlags::mergeTokens(flags)));
}

std::pair<std::string, std::string> splitLast(
        const std::string& str,
        const std::string& sep,
        SplitFlags::Flags flags)
{
    if (!SplitFlags::caseInsensitive(flags))
        return Utf8::splitPairWithFinder(str, Utf8::lastFinder(sep));
    else
        return Utf8::splitPairWithFinder(
                str,
                Utf8::lastFinder(sep, Unicode::CaseInsensitiveEqual<uint32_t>()));
}

std::pair<std::string, std::string> splitLastToken(
        const std::string& str,
        uint32_t sep,
        SplitFlags::Flags flags)
{
    if (!SplitFlags::caseInsensitive(flags))
        return splitLastWhere(str, isCharacter(sep), flags);
    else
        return splitLastWhere(
                str,
                isCharacter(sep, Unicode::CaseInsensitiveEqual<uint32_t>()),
                flags);
}

std::pair<std::string, std::string> splitLastToken(
        const std::string& str,
        const std::string& seps,
        SplitFlags::Flags flags)
{
    if (!SplitFlags::caseInsensitive(flags))
        return splitLastWhere(
                str,
                isOneOf(Utf8::begin(seps), Utf8::end(seps)),
                flags);
    else
        return splitLastWhere(
                str,
                isOneOf(Utf8::begin(seps), Utf8::end(seps),
                        Unicode::CaseInsensitiveEqual<uint32_t>()),
                flags);
}

std::pair<std::string, std::string> splitLastWhere(
        const std::string& str,
        const std::function<bool(uint32_t)>& predicate,
        SplitFlags::Flags flags)
{
    return Utf8::splitPairWithFinder(
            str,
            Utf8::lastTokenFinder(predicate, SplitFlags::mergeTokens(flags)));
}

bool startsWith(const std::string& str,
                const std::string& cmp,
                FindFlags::Flags flags)
{
    return Generic::startsWith(Utf8::begin(str), Utf8::end(str),
                               Utf8::begin(cmp), Utf8::end(cmp),
                               flags);
}

std::string substring(const std::string& str, long startIndex, long endIndex)
{
    Utf8Iterator begin = nth(Utf8::begin(str), Utf8::end(str), startIndex);
    if (startIndex > 0 && endIndex > 0)
        endIndex -= startIndex;
    Utf8Iterator end = nth(begin, Utf8::end(str), endIndex);
    return detail::string(begin, end);
}

std::string substring(const std::string& str,
                      std::pair<size_t, size_t>& indexes)
{
    return substring(str,
                     static_cast<long>(indexes.first),
                     static_cast<long>(indexes.second));
}

std::string toString(uint32_t chr)
{
    char buffer[Utf8::MAX_ENCODED_LENGTH];
    size_t n = Utf8::encode(buffer, chr);
    return std::string(buffer, buffer + n);
}

std::string title(const std::string& str)
{
    std::string result;
    Generic::title(Utf8::begin(str), Utf8::end(str),
                   Utf8::backInserter(result));
    return result;
}

std::string toUtf8(const std::wstring& str, Encoding::Enum encoding)
{
    std::string result;
    result.reserve(str.size());
    switch (encoding)
    {
    case Encoding::Utf16:
        std::copy(Utf16::begin(str), Utf16::end(str), Utf8::backInserter(result));
        break;
    default:
        throw std::logic_error(FORMAT_STRING("Convert to UTF-8: unsupported encoding " << encoding << "."));
    }
    return result;
}

std::string trim(const std::string& str)
{
    return detail::string(Generic::trim(
                Utf8::begin(str), Utf8::end(str),
                isWhitespace()));
}

std::string trim(const std::string& str,
                 const std::function<bool(uint32_t)>& predicate)
{
    return detail::string(Generic::trim(
                Utf8::begin(str), Utf8::end(str),
                predicate));
}

std::string trim(const std::string& str,
                 const std::string& chars)
{
    return detail::string(Generic::trim(
                Utf8::begin(str), Utf8::end(str),
                isOneOf(Utf8::begin(chars), Utf8::end(chars))));
}

std::string trimStart(const std::string& str)
{
    return detail::string(Generic::trimStart(
                Utf8::begin(str), Utf8::end(str),
                isWhitespace()));
}

std::string trimStart(const std::string& str,
                      const std::function<bool(uint32_t)>& predicate)
{
    return detail::string(Generic::trimStart(
                Utf8::begin(str), Utf8::end(str),
                predicate));
}

std::string trimStart(const std::string& str,
                      const std::string& chars)
{
    return detail::string(Generic::trimStart(
                Utf8::begin(str), Utf8::end(str),
                isOneOf(Utf8::begin(chars), Utf8::end(chars))));
}

std::string trimEnd(const std::string& str)
{
    return detail::string(Generic::trimEnd(
                Utf8::begin(str), Utf8::end(str),
                isWhitespace()));
}

std::string trimEnd(const std::string& str,
                    const std::function<bool(uint32_t)>& predicate)
{
    return detail::string(Generic::trimEnd(
                Utf8::begin(str), Utf8::end(str),
                predicate));
}

std::string trimEnd(const std::string& str,
                    const std::string& chars)
{
    return detail::string(Generic::trimEnd(
                Utf8::begin(str), Utf8::end(str),
                isOneOf(Utf8::begin(chars), Utf8::end(chars))));
}

std::string upper(const std::string& str)
{
    std::string result;
    Generic::upper(Utf8::begin(str), Utf8::end(str),
                   Utf8::backInserter(result));
    return result;
}

// Range findFirstUnescaped(const std::string& str, uint32_t chr)
// {
//     return findFirstUnescaped(str.begin(), str.end(), chr);
// }

// Range findFirstUnescaped(Iterator begin, Iterator end, uint32_t chr)
// {
//     return detail::range(Generic::findFirstUnescaped(
//                 Utf8::begin(begin, end), Utf8::end(begin, end), chr));
// }

// Range findFirstUnescapedOf(const std::string& str,
//                            const std::string& chars)
// {
//     return findFirstUnescapedOf(str.begin(), str.end(), chars);
// }

// Range findFirstUnescapedOf(Iterator begin, Iterator end,
//                            const std::string& chars)
// {
//     return detail::range(Generic::findFirstUnescapedOf(
//                 Utf8::begin(begin, end), Utf8::end(begin, end),
//                 Utf8::begin(chars), Utf8::end(chars)));
// }

// Range findFirstUnescapedNotOf(const std::string& str,
//                               const std::string& chars)
// {
//     return findFirstUnescapedNotOf(str.begin(), str.end(), chars);
// }

// Range findFirstUnescapedNotOf(Iterator begin, Iterator end,
//                               const std::string& chars)
// {
//     return detail::range(Generic::findFirstUnescapedNotOf(
//                 Utf8::begin(begin, end), Utf8::end(begin, end),
//                 Utf8::begin(chars), Utf8::end(chars)));
// }

// Range findFirstUnescapedWhere(const std::string& str,
//                               std::function<bool(uint32_t)>& predicate)
// {
//     return findFirstUnescapedWhere(str.begin(), str.end(), predicate);
// }

// Range findFirstUnescapedWhere(Iterator begin, Iterator end,
//                               std::function<bool(uint32_t)>& predicate)
// {
//     return detail::range(Generic::findFirstUnescapedWhere(
//                 Utf8::begin(begin, end), Utf8::end(begin, end), predicate));
// }

// Range findFirstUnescapedWhereNot(const std::string& str,
//                                  std::function<bool(uint32_t)>& predicate)
// {
//     return findFirstUnescapedWhereNot(str.begin(), str.end(), predicate);
// }

// Range findFirstUnescapedWhereNot(Iterator begin, Iterator end,
//                                  std::function<bool(uint32_t)>& predicate)
// {
//     return detail::range(Generic::findFirstUnescapedWhereNot(
//                 Utf8::begin(begin, end), Utf8::end(begin, end), predicate));
// }

struct WildcardExpression::Data
{
    Generic::WildcardMatcher matcher;
};

WildcardExpression::WildcardExpression()
    : m_Data(new Data)
{
}

WildcardExpression::~WildcardExpression()
{
}

WildcardExpression::Data* WildcardExpression::data() const
{
    return m_Data.get();
}

WildcardExpression parseWildcards(const std::string& expr)
{
    WildcardExpression we;
    we.data()->matcher.parse(Utf8::begin(expr), Utf8::end(expr));
    return we;
}

bool match(const WildcardExpression& expr, const std::string& str)
{
    return expr.data()->matcher.match(Utf8::begin(str), Utf8::end(str));
}

Range findShortest(const WildcardExpression& expr, const std::string& str)
{
    return detail::range(expr.data()->matcher.findShortest(
                Utf8::begin(str), Utf8::end(str)));
}

Range findLongest(const WildcardExpression& expr, const std::string& str)
{
    return detail::range(expr.data()->matcher.find(
                Utf8::begin(str), Utf8::end(str)));
}

}}
