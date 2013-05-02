#include "Test.hpp"
#include <iostream>
#include <stdexcept>

#include "JEB/Sys/Path.hpp"
#include "JEB/String/String.hpp"
#undef JEB

namespace JEB { namespace Test {

Test::Test(const std::string& name)
    : m_Assertions(0),
      m_Failed(false),
      m_Name(name)
{
}

size_t Test::assertions() const
{
    return m_Assertions;
}

void Test::incrementAssertions()
{
    m_Assertions++;
}

void Test::addTest(TestPtr test)
{
    m_Tests.push_back(test);
}

const Error& Test::error() const
{
    return m_Error;
}

void Test::setError(const Error& error)
{
    m_Error = error;
}

bool Test::failed() const
{
    return m_Failed;
}

void Test::setFailed(bool failed)
{
    m_Failed = failed;
}

const std::string& Test::name() const
{
    return m_Name;
}

std::vector<TestPtr>& Test::tests()
{
    return m_Tests;
}

const std::vector<TestPtr>& Test::tests() const
{
    return m_Tests;
}

}}
