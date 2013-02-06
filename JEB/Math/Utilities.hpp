#ifndef JEB_MATH_UTILTIES_HPP
#define JEB_MATH_UTILTIES_HPP

#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Math {

template <typename T>
T sign(T value)
{
    if (value > 0)
        return T(1);
    else if (value < 0)
        return T(-1);
    else
        return T(0);
}

}}

#endif
