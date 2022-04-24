//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-16.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Indentation.hpp"

#include <cassert>
#include <ostream>
#include <stdexcept>

using namespace std;

namespace JEBTest
{
    Indentation::Indentation() noexcept
        : m_IndentationString("  ")
    {}

    const std::string& Indentation::indentationString() const
    {
        return m_IndentationString;
    }

    void Indentation::setIndentationString(
            const std::string& indentationString)
    {
        m_IndentationString = indentationString;
    }

    void Indentation::clear()
    {
        m_Indents.clear();
    }

    void Indentation::pushIndent()
    {
        m_Indents.push_back(-1);
    }

    void Indentation::pushAlignment(unsigned pos)
    {
        assert((int)pos >= 0);
        m_Indents.push_back(pos);
    }

    void Indentation::pop()
    {
        if (m_Indents.empty())
            throw runtime_error("Can't pop, stack is empty");
        m_Indents.erase(m_Indents.end() - 1);
    }

    void Indentation::write(ostream& os) const
    {
        for (int m_Indent : m_Indents)
        {
            if (m_Indent == -1)
            {
                os << m_IndentationString;
            }
            else
            {
                for (int i = 0; i < m_Indent; i++)
                    os.put(' ');
            }
        }
    }

    std::ostream& operator<<(std::ostream& os, const Indentation& i)
    {
        i.write(os);
        return os;
    }
}
