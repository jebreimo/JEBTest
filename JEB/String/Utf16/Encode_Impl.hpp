#include <iterator>
#include "JEB/Bits/Union16.hpp"
#include "JEB/Bits/Endian.hpp"

namespace JEB { namespace String { namespace Utf16 {

template <typename OutIt, bool SwapBytes>
OutIt add(OutIt out, uint32_t codePoint)
{
    if (codePoint <= 0xFFFF)
    {
        uint16_t word = (uint16_t)codePoint;
        if (SwapBytes)
            *out = JEB::Endian::swap(word);
        else
            *out = word;
        return ++out;
    }
    else
    {
        codePoint -= 0x10000;
        uint16_t word1 = (uint16_t)(0xD800 | (codePoint >> 10));
        uint16_t word2 = (uint16_t)(0xDC00 | (codePoint & 0x3FF));
        if (SwapBytes)
        {
            *out = Endian::swap(word1);
            *++out = Endian::swap(word2);
        }
        else
        {
            *out = word1;
            *++out = word2;
        }
        return ++out;
    }
}

template <typename OutIt>
OutIt add(OutIt out, uint32_t codePoint)
{
    return add<OutIt, false>(out, codePoint);
}

template <typename OutIt>
OutIt addLE(OutIt out, uint32_t codePoint)
{
    return add<OutIt, Endian::IsBig>(out, codePoint);
}

template <typename OutIt>
OutIt addBE(OutIt out, uint32_t codePoint)
{
    return add<OutIt, Endian::IsLittle>(out, codePoint);
}

template <bool SwapBytes, typename FwdIt, typename ChrType>
bool encode(FwdIt& begin, FwdIt end, uint32_t codePoint, ChrType)
{
    if (codePoint <= 0xFFFF)
    {
        if (std::distance(begin, end) < 1)
            return false;
        Union16 word((uint16_t)codePoint);
        if (SwapBytes)
            word.reverse();
        *begin++ = word.u16;
        return true;
    }
    else
    {
        if (std::distance(begin, end) < 2)
            return false;
        codePoint -= 0x10000;
        Union16 word1((uint16_t)(0xD800 | (codePoint >> 10)));
        Union16 word2((uint16_t)(0xDC00 | (codePoint & 0x3FF)));
        if (SwapBytes)
        {
            word1.reverse();
            word2.reverse();
        }
        *begin++ = word1.u16;
        *begin++ = word2.u16;
        return true;
    }
}

template <bool SwapBytes, typename FwdIt>
bool encode(FwdIt& begin, FwdIt end, uint32_t codePoint, char)
{
    if (codePoint <= 0xFFFF)
    {
        if (std::distance(begin, end) < 2)
            return false;
        Union16 word((uint16_t)codePoint);
        if (SwapBytes)
            word.reverse();
        *begin++ = word.i8[0];
        *begin++ = word.i8[1];
        return true;
    }
    else
    {
        if (std::distance(begin, end) < 4)
            return false;
        codePoint -= 0x10000;
        Union16 word1((uint16_t)(0xD800 | (codePoint >> 10)));
        Union16 word2((uint16_t)(0xDC00 | (codePoint & 0x3FF)));
        if (SwapBytes)
        {
            word1.reverse();
            word2.reverse();
        }
        *begin++ = word1.i8[0];
        *begin++ = word1.i8[1];
        *begin++ = word2.i8[0];
        *begin++ = word2.i8[1];
        return true;
    }
}

template <typename FwdIt>
bool encode(FwdIt& begin, FwdIt end, uint32_t codePoint)
{
    return encode<false>(
            begin, end, codePoint,
            typename std::iterator_traits<FwdIt>::value_type());
}

template <typename FwdIt>
bool encodeLE(FwdIt& begin, FwdIt end, uint32_t codePoint)
{
    return encode<Endian::IsBig>(
            begin, end, codePoint,
            typename std::iterator_traits<FwdIt>::value_type());
}

template <typename FwdIt>
bool encodeBE(FwdIt& begin, FwdIt end, uint32_t codePoint)
{
    return encode<Endian::IsLittle>(
            begin, end, codePoint,
            typename std::iterator_traits<FwdIt>::value_type());
}

}}}
