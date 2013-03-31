#include <ostream>
#include "JEB/Unicode/UnicodeChars.hpp"
#include "Decode.hpp"

namespace JEB { namespace String { namespace Utf8 {

template <typename BiIt>
BiIterator<BiIt>::BiIterator()
    : m_CharStart(),
      m_CharEnd(),
      m_Begin(),
      m_End(),
      m_Value(Unicode::Invalid)
{
}

template <typename BiIt>
BiIterator<BiIt>::BiIterator(BiIt beg, BiIt end)
    : m_CharStart(beg),
      m_CharEnd(beg),
      m_Begin(beg),
      m_End(end),
      m_Value(Unicode::Invalid)
{
}

template <typename BiIt>
BiIterator<BiIt>::BiIterator(BiIt beg, BiIt end, BiIt pos)
    : m_CharStart(pos),
      m_CharEnd(pos),
      m_Begin(beg),
      m_End(end),
      m_Value(Unicode::Invalid)
{
}

template <typename BiIt>
bool BiIterator<BiIt>::operator==(const BiIterator<BiIt>& rhs) const
{
    return m_CharStart == rhs.m_CharStart;
}

template <typename BiIt>
bool BiIterator<BiIt>::operator!=(const BiIterator<BiIt>& rhs) const
{
    return !(*this == rhs);
}

template <typename BiIt>
BiIterator<BiIt>& BiIterator<BiIt>::operator++()
{
    if (m_CharStart == m_CharEnd)
        endCodePoint();
    m_CharStart = m_CharEnd;
    m_Value = Unicode::Invalid;

    return *this;
}

template <typename BiIt>
BiIterator<BiIt> BiIterator<BiIt>::operator++(int)
{
    BiIterator prev(*this);
    operator++();
    return prev;
}

template <typename BiIt>
BiIterator<BiIt>& BiIterator<BiIt>::operator--()
{
    m_CharEnd = m_CharStart;
    int dr = prevCodePoint(m_Value, m_CharStart, m_Begin);
    if (dr == DecodeResult::StartOfString)
        throw std::runtime_error("Decrement at start of string.");
    else if (dr != DecodeResult::Ok)
        throw std::runtime_error("invalid UTF-8 character");
    return *this;
}

template <typename BiIt>
BiIterator<BiIt> BiIterator<BiIt>::operator--(int)
{
    BiIterator prev(*this);
    operator--();
    return prev;
}

template <typename BiIt>
const uint32_t& BiIterator<BiIt>::operator*() const
{
    if (m_Value == Unicode::Invalid)
        endCodePoint();
    return m_Value;
}

template <typename BiIt>
BiIt BiIterator<BiIt>::beginCodePoint() const
{
    return m_CharStart;
}

template <typename BiIt>
BiIt BiIterator<BiIt>::endCodePoint() const
{
    if (m_CharEnd == m_CharStart)
    {
        int dr = nextCodePoint(m_Value, m_CharEnd, m_End);
        if (dr != DecodeResult::Ok && dr != DecodeResult::EndOfString)
            throw std::runtime_error("invalid UTF-8 character");
    }
    return m_CharEnd;
}

template <typename BiIt>
bool BiIterator<BiIt>::empty() const
{
    return beginCodePoint() == endCodePoint();
}

template <typename BiIt>
std::pair<BiIt, BiIt> BiIterator<BiIt>::range() const
{
    return std::make_pair(beginCodePoint(), endCodePoint());
}

}}}
