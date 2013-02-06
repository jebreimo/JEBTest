//***************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#include "CaseInsensitive.hpp"

#include <JEB/Algorithms/Algorithms.hpp>
#include "CaseConverter.hpp"

namespace JEB { namespace Unicode {

template <typename T>
bool CaseInsensitiveEqual<T>::operator()(T a, T b) const
{
    return CaseInsensitiveEqual<uint32_t>()(static_cast<uint32_t>(a),
                                            static_cast<uint32_t>(b));
}

template <>
bool CaseInsensitiveEqual<char>::operator()(char a, char b) const;

template <>
bool CaseInsensitiveEqual<uint32_t>::operator()(uint32_t a, uint32_t b) const;

template <typename T>
bool CaseInsensitiveLess<T>::operator()(T a, T b) const
{
    return CaseInsensitiveLess<uint32_t>()(static_cast<uint32_t>(a),
                                           static_cast<uint32_t>(b));
}

template <>
bool CaseInsensitiveLess<char>::operator()(char a, char b) const;

template <>
bool CaseInsensitiveLess<uint32_t>::operator()(uint32_t a, uint32_t b) const;

template <typename T>
int32_t CaseInsensitiveCompare<T>::operator()(T a, T b) const
{
    return CaseInsensitiveCompare<uint32_t>()(static_cast<uint32_t>(a),
                                              static_cast<uint32_t>(b));
}

template <>
int32_t CaseInsensitiveCompare<char>::operator()(char a, char b) const;

template <>
int32_t CaseInsensitiveCompare<uint32_t>::operator()(uint32_t a, uint32_t b) const;

template <typename FwdIt>
bool caseInsensitiveEqual(FwdIt beg, FwdIt end, FwdIt cmpBeg, FwdIt cmpEnd)
{
    return JEB::Algorithms::equal(beg, end, cmpBeg, cmpEnd,
                                  CaseInsensitiveEqual<uint32_t>());
}

template <typename FwdIt>
bool caseInsensitiveLess(FwdIt beg, FwdIt end, FwdIt cmpBeg, FwdIt cmpEnd)
{
    return caseInsensitiveCompare(beg, end, cmpBeg, cmpEnd) < 0;
}

template <typename It, typename BinaryFunc>
int32_t findFirstNonZero(It beg, It end,
                         It cmpBeg, It cmpEnd,
                         BinaryFunc compare)
{
    while (beg != end && cmpBeg != cmpEnd)
    {
        int32_t value = compare(*beg, *cmpBeg);
        if (value != 0)
            return value;
        beg++;
        cmpBeg++;
    }
    if (beg != end)
        return static_cast<int32_t>(*beg);
    else if (cmpBeg != cmpEnd)
        return -static_cast<int32_t>(*cmpBeg);
    else
        return 0;
}

template <typename FwdIt>
int32_t caseInsensitiveCompare(FwdIt beg, FwdIt end, FwdIt cmpBeg, FwdIt cmpEnd)
{
    return findFirstNonZero(beg, end, cmpBeg, cmpEnd,
                            Unicode::CaseInsensitiveCompare<uint32_t>());
}

}}
