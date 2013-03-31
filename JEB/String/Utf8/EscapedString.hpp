#ifndef JEB_STRING_UTF8_ESCAPEDSTRING_HPP
#define JEB_STRING_UTF8_ESCAPEDSTRING_HPP

#include <stdexcept>
#include "JEB/Unicode/UnicodeChars.hpp"
#include "Decode.hpp"

namespace JEB { namespace String { namespace Utf8 {

template <typename StrInpIt>
uint32_t fromHex(StrInpIt& beg, StrInpIt end, size_t length)
{
    uint32_t ch = 0;
    for (size_t i = 0; i < length; i++)
    {
        uint32_t tmp;
        if (nextCodePoint(tmp, beg, end) != DecodeResult::Ok)
            throw std::invalid_argument("Hexadecimal sequence is too short.");
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
std::pair<uint32_t, bool> unescapeNext(FwdIt& beg, FwdIt end, uint32_t escapeChar)
{
    uint32_t ch = Unicode::Invalid;
    bool escaped = nextCodePoint(ch, beg, end) == DecodeResult::Ok &&
                   ch == escapeChar &&
                   nextCodePoint(ch, beg, end) == DecodeResult::Ok;
    return std::make_pair(ch, escaped);
}

template <typename FwdIt>
std::pair<uint32_t, bool> unescapeNext(FwdIt& beg, FwdIt end)
{
    std::pair<uint32_t, bool> value = unescapeNext(beg, end, '\\');
    if (!value.second)
        return value;

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

    return value;
}

}}}

#endif
