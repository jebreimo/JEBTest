#include "JEB/Bits/Union16.hpp"

namespace JEB { namespace String { namespace Utf16 {

namespace internal
{

template <typename Iterator, bool SwapBytes>
bool nextWord(uint16_t& word,
              Iterator& it,
              Iterator end,
              wchar_t)
{
    if (it == end)
        return false;

    word = *it++;
    if (SwapBytes)
        Endian::swap(word);

    return true;
}

template <typename Iterator, bool SwapBytes>
bool prevWord(uint16_t& word,
              Iterator& it,
              Iterator begin,
              wchar_t)
{
    if (it == begin)
        return false;

    word = *(--it);
    if (SwapBytes)
        Endian::swap(word);

    return true;
}

template <typename Iterator, bool SwapBytes>
bool nextWord(uint16_t& word,
              Iterator& it,
              Iterator end,
              char)
{
    if (it == end)
        return false;

    Union16 chr;
    chr.u8[SwapBytes ? 1 : 0] = *it++;

    if (it == end)
        return false;

    chr.u8[SwapBytes ? 0 : 1] = *it++;

    word = chr.u16;
    return true;
}

template <typename Iterator, bool SwapBytes>
bool prevWord(uint16_t& word,
              Iterator& it,
              Iterator begin,
              char)
{
    if (it == begin)
        return false;

    Union16 chr;
    chr.u8[SwapBytes ? 0 : 1] = *(--it);

    if (it == begin)
        return false;

    chr.u8[SwapBytes ? 1 : 0] = *(--it);

    word = chr.u16;
    return true;
}

}

template <typename Iterator, bool SwapBytes>
bool nextCodePoint(uint32_t& codePoint,
                   Iterator& it,
                   Iterator end)
{
    uint16_t chr;
    if (!internal::nextWord<Iterator, SwapBytes>(chr, it, end, typename std::iterator_traits<Iterator>::value_type()))
        return false;

    if (chr < 0xD800 || 0xE000 <= chr)
    {
        codePoint = chr;
        return true;
    }
    else if (0xDC00 <= chr)
    {
        codePoint = chr;
        return false;
    }

    codePoint = (chr & 0x3FF) << 10;

    if (!internal::nextWord<Iterator, SwapBytes>(chr, it, end, typename std::iterator_traits<Iterator>::value_type()))
        return false;

    if (chr < 0xDC00 || 0xE000 <= chr)
    {
        codePoint |= chr;
        return false;
    }

    codePoint |= chr & 0x3FF;
    codePoint += 0x10000;

    return true;
}

template <typename Iterator>
bool nextCodePoint(uint32_t& codePoint,
                   Iterator& it,
                   Iterator end)
{
    return nextCodePoint<Iterator, false>(codePoint, it, end);
}

template <typename Iterator, bool SwapBytes>
bool prevCodePoint(uint32_t& codePoint,
                   Iterator& it,
                   Iterator begin)
{
    uint16_t chr;
    if (!internal::prevWord<Iterator, SwapBytes>(chr, it, begin, typename std::iterator_traits<Iterator>::value_type()))
        return false;

    if (chr < 0xD800 || 0xE000 <= chr)
    {
        codePoint = chr;
        return true;
    }
    else if (chr < 0xDC00)
    {
        codePoint = chr;
        return false;
    }

    codePoint = chr & 0x3FF;

    if (!internal::prevWord<Iterator, SwapBytes>(chr, it, begin, typename std::iterator_traits<Iterator>::value_type()))
        return false;

    if (chr < 0xD800 || 0xDC00 <= chr)
    {
        codePoint |= chr << 10;
        return false;
    }

    codePoint |= (chr & 0x3FF) << 10;
    codePoint += 0x10000;

    return true;
}

template <typename Iterator>
bool prevCodePoint(uint32_t& codePoint,
                   Iterator& it,
                   Iterator end)
{
    return prevCodePoint<Iterator, false>(codePoint, it, end);
}

}}}
