/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "Error.hpp"
#include <sstream>

namespace JEB { namespace Test {

Error::Error()
    : m_LineNo(0)
{
}

Error::Error(const std::string& file,
             unsigned lineNo,
             const std::string& message)
    : m_File(file),
      m_LineNo(lineNo),
      m_Message(message)
{
}

const std::string& Error::file() const
{
    return m_File;
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
    ss << m_File << "[" << m_LineNo << "]: " << m_Message;
    return ss.str();
}

void Error::addContext(const std::string& file,
                       unsigned lineNo,
                       const std::string& message)
{
    m_Context.push_back(Error(file, lineNo, message));
}

const std::vector<Error>& Error::context() const
{
    return m_Context;
}

std::ostream& operator<<(std::ostream& os, const Error& e)
{
    return os << e.text();
}

}}
