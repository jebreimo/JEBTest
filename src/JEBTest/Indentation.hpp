//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-16.
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
    class Indentation
    {
    public:
        Indentation() noexcept;

        const std::string& indentationString() const;
        void setIndentationString(const std::string& str);

        void clear();
        void pushIndent();
        void pushAlignment(unsigned pos);
        void pop();

        void write(std::ostream& os) const;
    private:
        std::string m_IndentationString;
        std::vector<int> m_Indents;
    };

    std::ostream& operator<<(std::ostream& os, const Indentation& i);
}
