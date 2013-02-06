#include "Session.hpp"
#include <iostream>
#include <stdexcept>

#include "Test.hpp"

namespace JEB { namespace Unit {

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

}}
