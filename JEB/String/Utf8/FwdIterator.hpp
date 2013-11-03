#ifndef JEB_ENCODING_UTF8ITERATOR_HPP
#define JEB_ENCODING_UTF8ITERATOR_HPP

#include <cstdint>
#include <iterator>
#include <limits>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String { namespace Utf8 {

template <typename FwdIt>
class FwdIterator
    : public std::iterator<std::forward_iterator_tag, uint32_t, ptrdiff_t, void, const uint32_t&>
{
public:
    FwdIterator();
    FwdIterator(FwdIt beg, FwdIt end);

    bool operator==(const FwdIterator<FwdIt>& rhs) const;
    bool operator!=(const FwdIterator<FwdIt>& rhs) const;

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
FwdIterator<FwdIt> beginFwd(FwdIt begin, FwdIt end)
{
    return FwdIterator<FwdIt>(begin, end);
}

template <typename Coll>
FwdIterator<typename Coll::const_iterator> beginFwd(const Coll& coll)
{
    return beginFwd(coll.cbegin(), coll.cend());
}

template <typename FwdIt>
FwdIterator<FwdIt> endFwd(FwdIt begin, FwdIt end)
{
    return FwdIterator<FwdIt>(end, end);
}

template <typename Coll>
FwdIterator<typename Coll::const_iterator> endFwd(const Coll& coll)
{
    return endFwd(coll.cend(), coll.cend());
}

}}}

#include "FwdIterator_Impl.hpp"

#endif
