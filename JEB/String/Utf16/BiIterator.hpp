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
    mutable BiIt m_CharEnd;
    BiIt m_Begin;
    BiIt m_End;
    mutable uint32_t m_Value;
};

template <typename BiIt>
BiIterator<BiIt> begin(BiIt first, BiIt last)
{
    return BiIterator<BiIt>(first, last);
}

template <typename Container>
BiIterator<typename Container::const_iterator> begin(const Container& c)
{
    return begin(c.begin(), c.end());
}

template <typename BiIt>
BiIterator<BiIt> end(BiIt first, BiIt last)
{
    return BiIterator<BiIt>(first, last, last);
}

template <typename Container>
BiIterator<typename Container::const_iterator> end(const Container& c)
{
    return end(c.begin(), c.end());
}

}}}

#include "BiIterator_Impl.hpp"

#endif
