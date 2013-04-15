//***************************************************************************
// Copyright © 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#ifndef JEB_STRING_HPP
#define JEB_STRING_HPP

#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "StringFlags.hpp"

/** @file
  * @brief Defines functions for working with UTF-8 encoded std::string
  */

namespace JEB {

/** @brief The namespace for functions working with UTF-8 encoded std::string
  *
  * @note It is not safe to use any function that involve case conversion in
  *     the initialization of static variables. The case-conversion code itself
  *     relies on static variables being initialized, and the initialization
  *     order of static variables is unpredictable.
  */
namespace String
{

#ifdef _MSC_VER
  #define FORMAT_STRING(msg) \
      static_cast<std::ostringstream&>(static_cast<std::ostream&>(std::ostringstream()) << msg).str()
#else
  #define FORMAT_STRING(msg) \
      (std::ostringstream() << msg).str()
#endif

#define FORMAT_WSTRING(msg) \
    static_cast<std::wostringstream&>(static_cast<std::wostream&>(std::wostringstream()) << msg).str()

typedef std::string::const_iterator Iterator;
typedef std::pair<Iterator, Iterator> Range;

/** @brief Returns true if @a range.first is equal to @a range.second.
 */
bool empty(const Range& range);

size_t index(const std::string& str, const Range& range);

std::pair<size_t, size_t> indexes(const std::string& str, const Range& range);

/** @brief Returns the number of bytes between @a range.first and @a range.second.
 */
size_t length(const Range& range);

/** @brief Returns a range equivalent to the entire string @a str.
 */
Range range(const std::string& str);

/** @brief Returns a new string with the characters beween @a range.first
 *      and @a range.second.
 */
std::string toString(const Range& range);

/** @brief Returns a copy of @a str with @a codePoint encoded as UTF-8
 *      at the end.
 *
 *  @return a copy of @a str ending with @a codePoint.
 */
std::string append(const std::string& str, uint32_t chr);

/** @brief Adds @a codePoint encoded as UTF-8 to the end of@a str.
 */
void appendInPlace(std::string& str, uint32_t chr);

/** @brief compares @a a and @a b, ignoring any differences in letter casing.
 *  @returns @arg < 0 if @a a is less than @a b
 *           @arg 0 if @a a is equal to @a b
 *           @arg > 0 if @a a is greater than @a b
 */
int32_t caseInsensitiveCompare(const std::string& a, const std::string& b);

bool caseInsensitiveEqual(const std::string& a, const std::string& b);

bool caseInsensitiveLess(const std::string& a, const std::string& b);

/** @brief Returns iterators starting at and immediately after character @a pos
 *      in @a str.
 *
 *  This function consider combining marks part of the character.
 *  (Combining marks are code points that are not characters themselves, but
 *   instead manipulate the preceding codepoint, by for instance adding an
 *   accent).
 *
 *  @param str The string to be searched.
 *  @param pos The index of the code point. If positive, look from the start of
 *      @a str. If negative, look from the end of @a str.
 *  @see chrRange characterRange
 */
Range characterRange(const std::string& str, long pos);

/** @brief Returns the code point at @a pos in @a str.
 *
 *  @param str The string to be searched.
 *  @param pos The index of the code point. If positive, look from the start of
 *      @a str. If negative, look from the end of @a str.
 *  @see chrRange characterRange
 */
uint32_t chr(const std::string& str, long pos);

/** @brief Returns iterators starting at and immediately after code point @a pos
 *      in @a str.
 *
 *  @param str The string to be searched.
 *  @param pos The index of the code point. If positive, look from the start of
 *      @a str. If negative, look from the end of @a str.
 *  @see chrRange characterRange
 */
Range chrRange(const std::string& str, long pos);

size_t distance(const char* begin, const char* end);
size_t distance(std::string::iterator begin, std::string::iterator end);
size_t distance(std::string::const_iterator begin, std::string::const_iterator end);

bool endsWith(const std::string& str,
              const std::string& cmp,
              FindFlags::Flags flags = FindFlags::Defaults);

Range find(const std::string& str,
           const std::string& sub,
           FindFlags::Flags flags = FindFlags::Defaults);

Range find(Iterator begin, Iterator end,
           const std::string& sub,
           FindFlags::Flags flags = FindFlags::Defaults);

/** @brief Returns the start and end of the next newline in @a str.
 *
 *  @return If the file uses DOS-newlines ("\\r\\n"), @a first will point to
 *      '\\r' and @a second will point to the first character after '\\n'.
 */
Range findFirstNewline(const std::string& str);

/** @brief Returns the start and end of the next newline from @a begin.
 */
Range findFirstNewline(Iterator begin, Iterator end);

Range findFirstOf(const std::string& str,
                  const std::string& chars,
                  FindFlags::Flags flags = FindFlags::Defaults);

Range findFirstOf(Iterator begin, Iterator end,
                  const std::string& chars,
                  FindFlags::Flags flags = FindFlags::Defaults);

Range findFirstNotOf(const std::string& str,
                     const std::string& chars,
                     FindFlags::Flags flags = FindFlags::Defaults);

Range findFirstNotOf(Iterator begin, Iterator end,
                     const std::string& chars,
                     FindFlags::Flags flags = FindFlags::Defaults);

Range findLastOf(const std::string& str,
                 const std::string& chars,
                 FindFlags::Flags flags = FindFlags::Defaults);

Range findLastOf(Iterator begin, Iterator end,
                 const std::string& chars,
                 FindFlags::Flags flags = FindFlags::Defaults);

Range findLastNotOf(const std::string& str,
                    const std::string& chars,
                    FindFlags::Flags flags = FindFlags::Defaults);

Range findLastNotOf(Iterator begin, Iterator end,
                    const std::string& chars,
                    FindFlags::Flags flags = FindFlags::Defaults);

Range findFirstWhere(const std::string& str,
                     std::function<bool(uint32_t)> predicate);
Range findFirstWhere(Iterator begin, Iterator end,
                     std::function<bool(uint32_t)> predicate);

Range findFirstWhereNot(const std::string& str,
                        std::function<bool(uint32_t)> predicate);
Range findFirstWhereNot(Iterator begin, Iterator end,
                        std::function<bool(uint32_t)> predicate);

Range findLastWhere(const std::string& str,
                    std::function<bool(uint32_t)> predicate);
Range findLastWhere(Iterator begin, Iterator end,
                    std::function<bool(uint32_t)> predicate);

Range findLastWhereNot(const std::string& str,
                       std::function<bool(uint32_t)> predicate);
Range findLastWhereNot(Iterator begin, Iterator end,
                       std::function<bool(uint32_t)> predicate);

std::string insert(const std::string& str,
                   long pos,
                   const std::string& sub);

std::string insert(const std::string& str,
                   long pos,
                   uint32_t chr);

void insertInPlace(std::string& str,
                   long pos,
                   const std::string& sub);

/** @brief Returns true if all characters in @a str are valid UTF-8.
 */
bool isValidUtf8(const std::string& str);

/** @brief Returns a single string that is the concatenation of the strings
 *         in @a parts.
 *
 *  @param parts     the strings that will be joined
 *  @param separator the strings in @a parts will be separated by this.
 */
std::string join(const std::vector<std::string>& parts,
                 const std::string& separator = std::string());

/** @brief Returns the number of code points from @a begin to @a end.
  *
  * @return the number of code points.
  * @throw runtime_error if str contains an invalid UTF-8 code point.
  */
size_t length(const std::string& str);

/** @brief Returns a copy of @a str with all letters lower-cased.
 */
std::string lower(const std::string& str);

/** @brief Returns the number of complete characters in @a str.
 *
 *  This function typically return the same value as does length, but if
 *  @a str contains any combining marks, these are ignored by
 *  numberOfCharacters but included by length.
 */
size_t numberOfCharacters(const std::string& str);

/** @brief Returns a copy of @a str where instances of @a from are replaced
 *      with @a to.
 *
 * @param max The maximum number of replacements that will be performed. All
 *      instances of @a from are replaced if 0.
 */
std::string replace(const std::string& str,
                    const std::string& from,
                    const std::string& to,
                    size_t max = 0,
                    FindFlags::Flags flags = FindFlags::Defaults);

/** @brief Returns a copy of @a str with instances of @a fromChar replaced
 *      with @a toChar.
 *
 *  @param fromChar The character to replace
 *  @param toChar The replacement
 *  @param max The maximum number of replacements that will be performed. All
 *      instances of @a from are replaced if 0.
 */
std::string replace(const std::string& s,
                    uint32_t fromChar,
                    uint32_t toChar,
                    size_t max = 0);

std::string replaceInvalidUtf8(const std::string& str, uint32_t chr);

void replaceInvalidUtf8InPlace(std::string& str, char chr);

std::vector<std::string> split(
        const std::string& str,
        size_t maxSplits = 0,
        SplitFlags::Flags flags = SplitFlags::IgnoreEmpty);

std::vector<std::string> split(
        const std::string& str,
        const std::string& sep,
        size_t maxSplits = 0,
        SplitFlags::Flags flags = SplitFlags::Defaults);

// std::vector<std::string> splitLines(
//         const std::string& str);

std::vector<std::string> splitToken(
        const std::string& str,
        uint32_t sep,
        size_t maxSplits = 0,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::vector<std::string> splitToken(
        const std::string& str,
        const std::string& seps,
        size_t maxSplits = 0,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::vector<std::string> splitWhere(
        const std::string& str,
        const std::function<bool(uint32_t)> predicate,
        size_t maxSplits = 0,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::string, std::string> splitFirst(
        const std::string& str,
        SplitFlags::Flags flags = SplitFlags::MergeTokens);

std::pair<std::string, std::string> splitFirst(
        const std::string& str,
        const std::string& sep,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::string, std::string> splitFirstToken(
        const std::string& str,
        uint32_t sep,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::string, std::string> splitFirstToken(
        const std::string& str,
        const std::string& seps,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::string, std::string> splitFirstWhere(
        const std::string& str,
        const std::function<bool(uint32_t)>& predicate,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::string, std::string> splitLast(
        const std::string& str,
        SplitFlags::Flags flags = SplitFlags::MergeTokens);

std::pair<std::string, std::string> splitLast(
        const std::string& str,
        const std::string& sep,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::string, std::string> splitLastToken(
        const std::string& str,
        uint32_t sep,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::string, std::string> splitLastToken(
        const std::string& str,
        const std::string& seps,
        SplitFlags::Flags flags = SplitFlags::Defaults);

std::pair<std::string, std::string> splitLastWhere(
        const std::string& str,
        const std::function<bool(uint32_t)>& predicate,
        SplitFlags::Flags flags = SplitFlags::Defaults);

bool startsWith(const std::string& str,
                const std::string& cmp,
                FindFlags::Flags flags = FindFlags::Defaults);

std::string substring(const std::string& str,
                      long startIndex,
                      long endIndex = std::numeric_limits<long>::max());

std::string substring(const std::string& str,
                      std::pair<size_t, size_t>& indexes);

/** @brief Returns a copy of @a str with all words capitalized.
 */
std::string title(const std::string& str);

/** @brief Returns a UTF-8 encoded string representing @a chr
 */
std::string toString(uint32_t chr);

/** @brief Returns the UTF-8 encoded string that is equivalent to @a str.
 *
 *  @param str The string to convert from.
 *  @param encoding The encoding of @a str.
 *  @throws runtime_error if str contains any characters that aren't encoded
 *      according to @a encoding, or if @a encoding isn't an 8-bit encoding.
 */
// std::string toUtf8(const std::string& str, Encoding encoding);

/** @brief Returns the UTF-8 encoded string that is equivalent to @a str.
 *
 *  @param str The string to convert from.
 *  @param encoding The encoding of @a str.
 *  @throws runtime_error if str contains any characters that aren't encoded
 *      according to @a encoding, or if @a encoding isn't a 16-bit encoding.
 */
std::string toUtf8(const std::wstring& str, Encoding::Enum encoding);

/** @brief Returns the UTF-8 encoded string that is equivalent to @a str.
 *
 *  @param str The string to convert from.
 *  @param encoding The encoding of @a str.
 *  @throws runtime_error if str contains any characters that aren't encoded
 *      according to @a encoding, or if @a encoding isn't a 32-bit encoding.
 */
// std::string toUtf8(const std::vector<uint32_t>& str, Encoding encoding);

// std::string fromUtf8(const std::string& str, Encoding encoding);

std::string trim(const std::string& str);

std::string trim(const std::string& str,
                 const std::function<bool(uint32_t)>& predicate);

std::string trim(const std::string& str,
                 const std::string& chars);

std::string trimStart(const std::string& str);

std::string trimStart(const std::string& str,
                      const std::function<bool(uint32_t)>& predicate);

std::string trimStart(const std::string& str,
                      const std::string& chars);

std::string trimEnd(const std::string& str);

std::string trimEnd(const std::string& str,
                    const std::function<bool(uint32_t)>& predicate);

std::string trimEnd(const std::string& str,
                    const std::string& chars);

std::string upper(const std::string& str);

// Range findFirstUnescaped(const std::string& str, uint32_t chr);
// Range findFirstUnescaped(Iterator begin, Iterator end, uint32_t chr);

// Range findFirstUnescapedOf(const std::string& str,
//                            const std::string& chars);
// Range findFirstUnescapedOf(Iterator begin, Iterator end,
//                            const std::string& chars);

// Range findFirstUnescapedNotOf(const std::string& str,
//                               const std::string& chars);
// Range findFirstUnescapedNotOf(Iterator begin, Iterator end,
//                               const std::string& chars);

// Range findFirstUnescapedWhere(const std::string& str,
//                               std::function<bool(uint32_t)>& predicate);
// Range findFirstUnescapedWhere(Iterator begin, Iterator end,
//                               std::function<bool(uint32_t)>& predicate);

// Range findFirstUnescapedWhereNot(const std::string& str,
//                                  std::function<bool(uint32_t)>& predicate);
// Range findFirstUnescapedWhereNot(Iterator begin, Iterator end,
//                                  std::function<bool(uint32_t)>& predicate);

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

bool hasWildcards(const std::string& str);
WildcardExpression parseWildcards(const std::string& expr);
bool match(const WildcardExpression& expr, const std::string& str);
Range findShortest(const WildcardExpression& expr, const std::string& str);
Range findLongest(const WildcardExpression& expr, const std::string& str);

}
}

#endif
