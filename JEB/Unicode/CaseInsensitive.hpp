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

template <typename FwdIt>
bool caseInsensitiveEqual(FwdIt beg, FwdIt end, FwdIt cmpBeg, FwdIt cmpEnd);

template <typename FwdIt>
bool caseInsensitiveLess(FwdIt beg, FwdIt end, FwdIt cmpBeg, FwdIt cmpEnd);

template <typename FwdIt>
int32_t caseInsensitiveCompare(FwdIt beg, FwdIt end, FwdIt cmpBeg, FwdIt cmpEnd);

}}

#include "CaseInsensitive_Impl.hpp"

#endif
