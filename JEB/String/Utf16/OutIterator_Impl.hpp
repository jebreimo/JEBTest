#include <ostream>
#include "Encode.hpp"

namespace JEB { namespace String { namespace Utf16 {

template <typename OutIt, bool SwapBytes>
OutIterator<OutIt>::OutIterator(OutIt it)
    : m_It(it)
{
}

template <typename OutIt, bool SwapBytes>
OutIterator<OutIt>& OutIterator<OutIt>::operator=(uint32_t codePoint)
{
    add<OutIt, SwapBytes>(m_It, codePoint);
    return *this;
}

template <typename OutIt, bool SwapBytes>
OutIterator<OutIt>& OutIterator<OutIt>::operator++()
{
    return *this;
}

template <typename OutIt, bool SwapBytes>
OutIterator<OutIt>& OutIterator<OutIt>::operator++(int)
{
    return *this;
}

template <typename OutIt, bool SwapBytes>
typename OutIterator<OutIt>::ValueProxy OutIterator<OutIt>::operator*()
{
    return *this;
}

}}}
