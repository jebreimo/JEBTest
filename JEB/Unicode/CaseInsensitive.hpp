//***************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#ifndef JEB_STRING_UNICODE_CASEINSENSITIVE_HPP
#define JEB_STRING_UNICODE_CASEINSENSITIVE_HPP

#include <cstdint>
#include <functional>
#include <string>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Unicode {

template <typename T>
struct CaseInsensitiveEqual : std::binary_function<T, T, bool>
{
    bool operator()(T a, T b) const;
};

template <typename T>
struct CaseInsensitiveLess : std::binary_function<T, T, bool>
{
    bool operator()(T a, T b) const;
};

template <typename T>
struct CaseInsensitiveCompare : std::binary_function<T, T, bool>
{
    int32_t operator()(T a, T b) const;
};

template <typename InpIt1, typename InpIt2>
bool caseInsensitiveEqual(InpIt1 beg, InpIt1 end,
                          InpIt2 cmpBeg, InpIt2 cmpEnd);

template <typename InpIt1, typename InpIt2>
bool caseInsensitiveLess(InpIt1 beg, InpIt1 end,
                         InpIt2 cmpBeg, InpIt2 cmpEnd);

template <typename InpIt1, typename InpIt2>
int32_t caseInsensitiveCompare(InpIt1 beg, InpIt1 end,
                               InpIt2 cmpBeg, InpIt2 cmpEnd);

}}

#include "CaseInsensitive_Impl.hpp"

#endif
