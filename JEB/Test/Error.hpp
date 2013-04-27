#ifndef JEB_ERROR_HPP
#define JEB_ERROR_HPP

#include <iosfwd>
#include <string>
#include <vector>

namespace JEB { namespace Test {

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

    void addContext(const std::string& file,
                    unsigned lineNo,
                    const std::string& message);
    const std::vector<Error>& context() const;
private:
    std::string m_File;
    unsigned m_LineNo;
    std::string m_Message;
    std::vector<Error> m_Context;
};

std::ostream& operator<<(std::ostream& os, const Error& e);

}}

#endif