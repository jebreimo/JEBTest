#include "Exceptions.hpp"

namespace JEB { namespace Test {

AbstractFailure::AbstractFailure(const Error& error)
    : m_Error(error)
{}

AbstractFailure::~AbstractFailure()
{}

const Error& AbstractFailure::error() const
{
    return m_Error;
}

std::string AbstractFailure::what() const
{
    return m_Error.text();
}

void AbstractFailure::addContext(const std::string& file,
                                 unsigned lineNo,
                                 const std::string& message)
{
    m_Error.addContext(file, lineNo, message);
}

TestFailure::TestFailure(const std::string& file,
                         unsigned lineNo,
                         const std::string& message)
    : AbstractFailure(Error(file, lineNo, message))
{}

TestFailure::~TestFailure()
{}

TestSuiteFailure::TestSuiteFailure(const std::string& file,
                                   unsigned lineNo,
                                   const std::string& message)
    : AbstractFailure(Error(file, lineNo, message))
{}

TestSuiteFailure::~TestSuiteFailure()
{}

}}
