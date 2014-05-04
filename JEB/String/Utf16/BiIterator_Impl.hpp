#include <ostream>
#include "JEB/Unicode/UnicodeChars.hpp"
#include "Decode.hpp"

namespace JEB { namespace String { namespace Utf16 {

template <typename BiIt, bool SwapBytes>
BiIterator<BiIt, SwapBytes>::BiIterator()
    : m_CharStart(),
      m_CharEnd(),
      m_Begin(),
      m_End(),
      m_Value(Unicode::Invalid)
{
}

template <typename BiIt, bool SwapBytes>
BiIterator<BiIt, SwapBytes>::BiIterator(BiIt beg, BiIt end)
    : m_CharStart(beg),
      m_CharEnd(beg),
      m_Begin(beg),
      m_End(end),
      m_Value(Unicode::Invalid)
{
}

template <typename BiIt, bool SwapBytes>
BiIterator<BiIt, SwapBytes>::BiIterator(BiIt beg, BiIt end, BiIt pos)
    : m_CharStart(pos),
      m_CharEnd(pos),
      m_Begin(beg),
      m_End(end),
      m_Value(Unicode::Invalid)
{
}

template <typename BiIt, bool SwapBytes>
bool BiIterator<BiIt, SwapBytes>::operator==(const BiIterator<BiIt, SwapBytes>& rhs) const
{
    return m_CharStart == rhs.m_CharStart;
}

template <typename BiIt, bool SwapBytes>
bool BiIterator<BiIt, SwapBytes>::operator!=(const BiIterator<BiIt, SwapBytes>& rhs) const
{
    return !(*this == rhs);
}

template <typename BiIt, bool SwapBytes>
BiIterator<BiIt, SwapBytes>& BiIterator<BiIt, SwapBytes>::operator++()
{
    if (m_CharStart == m_CharEnd)
        endCodePoint();
    m_CharStart = m_CharEnd;
    m_Value = Unicode::Invalid;
    return *this;
}

template <typename BiIt, bool SwapBytes>
BiIterator<BiIt, SwapBytes> BiIterator<BiIt, SwapBytes>::operator++(int)
{
    BiIterator prev(*this);
    operator++();
    return prev;
}

template <typename BiIt, bool SwapBytes>
BiIterator<BiIt, SwapBytes>& BiIterator<BiIt, SwapBytes>::operator--()
{
    m_CharEnd = m_CharStart;
    if (prevCodePoint<BiIt, SwapBytes>(m_Value, m_CharStart, m_Begin) != DecodeResult::Ok)
    {
        throw std::runtime_error("invalid UTF-16 character at position" +
                    std::to_string(std::distance(m_Begin, m_CharEnd)));
    }
    return *this;
}

template <typename BiIt, bool SwapBytes>
BiIterator<BiIt, SwapBytes> BiIterator<BiIt, SwapBytes>::operator--(int)
{
    BiIterator prev(*this);
    operator--();
    return prev;
}

template <typename BiIt, bool SwapBytes>
uint32_t BiIterator<BiIt, SwapBytes>::operator*() const
{
    if (m_Value == Unicode::Invalid)
        endCodePoint();
    return m_Value;
}

template <typename BiIt, bool SwapBytes>
BiIt BiIterator<BiIt, SwapBytes>::beginCodePoint() const
{
    return m_CharStart;
}

template <typename BiIt, bool SwapBytes>
BiIt BiIterator<BiIt, SwapBytes>::endCodePoint() const
{
    if (m_CharEnd == m_CharStart)
    {
        int dr = nextCodePoint<BiIt, SwapBytes>(m_Value, m_CharEnd, m_End);
        if (dr != DecodeResult::Ok && dr != DecodeResult::EndOfString)
            throw std::runtime_error("invalid UTF-16 character at position" +
                        std::to_string(std::distance(m_Begin, m_CharEnd)));
    }
    return m_CharEnd;
}

template <typename BiIt, bool SwapBytes>
bool BiIterator<BiIt, SwapBytes>::empty() const
{
    return beginCodePoint() == endCodePoint();
}

template <typename BiIt, bool SwapBytes>
std::pair<BiIt, BiIt> BiIterator<BiIt, SwapBytes>::range() const
{
    return std::make_pair(beginCodePoint(), endCodePoint());
}

}}}
