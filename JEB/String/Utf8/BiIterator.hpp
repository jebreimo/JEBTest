#ifndef JEB_STRING_UTF8_BIITERATOR_HPP
#define JEB_STRING_UTF8_BIITERATOR_HPP

#include <cstdint>
#include <iterator>
#include <utility>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String { namespace Utf8 {

template <typename BiIt>
class BiIterator
    : public std::iterator<std::bidirectional_iterator_tag, uint32_t, ptrdiff_t, void, const uint32_t&>
{
public:
    BiIterator();
    BiIterator(BiIt beg, BiIt end);
    BiIterator(BiIt beg, BiIt end, BiIt pos);

    bool operator==(const BiIterator<BiIt>& rhs) const;
    bool operator!=(const BiIterator<BiIt>& rhs) const;

    BiIterator& operator++();
    BiIterator operator++(int);
    BiIterator& operator--();
    BiIterator operator--(int);

    const uint32_t& operator*() const;

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
BiIterator<BiIt> begin(BiIt begin, BiIt end)
{
    return BiIterator<BiIt>(begin, end);
}

template <typename Container>
BiIterator<typename Container::const_iterator> begin(const Container& c)
{
    return begin(c.cbegin(), c.cend());
}

template <typename BiIt>
BiIterator<BiIt> end(BiIt begin, BiIt end)
{
    return BiIterator<BiIt>(begin, end, end);
}

template <typename Container>
BiIterator<typename Container::const_iterator> end(const Container& c)
{
    return end(c.cbegin(), c.cend());
}

template <typename BiIt>
std::reverse_iterator<BiIterator<BiIt>> rbegin(BiIt begin, BiIt end)
{
    return std::reverse_iterator<BiIterator<BiIt>>(Utf8::end(begin, end));
}

template <typename Container>
std::reverse_iterator<BiIterator<typename Container::const_iterator>> rbegin(const Container& c)
{
    return rbegin(c.cbegin(), c.cend());
}

template <typename BiIt>
std::reverse_iterator<BiIterator<BiIt>> rend(BiIt begin, BiIt end)
{
    return std::reverse_iterator<BiIterator<BiIt>>(Utf8::begin(begin, end));
}

template <typename Container>
std::reverse_iterator<BiIterator<typename Container::const_iterator>> rend(const Container& c)
{
    return rend(c.cbegin(), c.cend());
}

}}}

#include "BiIterator_Impl.hpp"

#endif
