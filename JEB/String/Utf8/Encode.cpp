//****************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-14 by Jan Erik Breimo
//****************************************************************************
#include "Encode.hpp"

using namespace std;

namespace JEB { namespace String { namespace Utf8 {

size_t encode(char* buffer, uint32_t c, size_t bufferSize)
{
    size_t length = encodedLength(c);
    if (length > bufferSize)
    {
        return 0;
    }
    else if (length == 1)
    {
        buffer[0] = (char)c;
        return 1;
    }

    for (size_t i = length; i-- > 1;)
    {
        buffer[i] = (char)(0x80 | (c & 0x3F));
        c >>= 6;
    }
    buffer[0] = (char)((0xFF << (8 - length)) | c);
    return length;
}

size_t encode(char (&buffer)[MAX_ENCODED_LENGTH], uint32_t chr)
{
    return encode(buffer, chr, MAX_ENCODED_LENGTH);
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
