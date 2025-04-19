//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
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
        [[nodiscard]] const std::string& file() const;

        [[nodiscard]] Type type() const;

        [[nodiscard]] unsigned lineNo() const;

        [[nodiscard]] const std::string& message() const;

        [[nodiscard]] std::string text() const;

        void addContext(const std::string& file,
                        unsigned lineNo,
                        const std::string& message);

        [[nodiscard]] const std::vector<Error>& context() const;

        [[nodiscard]] static const char* levelName(Type level);
    private:
        std::string m_File;
        Type m_Type;
        unsigned m_LineNo;
        std::string m_Message;
        std::vector<Error> m_Context;
    };

    std::ostream& operator<<(std::ostream& os, const Error& e);
}
