#ifndef JEB_SORT_HPP
#define JEB_SORT_HPP

#include <utility>
#include "JEB/JEBDefinitions.hpp"

namespace JEB
{

template <typename T>
void sort(T& a, T& b)
{
    if (b < a)
        std::swap(a, b);
}

template <typename T>
void sort(T& a, T& b, T& c)
{
    sort(a, b);
    sort(b, c);
    sort(a, b);
}

template <typename T>
void sort(T& a, T& b, T& c, T& d)
{
    sort(a, c);
    sort(b, d);
    sort(a, b);
    sort(c, d);
    sort(b, c);
}

template <typename T>
void sort(T (&a)[2])
{
    sort(a[0], a[1]);
}

template <typename T>
void sort(T (&a)[3])
{
    sort(a[0], a[1], a[2]);
}

template <typename T>
void sort(T (&a)[4])
{
    sort(a[0], a[1], a[2], a[3]);
}

}

#endif
