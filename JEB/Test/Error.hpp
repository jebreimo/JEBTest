/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_ERROR_HPP
#define JEB_ERROR_HPP

#include <iosfwd>
#include <string>
#include <vector>

namespace JEB { namespace Test {

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
    Error(const std::string& file,
          unsigned lineNo,
          const std::string& message,
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

}}

#endif
