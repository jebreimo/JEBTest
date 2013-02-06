//***************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#include "CaseInsensitive.hpp"

#include "CaseConverter.hpp"

namespace JEB { namespace Unicode {

template <>
bool CaseInsensitiveEqual<char>::operator()(char a, char b) const
{
    return CaseInsensitiveEqual<uint32_t>()(static_cast<unsigned char>(a),
                                            static_cast<unsigned char>(b));
}

template <>
bool CaseInsensitiveEqual<uint32_t>::operator()(uint32_t a, uint32_t b) const
{
    return Unicode::upper(a) == Unicode::upper(b);
}

template <>
bool CaseInsensitiveLess<char>::operator()(char a, char b) const
{
    return CaseInsensitiveLess<uint32_t>()(static_cast<unsigned char>(a),
                                           static_cast<unsigned char>(b));
}

template <>
bool CaseInsensitiveLess<uint32_t>::operator()(uint32_t a, uint32_t b) const
{
    return Unicode::upper(a) < Unicode::upper(b);
}

template <>
int32_t CaseInsensitiveCompare<char>::operator()(char a, char b) const
{
    return CaseInsensitiveCompare<uint32_t>()(static_cast<unsigned char>(a),
                                              static_cast<unsigned char>(b));
}

template <>
int32_t CaseInsensitiveCompare<uint32_t>::operator()(uint32_t a, uint32_t b) const
{
    return static_cast<int32_t>(Unicode::upper(a) - Unicode::upper(b));
}

}}
