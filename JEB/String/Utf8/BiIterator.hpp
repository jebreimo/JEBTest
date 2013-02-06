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
    return begin(coll.cbegin(), coll.cend());
}

template <typename BiIt>
BiIterator<BiIt> end(BiIt begin, BiIt end)
{
    return BiIterator<BiIt>(begin, end, end);
}

template <typename Coll>
BiIterator<typename Coll::const_iterator> end(const Coll& coll)
{
    return end(coll.cbegin(), coll.cend());
}

template <typename BiIt>
std::reverse_iterator<BiIterator<BiIt>> rbegin(BiIt begin, BiIt end)
{
    return std::reverse_iterator<BiIterator<BiIt>>(Utf8::end(begin, end));
}

template <typename Coll>
std::reverse_iterator<BiIterator<typename Coll::const_iterator>> rbegin(const Coll& coll)
{
    return rbegin(coll.cbegin(), coll.cend());
}

template <typename BiIt>
std::reverse_iterator<BiIterator<BiIt>> rend(BiIt begin, BiIt end)
{
    return std::reverse_iterator<BiIterator<BiIt>>(Utf8::begin(begin, end));
}

template <typename Coll>
std::reverse_iterator<BiIterator<typename Coll::const_iterator>> rend(const Coll& coll)
{
    return rend(coll.cbegin(), coll.cend());
}

}}}

#include "BiIterator_Impl.hpp"

#endif
