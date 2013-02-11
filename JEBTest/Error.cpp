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

std::ostream& operator<<(std::ostream& os, const Error& e)
{
    return os << e.text();
}

}}
