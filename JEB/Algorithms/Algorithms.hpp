#ifndef JEB_ALGORITHMS_HPP
#define JEB_ALGORITHMS_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>
#include "JEB/JEBDefinitions.hpp"

/** @file
  * @brief Defines various generic algorithms.
  */

namespace JEB
{
/** @brief The namespace for generic algorithms.
  */
namespace Algorithms
{

template <typename FwdIt, typename Comparable>
bool minMax(FwdIt beg, FwdIt end, Comparable& min, Comparable& max)
{
    if (beg == end)
        return false;
    min = max = *beg;
    while (++beg != end)
    {
        if (*beg < min)
            min = *beg;
        else if (max < *beg)
            max = *beg;
    }
    return true;
}

template <typename InpIt, typename UnaryFunc, typename Result>
Result max(InpIt begin, InpIt end, UnaryFunc func, Result defaultValue)
{
    Result maxValue = defaultValue;
    while (begin != end)
    {
        Result value = func(*begin);
        if (value > maxValue)
            maxValue = value;
        begin++;
    }
    return maxValue;
}

/** @brief Returns the max value returned by items' "size_t size()".
  */
template <typename FwdIt>
size_t maxSize(FwdIt begin, FwdIt end)
{
    size_t size = 0;
    while (begin != end)
    {
        if (begin->size() > size)
            size = begin->size();
        begin++;
    }
    return size;
}

template <typename T>
void swapArrays(T* a, T* b, size_t n)
{
    for (size_t i = 0; i < n; i++)
        std::swap(a[i], b[i]);
}

template <typename T, size_t N>
void swapArrays(T (&a)[N], T (&b)[N])
{
    swapArrays(a, b, N);
}

template <typename InpIt1, typename InpIt2>
std::pair<InpIt1, InpIt2> mismatch(InpIt1 beg, InpIt1 end,
                                   InpIt2 cmpBeg, InpIt2 cmpEnd)
{
    while (beg != end && cmpBeg != cmpEnd && *beg == *cmpBeg)
    {
        beg++;
        cmpBeg++;
    }
    return std::make_pair(beg, cmpBeg);
}

template <typename InpIt1, typename InpIt2, typename BinaryPredicate>
std::pair<InpIt1, InpIt2> mismatch(InpIt1 beg, InpIt1 end,
                                   InpIt2 cmpBeg, InpIt2 cmpEnd,
                                   BinaryPredicate pred)
{
    while (beg != end && cmpBeg != cmpEnd && pred(*beg, *cmpBeg))
    {
        beg++;
        cmpBeg++;
    }
    return std::make_pair(beg, cmpBeg);
}

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt1> search(FwdIt1 beg, FwdIt1 end,
                                 FwdIt2 cmpBeg, FwdIt2 cmpEnd)
{
    if (cmpBeg == cmpEnd)
        return std::make_pair(end, end);
    while (beg != end)
    {
        std::pair<FwdIt1, FwdIt2> its = mismatch(beg, end, cmpBeg, cmpEnd);
        if (its.second == cmpEnd)
            return std::make_pair(beg, its.first);
        else if (its.first == end)
            break;
        beg++;
    }
    return std::make_pair(end, end);
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
std::pair<FwdIt1, FwdIt1> search(FwdIt1 beg, FwdIt1 end,
                                 FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                 BinaryPredicate pred)
{
    if (cmpBeg == cmpEnd)
        return std::make_pair(end, end);
    while (beg != end)
    {
        std::pair<FwdIt1, FwdIt2> its = mismatch(beg, end, cmpBeg, cmpEnd, pred);
        if (its.second == cmpEnd)
            return std::make_pair(beg, its.first);
        else if (its.first == end)
            break;
        beg++;
    }
    return std::make_pair(end, end);
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
std::pair<FwdIt1, FwdIt1> search_last_impl(FwdIt1 beg, FwdIt1 end,
                                           FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                           BinaryPredicate pred,
                                           const std::forward_iterator_tag&)
{
    std::pair<FwdIt1, FwdIt1> result(end, end);
    if (cmpBeg == cmpEnd)
        return result;
    while (beg != end)
    {
        std::pair<FwdIt1, FwdIt2> its = mismatch(beg, end, cmpBeg, cmpEnd, pred);
        if (its.second == cmpEnd)
            result = std::make_pair(beg, its.first);
        else if (its.first == end)
            break;
        beg++;
    }
    return result;
}

template <typename BiIt, typename FwdIt, typename BinaryPredicate>
std::pair<BiIt, BiIt> search_last_impl(BiIt beg, BiIt end,
                                       FwdIt cmpBeg, FwdIt cmpEnd,
                                       BinaryPredicate pred,
                                       const std::bidirectional_iterator_tag&)
{
    if (cmpBeg == cmpEnd)
        return std::make_pair(end, end);
    BiIt it = end;
    while (it-- != beg)
    {
        std::pair<BiIt, FwdIt> its = mismatch(it, end, cmpBeg, cmpEnd, pred);
        if (its.second == cmpEnd)
            return std::make_pair(it, its.first);
        else if (its.first == end)
            break;
    }
    return std::make_pair(end, end);
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
std::pair<FwdIt1, FwdIt1> search_last(FwdIt1 beg, FwdIt1 end,
                                      FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                      BinaryPredicate pred)
{
    return search_last_impl(
            beg, end,
            cmpBeg, cmpEnd,
            pred,
            typename std::iterator_traits<FwdIt1>::iterator_category());
}

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt1> search_last(FwdIt1 beg, FwdIt1 end,
                                      FwdIt2 cmpBeg, FwdIt2 cmpEnd)
{
    return search_last(
            beg, end,
            cmpBeg, cmpEnd,
            std::equal_to<typename std::iterator_traits<FwdIt1>::value_type>());
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
std::pair<FwdIt1, FwdIt1> search_nth_last(FwdIt1 beg, FwdIt1 end,
                                          FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                          size_t count,
                                          BinaryPredicate pred)
{
    std::pair<FwdIt1, FwdIt1> its = std::make_pair(end, end);
    for (size_t i = 0; i < count; i++)
    {
        its = search_last(beg, its.first, cmpBeg, cmpEnd, pred);
        if (its.first == its.second)
        {
            its = std::make_pair(end, end);
            break;
        }
    }
    return its;
}

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt1> search_nth_last(FwdIt1 beg, FwdIt1 end,
                                          FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                          size_t count)
{
    return search_nth_last(
            beg, end,
            cmpBeg, cmpEnd,
            count,
            std::equal_to<typename std::iterator_traits<FwdIt1>::value_type>());
}

template <typename FwdIt, typename UnaryFunc>
FwdIt find_last_if_impl(FwdIt beg, FwdIt end,
                        UnaryFunc predicate,
                        const std::forward_iterator_tag&)
{
    FwdIt it = end;
    while (beg != end)
    {
        if (predicate(*beg))
            it = beg;
        ++beg;
    }
    return it;
}

template <typename BiIt, typename UnaryFunc>
BiIt find_last_if_impl(BiIt beg, BiIt end,
                       UnaryFunc predicate,
                       const std::bidirectional_iterator_tag&)
{
    BiIt it = end;
    while (beg != it)
    {
        --it;
        if (predicate(*it))
            return it;
    }
    return end;
}

template <typename FwdIt, typename UnaryFunc>
FwdIt find_last_if(FwdIt beg, FwdIt end, UnaryFunc predicate)
{
    return find_last_if_impl(
            beg, end,
            predicate,
            typename std::iterator_traits<FwdIt>::iterator_category());
}

template <typename FwdIt1, typename FwdIt2>
bool equal(FwdIt1 beg, FwdIt1 end,
           FwdIt2 cmpBeg, FwdIt2 cmpEnd)
{
    std::pair<FwdIt1, FwdIt2> its = mismatch(beg, end, cmpBeg, cmpEnd);
    return its.first == end && its.second == cmpEnd;
}

template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
bool equal(FwdIt1 beg, FwdIt1 end,
           FwdIt2 cmpBeg, FwdIt2 cmpEnd,
           BinaryPredicate pred)
{
    std::pair<FwdIt1, FwdIt2> its = mismatch(beg, end, cmpBeg, cmpEnd, pred);
    return its.first == end && its.second == cmpEnd;
}

template <typename RndIt, typename T, typename UnaryFunc>
RndIt lower_bound(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    while (beg != end)
    {
        RndIt mid = beg + std::distance(beg, end) / 2;
        if (keyFunc(*mid) < value)
            beg = mid + 1;
        else
            end = mid;
    }
    return beg;
}

template <typename RndIt, typename T, typename UnaryFunc>
RndIt upper_bound(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    while (beg != end)
    {
        RndIt mid = beg + std::distance(beg, end) / 2;
        if (value < keyFunc(*mid))
            end = mid;
        else
            beg = mid + 1;
    }
    return beg;
}

template <typename RndIt, typename T, typename UnaryFunc>
std::pair<RndIt, RndIt> bounds(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    RndIt first = ::JEB::Algorithms::lower_bound(beg, end, value, keyFunc);
    RndIt second = ::JEB::Algorithms::upper_bound(first, end, value, keyFunc);
    return std::make_pair(first, second);
}

template <typename UnaryFunc>
class KeyComparer
{
public:
  KeyComparer(UnaryFunc keyFunc) : m_KeyFunc(keyFunc) {}
  template <typename T>
  bool operator()(T a, T b) {return m_KeyFunc(a) < m_KeyFunc(b);}
private:
  UnaryFunc m_KeyFunc;
};

template <typename RndIt, typename UnaryFunc>
void sort_by_key(RndIt beg, RndIt end, UnaryFunc keyFunc)
{
  std::sort(beg, end, KeyComparer<UnaryFunc>(keyFunc));
}

}}

#endif
