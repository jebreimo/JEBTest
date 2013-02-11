#include "TestSuite.hpp"

namespace JEB { namespace Test {

TestSuite::TestSuite(const std::string& name)
    : m_Failed(false),
      m_Name(name)
{
}

const Error& TestSuite::error() const
{
    return m_Error;
}

void TestSuite::setError(const Error& error)
{
    m_Error = error;
}

bool TestSuite::failed() const
{
    return m_Failed;
}

void TestSuite::setFailed(bool failed)
{
    m_Failed = failed;
}

const std::string& TestSuite::name() const
{
    return m_Name;
}

void TestSuite::addTest(TestPtr test)
{
    m_Tests.push_back(test);
}

std::vector<TestPtr>& TestSuite::tests()
{
    return m_Tests;
}

const std::vector<TestPtr>& TestSuite::tests() const
{
    return m_Tests;
}

}}
