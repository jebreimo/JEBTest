#include "JEB/Bits/Union16.hpp"

#ifdef __APPLE__
    #define JEB_WCHAR_SIZE 4
    typedef uint32_t JEB_wchar_alias;
#elif WIN32
    #define JEB_WCHAR_SIZE 2
    typedef uint16_t JEB_wchar_alias;
#endif

namespace JEB { namespace String { namespace Utf16 {

namespace internal
{

template <typename FwdIt, bool SwapBytes>
int nextWord(uint16_t& word, FwdIt& it, FwdIt end, uint32_t)
{
    if (it == end)
        return DecodeResult::EndOfString;
    else if (*it > 0xFFFFu)
        return DecodeResult::Invalid;

    word = *it++;
    if (SwapBytes)
        Endian::swap(word);

    return DecodeResult::Ok;
}

template <typename BiIt, bool SwapBytes>
int prevWord(uint16_t& word, BiIt& it, BiIt begin, uint32_t)
{
    if (it == begin)
        return DecodeResult::StartOfString;
    else if (*it > 0xFFFFu)
        return DecodeResult::Invalid;

    word = *(--it);
    if (SwapBytes)
        Endian::swap(word);

    return DecodeResult::Ok;
}

template <typename FwdIt, bool SwapBytes>
int nextWord(uint16_t& word, FwdIt& it, FwdIt end, uint16_t)
{
    if (it == end)
        return DecodeResult::EndOfString;

    word = *it++;
    if (SwapBytes)
        Endian::swap(word);

    return DecodeResult::Ok;
}

template <typename BiIt, bool SwapBytes>
int prevWord(uint16_t& word, BiIt& it, BiIt begin, uint16_t)
{
    if (it == begin)
        return DecodeResult::StartOfString;

    word = *(--it);
    if (SwapBytes)
        Endian::swap(word);

    return DecodeResult::Ok;
}

template <typename FwdIt, bool SwapBytes>
int nextWord(uint16_t& word, FwdIt& it, FwdIt end, char)
{
    if (it == end)
        return DecodeResult::EndOfString;

    FwdIt initialIt = it;
    Union16 chr;
    chr.u8[SwapBytes ? 1 : 0] = *it++;

    if (it == end)
    {
        it = initialIt;
        return DecodeResult::Incomplete | DecodeResult::EndOfString;
    }

    chr.u8[SwapBytes ? 0 : 1] = *it++;

    word = chr.u16;
    return DecodeResult::Ok;
}

template <typename BiIt, bool SwapBytes>
int prevWord(uint16_t& word, BiIt& it, BiIt begin, char)
{
    if (it == begin)
        return DecodeResult::StartOfString;

    BiIt initialIt = it;
    Union16 chr;
    chr.u8[SwapBytes ? 0 : 1] = *(--it);

    if (it == begin)
    {
        it = initialIt;
        return DecodeResult::Incomplete | DecodeResult::StartOfString;
    }

    chr.u8[SwapBytes ? 1 : 0] = *(--it);

    word = chr.u16;
    return DecodeResult::Ok;
}

template <typename FwdIt, bool SwapBytes>
int nextWord(uint16_t& word, FwdIt& it, FwdIt end, wchar_t)
{
    return nextWord<FwdIt, SwapBytes>(word, it, end, JEB_wchar_alias());
}

template <typename BiIt, bool SwapBytes>
int prevWord(uint16_t& word, BiIt& it, BiIt begin, wchar_t)
{
    return prevWord<BiIt, SwapBytes>(word, it, begin, JEB_wchar_alias());
}
}

template <typename FwdIt, bool SwapBytes>
int nextCodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    uint16_t chr;
    int nwResult = internal::nextWord<FwdIt, SwapBytes>(
            chr, it, end,
            typename std::iterator_traits<FwdIt>::value_type());
    if (nwResult != DecodeResult::Ok)
        return nwResult;

    if (chr < 0xD800 || 0xE000 <= chr)
    {
        codePoint = chr;
        return DecodeResult::Ok;
    }
    else if (0xDC00 <= chr)
    {
        codePoint = chr;
        return DecodeResult::Invalid;
    }

    codePoint = (chr & 0x3FF) << 10;

    nwResult = internal::nextWord<FwdIt, SwapBytes>(
            chr, it, end,
            typename std::iterator_traits<FwdIt>::value_type());
    if (nwResult == DecodeResult::EndOfString)
        return DecodeResult::EndOfString | DecodeResult::Incomplete;
    else if (nwResult != DecodeResult::Ok)
        return nwResult;

    if (chr < 0xDC00 || 0xE000 <= chr)
    {
        codePoint |= chr;
        return DecodeResult::Invalid;
    }

    codePoint |= chr & 0x3FF;
    codePoint += 0x10000;

    return DecodeResult::Ok;
}

template <typename FwdIt>
int nextCodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextCodePoint<FwdIt, false>(codePoint, it, end);
}

template <typename BiIt, int SwapBytes>
int prevCodePoint(uint32_t& codePoint, BiIt& it, BiIt begin)
{
    uint16_t chr;
    int pwResult = internal::prevWord<BiIt, SwapBytes>(
            chr, it, begin,
            typename std::iterator_traits<BiIt>::value_type());
    if (pwResult != DecodeResult::Ok)
        return pwResult;

    if (chr < 0xD800 || 0xE000 <= chr)
    {
        codePoint = chr;
        return DecodeResult::Ok;
    }
    else if (chr < 0xDC00)
    {
        codePoint = chr;
        return DecodeResult::Invalid;
    }

    codePoint = chr & 0x3FF;

    pwResult = internal::prevWord<BiIt, SwapBytes>(
            chr, it, begin,
            typename std::iterator_traits<BiIt>::value_type());
    if (pwResult == DecodeResult::StartOfString)
        return DecodeResult::StartOfString | DecodeResult::Incomplete;
    else if (pwResult != DecodeResult::Ok)
        return pwResult;

    if (chr < 0xD800 || 0xDC00 <= chr)
    {
        codePoint |= chr << 10;
        return DecodeResult::Invalid;
    }

    codePoint |= (chr & 0x3FF) << 10;
    codePoint += 0x10000;

    return DecodeResult::Ok;
}

template <typename BiIt>
int prevCodePoint(uint32_t& codePoint, BiIt& it, BiIt end)
{
    return prevCodePoint<BiIt, false>(codePoint, it, end);
}

}}}
