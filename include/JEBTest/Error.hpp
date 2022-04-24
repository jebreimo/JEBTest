//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <iosfwd>
#include <string>
#include <vector>

namespace JEBTest
{
    class Error
    {
    public:
        enum Type
        {
            None,
            Failure,
            CriticalFailure,
            FatalFailure,
            UnhandledException
        };

        Error();

        Error(std::string  file,
              unsigned lineNo,
              std::string  message,
              Type level = None);

        /** @brief The file where the error occurred.
          */
        const std::string& file() const;

        Type type() const;

        unsigned lineNo() const;

        const std::string& message() const;

        std::string text() const;

        void addContext(const std::string& file,
                        unsigned lineNo,
                        const std::string& message);

        const std::vector<Error>& context() const;

        static const char* levelName(Type level);
    private:
        std::string m_File;
        Type m_Type;
        unsigned m_LineNo;
        std::string m_Message;
        std::vector<Error> m_Context;
    };

    std::ostream& operator<<(std::ostream& os, const Error& e);
}
