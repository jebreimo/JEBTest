#include "Subset.hpp"

#include "JEB/Bits/Bits.hpp"

namespace JEB { namespace Math {

bool isSolvableSet(const Set& set)
{
    unsigned long values = 0;
    for (Set::const_iterator it = set.begin(); it != set.end(); it++)
        values |= *it;
    return set.size() == Bits::countOnes(values);
}

bool findSolvableSubset(Indexes& subset, const Set& set, size_t maxSize)
{

    return false;
}

}}
