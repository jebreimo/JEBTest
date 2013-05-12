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
    enum Level
    {
        None,
        Failure,
        Critical,
        Fatal
    };

    Error();
    Error(const std::string& file,
          unsigned lineNo,
          const std::string& message,
          Level level = None);

    const std::string& file() const;
    Level level() const;
    unsigned lineNo() const;
    const std::string& message() const;
    std::string text() const;

    void addContext(const std::string& file,
                    unsigned lineNo,
                    const std::string& message);
    const std::vector<Error>& context() const;
private:
    std::string m_File;
    Level m_Level;
    unsigned m_LineNo;
    std::string m_Message;
    std::vector<Error> m_Context;
};

std::ostream& operator<<(std::ostream& os, const Error& e);

}}

#endif
