#ifndef JEB_TEST_EXCEPTIONS_HPP
#define JEB_TEST_EXCEPTIONS_HPP

#include <exception>
#include "Error.hpp"

namespace JEB { namespace Test {

class AbstractFailure
{
public:
    virtual ~AbstractFailure();
    const Error& error() const;
    std::string what() const;
protected:
    AbstractFailure(const Error& error);
private:
    Error m_Error;
    std::string m_What;
};

class TestFailure : public AbstractFailure
{
public:
    TestFailure(const std::string& file,
                unsigned lineNo,
                const std::string& message);
    ~TestFailure();
};

class TestSuiteFailure : public AbstractFailure
{
public:
    TestSuiteFailure(const std::string& file,
                     unsigned lineNo,
                     const std::string& message);
    ~TestSuiteFailure();
};

}}

#endif
