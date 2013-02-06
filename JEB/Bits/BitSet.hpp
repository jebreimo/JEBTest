#ifndef JEB_BITSET_HPP
#define JEB_BITSET_HPP

#include <cstddef>
#include <vector>
#include "JEB/JEBDefinitions.hpp"

namespace JEB {

class BitSet
{
public:
    typedef unsigned long Word;
    static const size_t NotFound;

    BitSet();
    explicit BitSet(size_t size);
    size_t size() const;
    void setSize(size_t size);
    bool bit(size_t index);
    void setBit(size_t index, bool bit);
    size_t findFirst(bool value, size_t fromIndex = 0);
private:
    static size_t containerSize(size_t size);
    size_t first(bool value, size_t major);
    size_t first(bool value, size_t major, size_t minorMin, size_t minorMax);

    static const size_t BitsPerWord;

    std::vector<Word> m_Bits;
    size_t m_Size;
};

}

#endif
