#include <ostream>
#include "Decode.hpp"

namespace JEB { namespace String { namespace Utf16 {

template <typename FwdIt, bool SwapBytes>
FwdIterator<FwdIt, SwapBytes>::FwdIterator()
    : m_CharStart(),
      m_CharEnd(),
      m_End(),
      m_Value(Unicode::Invalid)
{
}

template <typename FwdIt, bool SwapBytes>
FwdIterator<FwdIt, SwapBytes>::FwdIterator(FwdIt beg, FwdIt end)
    : m_CharStart(beg),
      m_CharEnd(beg),
      m_End(end),
      m_Value(Unicode::Invalid)
{
}

template <typename FwdIt, bool SwapBytes>
bool FwdIterator<FwdIt, SwapBytes>::operator==(const FwdIterator<FwdIt, SwapBytes>& rhs) const
{
    if (m_CharStart == rhs.m_CharStart)
        return true;
    else
        return m_CharStart == m_End && rhs.m_CharStart == rhs.m_End;
}

template <typename FwdIt, bool SwapBytes>
bool FwdIterator<FwdIt, SwapBytes>::operator!=(const FwdIterator<FwdIt, SwapBytes>& rhs) const
{
    return !(*this == rhs);
}

template <typename FwdIt, bool SwapBytes>
FwdIterator<FwdIt, SwapBytes>& FwdIterator<FwdIt, SwapBytes>::operator++()
{
    m_CharStart = endOfCharacter();
    m_Value = Unicode::Invalid;
    return *this;
}

template <typename FwdIt, bool SwapBytes>
FwdIterator<FwdIt, SwapBytes> FwdIterator<FwdIt, SwapBytes>::operator++(int)
{
    FwdIterator prev(*this);
    operator++();
    return prev;
}

template <typename FwdIt, bool SwapBytes>
uint32_t FwdIterator<FwdIt, SwapBytes>::operator*() const
{
    if (m_Value == Unicode::Invalid)
        endOfCharacter();
    return m_Value;
}

template <typename FwdIt, bool SwapBytes>
FwdIt FwdIterator<FwdIt, SwapBytes>::beginCodePoint() const
{
    return m_CharStart;
}

template <typename FwdIt, bool SwapBytes>
FwdIt FwdIterator<FwdIt, SwapBytes>::endCodePoint() const
{
    if (m_CharEnd == m_CharStart)
    {
        uint32_t cp;
        nextCodePoint(cp, m_CharEnd, m_End);
    }
    return m_CharEnd;
}

}}}
