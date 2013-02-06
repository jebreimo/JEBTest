#ifndef JEB_UNION16_HPP
#define JEB_UNION16_HPP

#include <algorithm>
#include <cstdint>
#include "JEB/JEBDefinitions.hpp"

namespace JEB
{

union Union16
{
    Union16() : u16(0) {}
    explicit Union16(uint16_t n) : u16(n) {}

    template <typename T>
    explicit Union16(const T (&n)[2]);

    void reverse();

    uint16_t u16;
    uint8_t u8[2];
};

template <typename T>
Union16::Union16(const T (&n)[2])
{
    u8[0] = static_cast<uint8_t>(n[0]);
    u8[1] = static_cast<uint8_t>(n[1]);
}

inline void Union16::reverse()
{
    std::swap(u8[0], u8[1]);
}

}

#endif
