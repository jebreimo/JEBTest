#ifndef JEB_ENCODING_UTF16_DECODE_HPP
#define JEB_ENCODING_UTF16_DECODE_HPP

#include <cstdint>
#include <limits>
#include <string>
#include "JEB/Bits/Endian.hpp"
#include "JEB/String/StringFlags.hpp"

namespace JEB { namespace String { namespace Utf16 {

template <typename FwdIt, bool SwapBytes>
int nextCodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end);

template <typename FwdIt>
int nextCodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end);

template <typename BiIt, bool SwapBytes>
int prevCodePoint(uint32_t& codePoint, BiIt& it, BiIt begin);

template <typename BiIt>
int prevCodePoint(uint32_t& codePoint, BiIt& it, BiIt begin);

template <typename FwdIt>
int nextCodePointLE(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextCodePoint<FwdIt, Endian::IsBig>(codePoint, it, end);
}

template <typename FwdIt>
int nextCodePointBE(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextCodePoint<FwdIt, Endian::IsLittle>(codePoint, it, end);
}

template <typename BiIt>
int prevCodePointLE(uint32_t& codePoint, BiIt& it, BiIt begin)
{
    return prevCodePoint<BiIt, Endian::IsBig>(codePoint, it, begin);
}

template <typename BiIt>
int prevCodePointBE(uint32_t& codePoint, BiIt& it, BiIt begin)
{
    return prevCodePoint<BiIt, Endian::IsLittle>(codePoint, it, begin);
}

}}}

#include "Decode_Impl.hpp"

#endif
