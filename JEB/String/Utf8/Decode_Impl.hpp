#include <algorithm>

namespace JEB { namespace String { namespace Utf8 {

namespace internal
{

static inline bool isContinuation(uint8_t c)
{
    return (c & 0xC0) == 0x80;
}

static inline bool hasCountPrefix(uint8_t c, size_t count)
{
    return ((c >> (7 - count)) + 2 == (1 << (count + 1)));
}

static inline bool isAscii(uint32_t c)
{
    return  (c & 0x80) == 0;
}

}

template <typename FwdIt>
bool isValid(FwdIt begin, FwdIt end)
{
    unsigned cp;
    while (nextCodePoint(cp, begin, end))
    {
    }

    return begin == end;
}

template <typename Iterator>
void skipNextCodePoint(Iterator& it, Iterator end)
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

template <typename Iterator>
bool nextCodePoint(uint32_t& codePoint,
                   Iterator& it,
                   Iterator end)
{
    Iterator initialIt = it;

    if (it == end)
        return false;

    if (internal::isAscii(*it))
    {
        codePoint = (unsigned char)*it++;
        return true;
    }

    if (internal::isContinuation(*it) || *it == (char)0xFF)
    {
        return false;
    }

    codePoint = *it & 0x7F;
    unsigned bit = 0x40;
    while (++it != end && internal::isContinuation(*it))
    {
        if ((codePoint & bit) == 0)
            break; // Next call will deal with this error.
        codePoint ^= bit;
        codePoint <<= 6;
        codePoint |= *it & 0x3F;
        bit <<= 5;
    }

    if ((codePoint & bit) != 0)
    {
        it = initialIt;
        return false;
    }

    return true;
}

template <typename Iterator>
bool prevCodePoint(uint32_t& codePoint,
                   Iterator& it,
                   Iterator begin)
{
    if (it == begin)
        return false;

    Iterator initialIt = it;
    --it;
    if (internal::isAscii(*it))
    {
        codePoint = (unsigned char)*it;
        return true;
    }

    codePoint = *it & 0x3F;

    size_t count = 1;
    while (--it != begin && internal::isContinuation(*it))
    {
        codePoint |= ((unsigned)(*it & 0x3F)) << (6 * count);
        count++;
    }
    count++;
    if (count >= 8 || !internal::hasCountPrefix(*it, count))
    {
        it = initialIt;
        return false; // TODO: Make prevCodePoint stop in the same places nextCodePoint does.
    }

    codePoint |= ((unsigned)(*it & ((1 << (7 - count)) - 1)) << (6 * (count - 1)));

    return true;
}

}}}
