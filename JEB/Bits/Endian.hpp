#ifndef JEB_ENDIAN_HPP
#define JEB_ENDIAN_HPP

#include "Union16.hpp"
#include "Union32.hpp"
#include "Union64.hpp"

#define JB_LITTLE_ENDIAN

namespace JEB {

/** @brief Defines functions for handling endianness issues.
 */
namespace Endian
{

#ifdef JB_LITTLE_ENDIAN

static const bool IsBig = false;
static const bool IsLittle = true;

#else

static const bool IsBig = true;
static const bool IsLittle = false;

#endif

enum Enum
{
    Unknown,
    Big,
    Little
};

/** @brief Returns the system's endianness.
 */
inline Enum system()
{
    Union16 u(1);
    return u.u8[0] == 0 ? Big : Little;
}

inline uint8_t swap(uint8_t v)
{
    return v;
}

inline int8_t swap(int8_t v)
{
    return v;
}

inline uint16_t swap(uint16_t v)
{
    Union16 u(v);
    u.reverse();
    return u.u16;
}

inline int16_t swap(int16_t v)
{
    return (int16_t)swap((uint16_t)v);
}

inline uint32_t swap(uint32_t v)
{
    Union32 u(v);
    u.reverse();
    return u.u32;
}

inline int32_t swap(int32_t v)
{
    return (int32_t)swap((uint32_t)v);
}

inline uint64_t swap(uint64_t v)
{
    Union64 u(v);
    u.reverse();
    return u.u64;
}

inline int64_t swap(int64_t v)
{
    return (int64_t)swap((uint64_t)v);
}

}
}

#endif
