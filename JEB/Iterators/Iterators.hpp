#ifndef JEB_ITERATORS_HPP
#define JEB_ITERATORS_HPP

#include <cassert>
#include <iterator>
#include <stdexcept>
#include <utility>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Iterators {

namespace Throwing {

template <typename FwdIt>
FwdIt next(FwdIt begin, FwdIt end, size_t n, std::forward_iterator_tag)
{
    for (; n != 0; n--)
    {
        if (begin == end)
            throw std::range_error("advance beyond end of range");
        ++begin;
    }
    return begin;
}

template <typename RndIt>
RndIt next(RndIt begin, RndIt end, size_t n, std::random_access_iterator_tag)
{
    auto len = std::distance(begin, end);
    assert(len >= 0);
    if ((size_t)len < n)
        throw std::range_error("advance beyond start of range");
    return begin + n;
}

template <typename It>
It next(It begin, It end, size_t n)
{
    return next(begin, end, n,
                typename std::iterator_traits<It>::iterator_category());
}

template <typename FwdIt>
FwdIt prev(FwdIt begin, FwdIt end, size_t n, std::forward_iterator_tag)
{
    FwdIt it = begin;
    for (; n != 0; n--)
    {
        if (begin == end)
            throw std::range_error("retreat beyond start of range");
        ++begin;
    }
    for (; begin != end; ++begin)
        ++it;
    return it;
}

template <typename BiIt>
BiIt prev(BiIt begin, BiIt end, size_t n, std::bidirectional_iterator_tag)
{
    for (; n != 0; n--)
    {
        if (begin == end)
            throw std::range_error("retreat beyond start of range");
        --end;
    }
    return end;
}

template <typename RndIt>
RndIt prev(RndIt begin, RndIt end, size_t n, std::random_access_iterator_tag)
{
    auto len = std::distance(begin, end);
    assert(len >= 0);
    if ((size_t)len < n)
        throw std::range_error("retreat beyond start of range");
    return begin + (len - n);
}

template <typename It>
It prev(It begin, It end, size_t n)
{
    return prev(begin, end, n,
                typename std::iterator_traits<It>::iterator_category());
}

template <typename It>
It nth(It begin, It end, long steps)
{
    if (steps >= 0)
        return next(begin, end, steps);
    else
        return prev(begin, end, -steps);
}

}

namespace NonThrowing {

template <typename FwdIt>
FwdIt next(FwdIt begin, FwdIt end, size_t n, std::forward_iterator_tag)
{
    for (; n != 0; n--)
    {
        if (begin == end)
            return end;
        ++begin;
    }
    return begin;
}

template <typename RndIt>
RndIt next(RndIt begin, RndIt end, size_t n, std::random_access_iterator_tag)
{
    auto len = std::distance(begin, end);
    assert(len >= 0);
    if ((size_t)len < n)
        return end;
    return begin + n;
}

template <typename It>
It next(It begin, It end, size_t n)
{
    return next(begin, end, n,
                typename std::iterator_traits<It>::iterator_category());
}

template <typename FwdIt>
FwdIt prev(FwdIt begin, FwdIt end, size_t n, std::forward_iterator_tag)
{
    FwdIt it = begin;
    for (; n != 0; n--)
    {
        if (begin == end)
            return begin;
        ++begin;
    }
    for (; begin != end; ++begin)
        ++it;
    return it;
}

template <typename BiIt>
BiIt prev(BiIt begin, BiIt end, size_t n, std::bidirectional_iterator_tag)
{
    for (; n != 0; n--)
    {
        if (begin == end)
            return begin;
        --end;
    }
    return end;
}

template <typename RndIt>
RndIt prev(RndIt begin, RndIt end, size_t n, std::random_access_iterator_tag)
{
    auto len = std::distance(begin, end);
    assert(len >= 0);
    if ((size_t)len < n)
        return begin;
    return begin + (len - n);
}

template <typename It>
It prev(It begin, It end, size_t n)
{
    return prev(begin, end, n,
                typename std::iterator_traits<It>::iterator_category());
}

template <typename It>
It nth(It begin, It end, long steps)
{
    if (steps >= 0)
        return next(begin, end, steps);
    else
        return prev(begin, end, -steps);
}

}

using namespace NonThrowing;

}}

#endif
