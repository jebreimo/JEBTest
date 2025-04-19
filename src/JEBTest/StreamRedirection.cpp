//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "StreamRedirection.hpp"

namespace JEBTest
{
    StreamRedirection::StreamRedirection(std::ios& stream,
                                         std::ios& replacement)
        : m_Stream(stream),
          m_OriginalBuffer(stream.rdbuf(replacement.rdbuf()))
    {}

    StreamRedirection::StreamRedirection(std::ios& stream,
                                         std::streambuf* replacement)
        : m_Stream(stream),
          m_OriginalBuffer(stream.rdbuf(replacement))
    {}

    StreamRedirection::StreamRedirection(StreamRedirection&& other) noexcept
        : m_Stream(other.m_Stream),
          m_OriginalBuffer(other.m_OriginalBuffer)
    {
        other.m_OriginalBuffer = nullptr;
    }

    StreamRedirection::~StreamRedirection()
    {
        if (m_OriginalBuffer)
            m_Stream.rdbuf(m_OriginalBuffer);
    }
}
