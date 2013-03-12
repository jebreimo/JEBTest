#ifndef JEB_STRING_UTF8_OUTITERATOR_HPP
#define JEB_STRING_UTF8_OUTITERATOR_HPP

#include <cstdint>
#include <iosfwd>
#include <iterator>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String { namespace Utf8 {

template <typename OutIt>
class OutIterator
    : public std::iterator<std::output_iterator_tag, void, void, void, void>
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

template <typename Coll>
OutIterator<std::back_insert_iterator<Coll>> backInserter(Coll& collection)
{
    return OutIterator<std::back_insert_iterator<Coll>>(std::back_inserter(collection));
}

}}}

#include "OutIterator_Impl.hpp"

#endif
