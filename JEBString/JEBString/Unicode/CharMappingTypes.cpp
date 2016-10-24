#include "CharMappingTypes.hpp"

#include <cassert>

namespace JEBString { namespace Unicode {

bool CompactCharMapping::get(uint32_t chr, uint32_t& mappedChr) const
{
    assert(chr - segment < 32);
    auto mask = 1 << (chr - segment);
    if (mask & affected)
    {
        mappedChr =  chr + offset;
        return true;
    }
    else if (mask & ignorable)
    {
        mappedChr = chr;
        return true;
    }
    return false;
}

}}
