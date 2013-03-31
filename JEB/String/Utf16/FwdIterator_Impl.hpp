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
    return m_CharStart == rhs.m_CharStart;
}

template <typename FwdIt, bool SwapBytes>
bool FwdIterator<FwdIt, SwapBytes>::operator!=(const FwdIterator<FwdIt, SwapBytes>& rhs) const
{
    return !(*this == rhs);
}

template <typename FwdIt, bool SwapBytes>
FwdIterator<FwdIt, SwapBytes>& FwdIterator<FwdIt, SwapBytes>::operator++()
{
    if (m_CharStart == m_CharEnd)
        endCodePoint();
    m_CharStart = m_CharEnd;
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
        endCodePoint();
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
        int dr = nextCodePoint<BiIt, SwapBytes>(m_Value, m_CharEnd, m_End);
        if (dr != DecodeResult::Ok && dr != DecodeResult::EndOfString)
            throw std::runtime_error("invalid UTF-16 character");
    }
    return m_CharEnd;
}

}}}
