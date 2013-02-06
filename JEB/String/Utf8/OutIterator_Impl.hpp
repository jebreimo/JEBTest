#include <ostream>
#include "Encode.hpp"

namespace JEB { namespace String { namespace Utf8 {

template <typename OutIt>
OutIterator<OutIt>::OutIterator(OutIt it)
    : m_It(it)
{
}

template <typename OutIt>
OutIterator<OutIt>& OutIterator<OutIt>::operator=(uint32_t codePoint)
{
    add(m_It, codePoint);
    return *this;
}

template <typename OutIt>
OutIterator<OutIt>& OutIterator<OutIt>::operator++()
{
    return *this;
}

template <typename OutIt>
OutIterator<OutIt>& OutIterator<OutIt>::operator++(int)
{
    return *this;
}

template <typename OutIt>
OutIterator<OutIt>& OutIterator<OutIt>::operator*()
{
    return *this;
}

}}}
