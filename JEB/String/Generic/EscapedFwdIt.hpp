#ifndef JEB_STRING_GENERIC_ESCAPEDFWDIT_HPP
#define JEB_STRING_GENERIC_ESCAPEDFWDIT_HPP

#include "EscapedString.hpp"

namespace JEB { namespace String { namespace Generic {

template <typename FwdIt>
class EscapedFwdIt
{
public:
    EscapedFwdIt();
    EscapedFwdIt(FwdIt beg, FwdIt end);

    bool operator==(const EscapedFwdIt& rhs) const;
    bool operator!=(const EscapedFwdIt& rhs) const;

    EscapedFwdIt& operator++();
    EscapedFwdIt operator++(int);

    const std::pair<uint32_t, bool>& operator*() const;

    FwdIt beginSequence() const;
    FwdIt endSequence() const;
private:
    FwdIt m_SeqStart;
    mutable FwdIt m_SeqEnd;
    FwdIt m_End;
    mutable std::pair<uint32_t, bool> m_Value;
};

template <typename FwdIt>
EscapedFwdIt<FwdIt>::EscapedFwdIt()
    : m_SeqStart(),
      m_SeqEnd(),
      m_End(),
      m_Value(Unicode::Invalid, false)
{}

template <typename FwdIt>
EscapedFwdIt<FwdIt>::EscapedFwdIt(FwdIt beg, FwdIt end)
    : m_SeqStart(beg),
      m_SeqEnd(beg),
      m_End(end),
      m_Value(Unicode::Invalid, false)
{}

template <typename FwdIt>
bool EscapedFwdIt<FwdIt>::operator==(const EscapedFwdIt& rhs) const
{
    return m_SeqStart == rhs.m_SeqStart;
}

template <typename FwdIt>
bool EscapedFwdIt<FwdIt>::operator!=(const EscapedFwdIt& rhs) const
{
    return !(*this == rhs);
}

template <typename FwdIt>
EscapedFwdIt<FwdIt>& EscapedFwdIt<FwdIt>::operator++()
{
    m_SeqStart = endSequence();
    m_Value = std::make_pair(Unicode::Invalid, false);
}

template <typename FwdIt>
EscapedFwdIt<FwdIt> EscapedFwdIt<FwdIt>::operator++(int)
{
    EscapedFwdIt<FwdIt> prev(*this);
    operator++();
    return prev;
}

template <typename FwdIt>
const std::pair<uint32_t, bool>& EscapedFwdIt<FwdIt>::operator*() const
{
    return m_Value;
}

template <typename FwdIt>
FwdIt EscapedFwdIt<FwdIt>::beginSequence() const
{
    return m_SeqStart;
}

template <typename FwdIt>
FwdIt EscapedFwdIt<FwdIt>::endSequence() const
{
    if (m_SeqEnd == m_SeqStart)
        nextCodePoint(m_Value, m_SeqEnd, m_End);
    return m_SeqEnd;
}

}}}

#endif
