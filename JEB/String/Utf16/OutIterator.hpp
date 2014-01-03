#ifndef JEB_STRING_UTF16_OUTITERATOR_HPP
#define JEB_STRING_UTF16_OUTITERATOR_HPP

#include <cstdint>
#include <iosfwd>
#include <iterator>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String { namespace Utf16 {

template <typename OutIt, bool SwapBytes = false>
class OutIterator
    : public std::iterator<std::output_iterator_tag, uint32_t, void, void, void>
{
public:
    OutputIterator(OutIt it);

    OutIterator& operator=(uint32_t codePoint);
    OutIterator& operator++();
    OutIterator& operator++(int);
    OutIterator& operator*();
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
