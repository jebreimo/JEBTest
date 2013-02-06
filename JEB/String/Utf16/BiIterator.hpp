#ifndef JEB_STRING_UTF16_BIITERATOR_HPP
#define JEB_STRING_UTF16_BIITERATOR_HPP

#include <cstdint>
#include <iosfwd>
#include <iterator>
#include <utility>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String { namespace Utf16 {

template <typename BiIt, bool SwapBytes = false>
class BiIterator
    : public std::iterator<std::bidirectional_iterator_tag, uint32_t, ptrdiff_t, void, const uint32_t&>
{
public:
    BiIterator();
    BiIterator(BiIt beg, BiIt end);
    BiIterator(BiIt beg, BiIt end, BiIt pos);

    bool operator==(const BiIterator<BiIt, SwapBytes>& rhs) const;
    bool operator!=(const BiIterator<BiIt, SwapBytes>& rhs) const;

    BiIterator& operator++();
    BiIterator operator++(int);
    BiIterator& operator--();
    BiIterator operator--(int);

    uint32_t operator*() const;

    BiIt beginCodePoint() const;
    BiIt endCodePoint() const;
    bool empty() const;
    std::pair<BiIt, BiIt> range() const;
private:
    BiIt m_CharStart;
    BiIt m_Begin;
    BiIt m_End;
    mutable BiIt m_CharEnd;
    mutable uint32_t m_Value;
};

template <typename BiIt>
BiIterator<BiIt> begin(BiIt begin, BiIt end)
{
    return BiIterator<BiIt>(begin, end);
}

template <typename Coll>
BiIterator<typename Coll::const_iterator> begin(const Coll& coll)
{
    return BiIterator<typename Coll::const_iterator>(coll.begin(), coll.end());
}

template <typename BiIt>
BiIterator<BiIt> end(BiIt begin, BiIt end)
{
    return BiIterator<BiIt>(end, end);
}

template <typename Coll>
BiIterator<typename Coll::const_iterator> end(const Coll& coll)
{
    return end(coll.end(), coll.end());
}

}}}

#include "BiIterator_Impl.hpp"

#endif
