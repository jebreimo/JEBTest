//***************************************************************************
// Copyright © 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#ifndef JEB_WSTRING_HPP
#define JEB_WSTRING_HPP

#include <cstdint>
#include <functional>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include "StringFlags.hpp"

/** @file
  * @brief Defines functions for working with std::wstring
  */

namespace JEB {

/** @brief The namespace for functions working on std::wstring
  */
namespace String
{

#define FORMAT_STRING(msg) \
    static_cast<std::ostringstream&>(static_cast<std::ostream&>(std::ostringstream()) << msg).str()

typedef std::wstring::const_iterator Iterator;
typedef std::pair<Iterator, Iterator> Range;

bool empty(const Range& range);

size_t index(const std::wstring& str, const Range& range);

std::pair<size_t, size_t> indexes(const std::wstring& str, const Range& range);

size_t length(const Range& range);

Range range(const std::wstring& str);

std::wstring toString(const Range& range);

std::wstring append(std::wstring& str, uint32_t chr);

void appendInPlace(std::wstring& str, uint32_t chr);

Range characterRange(const std::wstring str, long pos);

uint32_t chr(const std::wstring str, long pos);

Range chrRange(const std::wstring str, long pos);

bool endsWith(const std::wstring& str,
              const std::wstring& cmp,
              FindFlags::Flags flags = FindFlags::Defaults);

Range find(const std::wstring& str,
           const std::wstring& sub,
           FindFlags::Flags flags = FindFlags::Defaults);

Range find(Iterator begin, Iterator end,
           const std::wstring& sub,
           FindFlags::Flags flags = FindFlags::Defaults);

Range findFirstOf(const std::wstring& str,
                  const std::wstring& chars,
                  FindFlags::Flags flags = FindFlags::Defaults);

Range findFirstOf(Iterator begin, Iterator end,
                  const std::wstring& chars,
                  FindFlags::Flags flags = FindFlags::Defaults);

Range findFirstNotOf(const std::wstring& str,
                     const std::wstring& chars,
                     FindFlags::Flags flags = FindFlags::Defaults);

Range findFirstNotOf(Iterator begin, Iterator end,
                     const std::wstring& chars,
                     FindFlags::Flags flags = FindFlags::Defaults);

Range findLastOf(const std::wstring& str,
                 const std::wstring& chars,
                 FindFlags::Flags flags = FindFlags::Defaults);

Range findLastOf(Iterator begin, Iterator end,
                 const std::wstring& chars,
                 FindFlags::Flags flags = FindFlags::Defaults);

Range findLastNotOf(const std::wstring& str,
                    const std::wstring& chars,
                    FindFlags::Flags flags = FindFlags::Defaults);

Range findLastNotOf(Iterator begin, Iterator end,
                    const std::wstring& chars,
                    FindFlags::Flags flags = FindFlags::Defaults);

Range findFirstWhere(const std::wstring& str,
                     std::function<bool(uint32_t)> predicate);
Range findFirstWhere(Iterator begin, Iterator end,
                     std::function<bool(uint32_t)> predicate);

Range findFirstWhereNot(const std::wstring& str,
                        std::function<bool(uint32_t)> predicate);
Range findFirstWhereNot(Iterator begin, Iterator end,
                        std::function<bool(uint32_t)> predicate);

Range findLastWhere(const std::wstring& str,
                    std::function<bool(uint32_t)> predicate);
Range findLastWhere(Iterator begin, Iterator end,
                    std::function<bool(uint32_t)> predicate);

Range findLastWhereNot(const std::wstring& str,
                       std::function<bool(uint32_t)> predicate);
Range findLastWhereNot(Iterator begin, Iterator end,
                       std::function<bool(uint32_t)> predicate);

bool hasWildcards(const std::wstring& str);

std::wstring insert(const std::wstring& str,
                   long pos,
                   const std::wstring& sub);

std::wstring insert(const std::wstring& str,
                   long pos,
                   uint32_t chr);

void insertInPlace(std::wstring& str,
                   long pos,
                   const std::wstring& sub);

bool isValidUtf16(const std::wstring& str);

/** @brief Returns a single string that is the concatenation of the strings
 *         in @a parts.
 *
 *  @param parts     the strings that will be joined
 *  @param separator the strings in @a parts will be separated by this.
 */
std::wstring join(const std::vector<std::wstring>& parts,
                 const std::wstring& separator = std::wstring());

size_t length(const std::wstring& str);

std::wstring lower(const std::wstring& str);

/** @brief Returns a copy of @a str where instances of @a from are replaced
 *      with @a to.
 *
 * @param max The maximum number of replacements that will be performed. All
 *      instances of @a from are replaced if 0.
 */
std::wstring replace(const std::wstring& str,
                    const std::wstring& from,
                    const std::wstring& to,
                    size_t max = 0,
                    FindFlags::Flags flags = FindFlags::Defaults);

/** @brief Returns a copy of @a str with instances of @a fromChar replaced
 *      with @a toChar.
 *
 *  @param max The maximum number of replacements that will be performed. All
 *      instances of @a from are replaced if 0.
 */
std::wstring replace(const std::wstring& s,
                    uint32_t fromChar,
                    uint32_t toChar,
                    size_t max = 0);

std::wstring replaceInvalidUtf16(const std::wstring& str, uint32_t chr);

void replaceInvalidUtf16InPlace(std::wstring& str, char chr);

std::vector<std::wstring> split(
        const std::wstring& str,
        size_t maxSplits = 0,
        SplitFlags::Flags flags = SplitFlags::IgnoreEmpty);

std::vector<std::wstring> split(
        const std::wstring& str,
        const std::wstring& sep,
        size_t maxSplits = 0,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::vector<std::wstring> splitToken(
        const std::wstring& str,
        uint32_t sep,
        size_t maxSplits = 0,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::vector<std::wstring> splitToken(
        const std::wstring& str,
        const std::wstring& seps,
        size_t maxSplits = 0,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::vector<std::wstring> splitWhere(
        const std::wstring& str,
        const std::function<bool(uint32_t)> predicate,
        size_t maxSplits = 0,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::wstring, std::wstring> splitFirst(
        const std::wstring& str,
        SplitFlags::Flags flags = SplitFlags::MergeTokens);

std::pair<std::wstring, std::wstring> splitFirst(
        const std::wstring& str,
        const std::wstring& sep,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::wstring, std::wstring> splitFirstToken(
        const std::wstring& str,
        uint32_t sep,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::wstring, std::wstring> splitFirstToken(
        const std::wstring& str,
        const std::wstring& seps,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::wstring, std::wstring> splitFirstWhere(
        const std::wstring& str,
        const std::function<bool(uint32_t)>& predicate,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::wstring, std::wstring> splitLast(
        const std::wstring& str,
        SplitFlags::Flags flags = SplitFlags::MergeTokens);

std::pair<std::wstring, std::wstring> splitLast(
        const std::wstring& str,
        const std::wstring& sep,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::wstring, std::wstring> splitLastToken(
        const std::wstring& str,
        uint32_t sep,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::wstring, std::wstring> splitLastToken(
        const std::wstring& str,
        const std::wstring& seps,
        SplitFlags::Flags flags = SplitFlags::Defaults);

/**
 *  @note The function is named splitLastWhere rather than splitLast to
 *      overcome a weakness in the VS2010 compiler; it considers calls
 *      to this function or the other splitLast function with three
 *      parameters amiguous if they have the same name.
 */
std::pair<std::wstring, std::wstring> splitLastWhere(
        const std::wstring& str,
        const std::function<bool(uint32_t)>& predicate,
        SplitFlags::Flags flags = SplitFlags::Defaults);

bool startsWith(const std::wstring& str,
                const std::wstring& cmp,
                FindFlags::Flags flags = FindFlags::Defaults);

std::wstring substring(const std::wstring& str,
                      long startIndex,
                      long endIndex = std::numeric_limits<long>::max());

std::wstring substring(const std::wstring& str,
                      std::pair<size_t, size_t>& indexes);

std::wstring title(const std::wstring& str);

std::wstring toString(uint32_t chr);

// std::wstring toUtf16(const std::string& str, Encoding encoding);
// std::wstring toUtf16(const std::wstring& str, Encoding encoding);
// std::wstring toUtf16(const std::vector<uint32_t>& str, Encoding encoding);
// std::wstring fromUtf16(const std::wstring& str, Encoding encoding);

std::wstring trim(const std::wstring& str);

std::wstring trim(const std::wstring& str,
                 const std::function<bool(uint32_t)>& predicate);

std::wstring trim(const std::wstring& str,
                 const std::wstring& chars);

std::wstring trimStart(const std::wstring& str);

std::wstring trimStart(const std::wstring& str,
                      const std::function<bool(uint32_t)>& predicate);

std::wstring trimStart(const std::wstring& str,
                      const std::wstring& chars);

std::wstring trimEnd(const std::wstring& str);

std::wstring trimEnd(const std::wstring& str,
                    const std::function<bool(uint32_t)>& predicate);

std::wstring trimEnd(const std::wstring& str,
                    const std::wstring& chars);

std::wstring upper(const std::wstring& str);

class WildcardExpression
{
public:
    struct Data;
    WildcardExpression();
    ~WildcardExpression();
    Data* data() const;
private:
    std::shared_ptr<Data> m_Data;
};

WildcardExpression parseWildcards(const std::wstring& expr);
bool match(const WildcardExpression& expr, const std::wstring& str);
Range findShortest(const WildcardExpression& expr, const std::wstring& str);
Range findLongest(const WildcardExpression& expr, const std::wstring& str);

}
}

#endif
