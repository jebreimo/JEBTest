/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_TEST_EXCEPTIONS_HPP
#define JEB_TEST_EXCEPTIONS_HPP

#include <exception>
#include <vector>
#include "Error.hpp"

namespace JEB { namespace Test {

class AbstractFailure
{
public:
    virtual ~AbstractFailure();
    const Error& error() const;
    std::string what() const;
    void addContext(const std::string& file,
                    unsigned lineNo,
                    const std::string& message);
protected:
    AbstractFailure(const Error& error);
private:
    Error m_Error;
    std::string m_What;
    std::vector<Error> m_Context;
};

class TestFailure : public AbstractFailure
{
public:
    TestFailure(const std::string& file,
                unsigned lineNo,
                const std::string& message);
    ~TestFailure();
};

class CriticalFailure : public AbstractFailure
{
public:
    CriticalFailure(const std::string& file,
                    unsigned lineNo,
                    const std::string& message);
    ~CriticalFailure();
};

class FatalFailure : public AbstractFailure
{
public:
    FatalFailure(const std::string& file,
                 unsigned lineNo,
                 const std::string& message);
    ~FatalFailure();
};

}}

#endif
