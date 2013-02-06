#ifndef JEB_MATH_BINOMIAL_HPP
#define JEB_MATH_BINOMIAL_HPP

#include <algorithm>
#include <cassert>
#include "Fraction.hpp"

namespace JEB { namespace Math {

namespace
{
    template <typename T>
    bool validBinomialArgs(T n, T k)
    {
        return n >= k && n > 0 && k >= 0;
    }

    template <>
    inline bool validBinomialArgs<unsigned>(unsigned n, unsigned k)
    {
        return n >= k && n > 0;
    }

    template <>
    inline bool validBinomialArgs<unsigned long>(unsigned long n,
                                                 unsigned long k)
    {
        return n >= k && n > 0;
    }
}

template <typename T>
T binomial(T n, T k)
{
    if (!validBinomialArgs(n, k))
        return 0;
    T iMax = std::min(k, n - k);
    Fraction<T> f(1);
    for (T i = 0; i < iMax; i++)
        f *= Fraction<T>(n - i, iMax - i);
    assert(f.denominator() == 1);
    return f.numerator();
}

}}

#endif
