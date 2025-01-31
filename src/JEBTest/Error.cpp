//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "JEBTest/Error.hpp"
#include <sstream>
#include <utility>

namespace JEBTest
{
    Error::Error()
        : m_Type(None),
          m_LineNo(0)
    {}

    Error::Error(std::string  file,
                 unsigned lineNo,
                 std::string  message,
                 Type type)
        : m_File(std::move(file)),
          m_Type(type),
          m_LineNo(lineNo),
          m_Message(std::move(message))
    {}

    const std::string& Error::file() const
    {
        return m_File;
    }

    Error::Type Error::type() const
    {
        return m_Type;
    }

    unsigned Error::lineNo() const
    {
        return m_LineNo;
    }

    const std::string& Error::message() const
    {
        return m_Message;
    }

    std::string Error::text() const
    {
        std::ostringstream ss;
        ss << m_File
#ifdef _MSC_VER
           << "(" << m_LineNo << "): ";
#else
           << ":" << m_LineNo << ": ";
#endif

        if (m_Type == CriticalFailure)
            ss << "CRITICAL ";
        else if (m_Type == FatalFailure)
            ss << "FATAL ";
        ss << m_Message;
        return ss.str();
    }

    void Error::addContext(const std::string& file,
                           unsigned lineNo,
                           const std::string& message)
    {
        m_Context.emplace_back(file, lineNo, message);
    }

    const std::vector<Error>& Error::context() const
    {
        return m_Context;
    }

    const char* Error::levelName(Type type)
    {
        switch (type)
        {
        case Failure: return "Failure";
        case CriticalFailure: return "Critical Failure";
        case FatalFailure: return "Fatal Failure";
        case UnhandledException: return "Unhandled Exception";
        default: break;
        }
        return "None";
    }

    std::ostream& operator<<(std::ostream& os, const Error& e)
    {
        return os << e.text();
    }
}
