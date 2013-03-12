//****************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-14 by Jan Erik Breimo
//****************************************************************************
#include "Encode.hpp"

using namespace std;

namespace JEB { namespace String { namespace Utf8 {

size_t encode(char (&buffer)[MAX_ENCODED_LENGTH], uint32_t chr)
{
    char* begin = buffer;
    char* end = buffer + MAX_ENCODED_LENGTH;
    encode(begin, end, chr);
    return (size_t)(begin - buffer);
}

size_t encodedLength(uint32_t c)
{
    if (!(c >> 7))
        return 1;
    else if (!(c >> 11))
        return 2;
    else if (!(c >> 16))
        return 3;
    else if (!(c >> 21))
        return 4;
    else if (!(c >> 26))
        return 5;
    else if (!(c >> 31))
        return 6;
    else
        return 7;
}

}}}
