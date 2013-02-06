#ifndef JEB_ERROR_HPP
#define JEB_ERROR_HPP

#include <iosfwd>
#include <string>

namespace JEB { namespace Unit {

class Error
{
public:
    Error();
    Error(const std::string& file,
          unsigned lineNo,
          const std::string& message);

    const std::string& file() const;
    unsigned lineNo() const;
    const std::string& message() const;
    std::string text() const;
private:
    std::string m_File;
    unsigned m_LineNo;
    std::string m_Message;
};

std::ostream& operator<<(std::ostream& os, const Error& e);

}}

#endif
