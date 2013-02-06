#ifndef JEB_ENCODING_UTF16_DECODE_HPP
#define JEB_ENCODING_UTF16_DECODE_HPP

#include <cstdint>
#include <limits>
#include <string>
#include "JEB/Bits/Endian.hpp"

namespace JEB { namespace String { namespace Utf16 {

template <typename Iterator, bool SwapBytes>
bool nextCodePoint(uint32_t& codePoint,
                   Iterator& it,
                   Iterator end);

template <typename Iterator>
bool nextCodePoint(uint32_t& codePoint,
                   Iterator& it,
                   Iterator end);

template <typename Iterator, bool SwapBytes>
bool prevCodePoint(uint32_t& codePoint,
                   Iterator& it,
                   Iterator begin);

template <typename Iterator>
bool prevCodePoint(uint32_t& codePoint,
                   Iterator& it,
                   Iterator begin);

template <typename Iterator>
bool nextCodePointLE(uint32_t& codePoint,
                     Iterator& it,
                     Iterator end)
{
    return nextCodePoint<Iterator, Endian::IsBig>(codePoint, it, end);
}

template <typename Iterator>
bool nextCodePointBE(uint32_t& codePoint,
                     Iterator& it,
                     Iterator end)
{
    return nextCodePoint<Iterator, Endian::IsLittle>(codePoint, it, end);
}

template <typename Iterator>
bool prevCodePointLE(uint32_t& codePoint,
                    Iterator& it,
                    Iterator begin)
{
    return prevCodePoint<Iterator, Endian::IsBig>(codePoint, it, begin);
}

template <typename Iterator>
bool prevCodePointBE(uint32_t& codePoint,
                    Iterator& it,
                    Iterator begin)
{
    return prevCodePoint<Iterator, Endian::IsLittle>(codePoint, it, begin);
}

}}}

#include "Decode_Impl.hpp"

#endif
