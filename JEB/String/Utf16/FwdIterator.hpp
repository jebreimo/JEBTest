#ifndef JEB_ENCODING_UTF16FWDITERATOR_HPP
#define JEB_ENCODING_UTF16FWDITERATOR_HPP

#include <cstdint>
#include <iosfwd>
#include <iterator>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String { namespace Utf16 {

template <typename FwdIt, bool SwapBytes = false>
class FwdIterator
    : public std::iterator<std::forward_iterator_tag, uint32_t, ptrdiff_t, void, const uint32_t&>
{
public:
    FwdIterator();
    FwdIterator(FwdIt beg, FwdIt end);

    bool operator==(const FwdIterator<FwdIt, SwapBytes>& rhs) const;
    bool operator!=(const FwdIterator<FwdIt, SwapBytes>& rhs) const;

    FwdIterator& operator++();
    FwdIterator operator++(int);

    const uint32_t& operator*() const;

    FwdIt beginCodePoint() const;
    FwdIt endCodePoint() const;
private:
    FwdIt m_CharStart;
    mutable FwdIt m_CharEnd;
    FwdIt m_End;
    mutable uint32_t m_Value;
};

template <typename FwdIt>
FwdIterator<FwdIt> begin(FwdIt begin, FwdIt end)
{
    return FwdIterator<FwdIt>(begin, end);
}

template <typename Coll>
FwdIterator<typename Coll::const_iterator> begin(const Coll& coll)
{
    return FwdIterator<typename Coll::const_iterator>(coll.begin(), coll.end());
}

template <typename FwdIt>
FwdIterator<FwdIt> end(FwdIt begin, FwdIt end)
{
    return FwdIterator<FwdIt>(end, end);
}

template <typename Coll>
FwdIterator<typename Coll::const_iterator> end(const Coll& coll)
{
    return end(coll.end(), coll.end());
}

}}}

#include "Utf16FwdIterator_Impl.hpp"

#endif
