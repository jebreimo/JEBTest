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

}}}
