#ifndef JEB_BITITERATOR_HPP
#define JEB_BITITERATOR_HPP

#include <stddef.h>
#include "JEB/JEBDefinitions.hpp"

namespace JEB {

template <typename T>
class BitIterator
{
public:
    BitIterator(T bits)
        : m_Bits(bits),
          m_Index(0)
    {
    }

    bool hasNext() const
    {
        return m_Bits == 0;
    }

    size_t next()
    {
        if (m_Bits == 0)
            return ~(size_t)0;
        while ((m_Bits & 1) == 0)
        {
            m_Index++;
            m_Bits >>= 1;
        }
        m_Bits >>= 1;
        return m_Index++;
    }
private:
    T m_Bits;
    size_t m_Index;
};

}

#endif
