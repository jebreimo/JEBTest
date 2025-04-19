//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <ios>

namespace JEBTest
{
    class StreamRedirection
    {
    public:
        StreamRedirection(std::ios& stream, std::ios& replacement);
        StreamRedirection(std::ios& stream, std::streambuf* replacement);
        StreamRedirection(StreamRedirection&& other) noexcept;
        ~StreamRedirection();
    private:
        std::ios& m_Stream;
        std::streambuf* m_OriginalBuffer;
    };
}
