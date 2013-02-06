#include <ostream>
#include "Decode.hpp"
#include "JEB/Unicode/UnicodeChars.hpp"

namespace JEB { namespace String { namespace Utf8 {

template <typename FwdIt>
FwdIterator<FwdIt>::FwdIterator()
    : m_CharStart(),
      m_CharEnd(),
      m_End(),
      m_Value(Unicode::Invalid)
{
}

template <typename FwdIt>
FwdIterator<FwdIt>::FwdIterator(FwdIt beg, FwdIt end)
    : m_CharStart(beg),
      m_CharEnd(beg),
      m_End(end),
      m_Value(Unicode::Invalid)
{
}

template <typename FwdIt>
bool FwdIterator<FwdIt>::operator==(const FwdIterator<FwdIt>& rhs) const
{
    return m_CharStart == rhs.m_CharStart;
}

template <typename FwdIt>
bool FwdIterator<FwdIt>::operator!=(const FwdIterator<FwdIt>& rhs) const
{
    return !(*this == rhs);
}

template <typename FwdIt>
FwdIterator<FwdIt>& FwdIterator<FwdIt>::operator++()
{
    m_CharStart = endCodePoint();
    m_Value = Unicode::Invalid;
    return *this;
}

template <typename FwdIt>
FwdIterator<FwdIt> FwdIterator<FwdIt>::operator++(int)
{
    FwdIterator prev(*this);
    operator++();
    return prev;
}

template <typename FwdIt>
const uint32_t& FwdIterator<FwdIt>::operator*() const
{
    if (m_Value == Unicode::Invalid)
        endCodePoint();
    return m_Value;
}

template <typename FwdIt>
FwdIt FwdIterator<FwdIt>::beginCodePoint() const
{
    return m_CharStart;
}

template <typename FwdIt>
FwdIt FwdIterator<FwdIt>::endCodePoint() const
{
    if (m_CharEnd == m_CharStart &&
        !nextCodePoint(m_Value, m_CharEnd, m_End) &&
        m_CharEnd == m_End)
    {
        throw std::runtime_error("invalid UTF-8 character");
    }
    return m_CharEnd;
}

}}}
