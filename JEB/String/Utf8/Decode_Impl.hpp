#include <algorithm>
#include <cassert>

namespace JEB { namespace String { namespace Utf8 {

namespace internal
{

static inline bool isContinuation(uint8_t c)
{
    return (c & 0xC0) == 0x80;
}

static inline int cmpCountPrefix(uint8_t c, size_t count)
{
    assert(count < 8);
    return int((c >> (7 - count)) + 2) - int((1 << (count + 1)));
}

static inline bool isAscii(uint32_t c)
{
    return  (c & 0x80) == 0;
}

}

template <typename FwdIt>
bool isValid(FwdIt begin, FwdIt end, bool acceptIncomleteAtEnd)
{
    unsigned cp;
    int result;
    while ((result = nextCodePoint(cp, begin, end)) == 0)
    {
    }
    return result == DecodeResult::EndOfString ||
           (acceptIncomleteAtEnd && (result & DecodeResult::EndOfString));
}

template <typename FwdIt>
void skipNextCodePoint(FwdIt& it, FwdIt end)
{
    if (it == end)
        return;

    if (internal::isAscii(*it) ||
        internal::isContinuation(*it) || *it == (char)0xFF)
    {
        ++it;
        return;
    }

    uint32_t codePoint = *it & 0x7F;
    unsigned bit = 0x40;
    while (++it != end && internal::isContinuation(*it))
    {
        if ((codePoint & bit) == 0)
            break;
        codePoint ^= bit;
        bit >>= 1;
    }
}

template <typename FwdIt>
int nextCodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    if (it == end)
        return DecodeResult::EndOfString;

    if (internal::isAscii(*it))
    {
        codePoint = (unsigned char)*it++;
        return DecodeResult::Ok;
    }

    if (internal::isContinuation(*it) || *it >= (char)0xFE)
        return DecodeResult::Invalid;

    FwdIt initialIt = it;
    codePoint = *it & 0x7F;
    unsigned bit = 0x40;
    while (++it != end && internal::isContinuation(*it))
    {
        if ((codePoint & bit) == 0)
            break; // Next call to this function deals with this error.
        codePoint ^= bit;
        codePoint <<= 6;
        codePoint |= *it & 0x3F;
        bit <<= 5;
    }

    if ((codePoint & bit) != 0)
    {
        int result = DecodeResult::Incomplete;
        if (it == end)
            result |= DecodeResult::EndOfString;
        it = initialIt;
        return result;
    }

    return DecodeResult::Ok;
}

template <typename BiIt>
int prevCodePoint(uint32_t& codePoint, BiIt& it, BiIt begin)
{
    if (it == begin)
        return DecodeResult::StartOfString;

    BiIt initialIt = it;
    --it;
    if (internal::isAscii(*it))
    {
        codePoint = (unsigned char)*it;
        return DecodeResult::Ok;
    }

    codePoint = 0;
    size_t count = 1;
    while (internal::isContinuation(*it))
    {
        if (++count == 7 || it == begin)
        {
            it = initialIt;
            return DecodeResult::Invalid;
        }
        codePoint |= ((unsigned)(*it & 0x3F)) << (6 * (count - 2));
        --it;
    }
    int cmp = internal::cmpCountPrefix(*it, count);
    if (cmp != 0)
    {
        it = initialIt;
        if (*it == (char)0xFF || cmp < 0)
            return DecodeResult::Invalid;
        else
            return DecodeResult::Incomplete;
    }

    codePoint |= ((unsigned)(*it & ((1 << (7 - count)) - 1)) << (6 * (count - 1)));

    return DecodeResult::Ok;
}

}}}
