#ifndef JEB_STRING_UTF8_OUTITERATOR_HPP
#define JEB_STRING_UTF8_OUTITERATOR_HPP

#include <cstdint>
#include <iosfwd>
#include <iterator>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String { namespace Utf8 {

template <typename OutIt>
class OutIterator
    : public std::iterator<std::output_iterator_tag, uint32_t, void, void, void>
{
public:
    OutIterator(OutIt it);

    OutIterator& operator=(uint32_t codePoint);
    OutIterator& operator++();
    OutIterator& operator++(int);
    OutIterator& operator*();

    OutIt innerIterator() const;
private:
    OutIt m_It;
};

template <typename Container>
OutIterator<std::back_insert_iterator<Container>> backInserter(Container& c)
{
    return OutIterator<std::back_insert_iterator<Container>>(std::back_inserter(c));
}

}}}

#include "OutIterator_Impl.hpp"

#endif
