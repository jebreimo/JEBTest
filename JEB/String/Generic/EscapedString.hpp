#ifndef JEB_ESCAPEDSTRING_HPP
#define JEB_ESCAPEDSTRING_HPP

#include <cstdint>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String { namespace Generic {

// TODO: function that produce escaped string

template <typename StrInpIt>
uint32_t fromHex(StrInpIt& beg, StrInpIt end, size_t length)
{
    uint32_t ch = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (beg == end)
            throw std::invalid_argument("Hexadecimal sequence is too short.");
        uint32_t tmp = *beg++;
        ch *= 16;
        if ('0' <= tmp && tmp <= '9')
            ch += tmp - '0';
        else if ('A' <= tmp && tmp <= 'F')
            ch += tmp - 'A' + 10;
        else if ('a' <= tmp && tmp <= 'f')
            ch += tmp - 'a' + 10;
        else
            throw std::invalid_argument("Hexadecimal sequence is too short.");
    }
    return ch;
}

template <typename FwdIt>
std::pair<uint32_t, bool> unescapeNext(FwdIt& beg, FwdIt end)
{
    if (beg == end)
        return std::pair<uint32_t, bool>(~(uint32_t)0, false);
    uint32_t ch = *beg++;
    if (ch != '\\')
        return std::pair<uint32_t, bool>(ch, false);
    if (beg == end)
        throw std::invalid_argument("Invalid escaped character.");

    ch = *beg++;
    switch (ch)
    {
    case '0': ch = '\0'; break;
    case 'a': ch = '\a'; break;
    case 'b': ch = '\b'; break;
    case 'f': ch = '\f'; break;
    case 'n': ch = '\n'; break;
    case 'r': ch = '\r'; break;
    case 't': ch = '\t'; break;
    case 'v': ch = '\v'; break;
    case 'u': ch = fromHex(beg, end, 4); break;
    case 'x': ch = fromHex(beg, end, 2); break;
    default: break;
    }

    return std::pair<uint32_t, bool>(ch, true);
}

template <typename FwdIt>
bool unescapeNext(std::pair<uint32_t, bool>& value, FwdIt& beg, FwdIt end)
{
    if (beg == end)
        return false;
    value.first = *beg++;
    if (value.first != '\\')
    {
        value.second = false;
        return true;
    }
    if (beg == end)
        throw std::invalid_argument("Invalid escaped character.");

    value.first = *beg++;
    value.second = true;
    switch (value.first)
    {
    case '0': value.first = '\0'; break;
    case 'a': value.first = '\a'; break;
    case 'b': value.first = '\b'; break;
    case 'f': value.first = '\f'; break;
    case 'n': value.first = '\n'; break;
    case 'r': value.first = '\r'; break;
    case 't': value.first = '\t'; break;
    case 'v': value.first = '\v'; break;
    case 'u': value.first = fromHex(beg, end, 4); break;
    case 'x': value.first = fromHex(beg, end, 2); break;
    default: break;
    }

    return true;
}

// template <typename FwdIt>
// class EscapedStringIterator
// {
// public:
//     EscapedStringIterator() {}
//     EscapedStringIterator(FwdIt begin, FwdIt end) : m_Begin(begin), m_End(end) {}
//     void reset(FwdIt begin, FwdIt end) {m_Begin = begin; m_End = end;}
//     bool hasNext() const {return m_Begin != m_End;}
//     std::pair<uint32_t, bool> next() {return unescapeNext(m_Begin, m_End);}
//     FwdIt remainder() const {return m_Begin;}
//     FwdIt end() const {return m_End;}
// private:
//     FwdIt m_Begin;
//     FwdIt m_End;
// };

template <typename StrFwdIt>
StrFwdIt findFirstUnescaped(StrFwdIt beg, StrFwdIt end, uint32_t c)
{
    bool escaped = false;
    for (; beg != end; beg++)
    {
        if (escaped)
            escaped = false;
        else if (*beg == '\\')
            escaped = true;
        else if (*beg == c)
            break;
    }
    return beg;
}

template <typename StrFwdIt1, typename StrFwdIt2>
StrFwdIt1 findFirstUnescapedOf(StrFwdIt1 beg, StrFwdIt1 end,
                               StrFwdIt2 searchBeg, StrFwdIt2 searchEnd)
{
    bool escaped = false;
    for (; beg != end; beg++)
    {
        if (escaped)
            escaped = false;
        else if (*beg == '\\')
            escaped = true;
        else if (std::find(searchBeg, searchEnd, *beg) != searchEnd)
            break;
    }
    return beg;
}

template <typename StrFwdIt1, typename StrFwdIt2>
StrFwdIt1 findFirstUnescapedNotOf(StrFwdIt1 beg, StrFwdIt1 end,
                                  StrFwdIt2 searchBeg, StrFwdIt2 searchEnd)
{
    bool escaped = false;
    for (; beg != end; beg++)
    {
        if (escaped)
            escaped = false;
        else if (*beg == '\\')
            escaped = true;
        else if (std::find(searchBeg, searchEnd, *beg) == searchEnd)
            break;
    }
    return beg;
}

template <typename StrFwdIt>
StrFwdIt findFirstUnescapedWhere(StrFwdIt beg, StrFwdIt end,
                                 std::function<bool(uint32_t)>& predicate)
{
    bool escaped = false;
    for (; beg != end; beg++)
    {
        if (escaped)
            escaped = false;
        else if (*beg == '\\')
            escaped = true;
        else if (predicate(*beg))
            break;
    }
    return beg;
}

template <typename StrFwdIt>
StrFwdIt findFirstUnescapedWhereNot(StrFwdIt beg, StrFwdIt end,
                                    std::function<bool(uint32_t)>& predicate)
{
    bool escaped = false;
    for (; beg != end; beg++)
    {
        if (escaped)
            escaped = false;
        else if (*beg == '\\')
            escaped = true;
        else if (!predicate(*beg))
            break;
    }
    return beg;
}

}}}

#endif
