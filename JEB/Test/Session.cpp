#include "Session.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "TestSuite.hpp"

namespace JEB { namespace Test {

Session::Session()
    : m_Log(&std::cerr)
{
}

Session::~Session()
{
}

Session& Session::instance()
{
    static Session test;
    return test;
}

void Session::beginSuite(const std::string& name)
{
    TestSuitePtr ts(new TestSuite(name));
    m_TestSuites.push_back(ts);
    print(std::string("Running test suite ") + name + "\n");
}

void Session::endSuite()
{
    if (m_TestSuites.empty())
        throw std::logic_error("Call to endSuite not preceded by a call to beginSuite");
}

void Session::suiteFailed(const Error& error)
{
    if (m_TestSuites.empty())
        throw std::logic_error("Call to suiteFailed not preceded by a call to beginSuite");
    TestSuite& ts = *m_TestSuites.back();
    if (ts.tests().empty())
        print("\n");
    ts.setFailed(true);
    ts.setError(error);
    print(std::string("  ") + error.text() + "\n");
}

void Session::beginTest(const std::string& name)
{
    if (m_TestSuites.empty())
        beginSuite();

    TestPtr t(new Test(name));
    m_TestSuites.back()->addTest(t);
    print(std::string("  Running test ") + name);
}

void Session::endTest()
{
    if (m_TestSuites.empty() ||
        m_TestSuites.back()->tests().empty())
        throw std::logic_error("Call to endTest not preceded by a call to beginTest");
    print("\n");
}

void Session::testFailed(const Error& error)
{
    if (m_TestSuites.empty() ||
        m_TestSuites.back()->tests().empty())
        throw std::logic_error("Call to testFailed not preceded by a call to beginTest");
    print("\n");
    Test& t = *m_TestSuites.back()->tests().back();
    t.setFailed(true);
    t.setError(error);
    m_TestSuites.back()->setFailed(true);
    print(std::string("    ") + error.text() + "\n");
}

size_t Session::numberOfFailedSuites() const
{
    size_t failures = 0;
    for (size_t i = 0; i < m_TestSuites.size(); i++)
        failures += m_TestSuites[i]->failed() ? 1 : 0;
    return failures;
}

const std::vector<TestSuitePtr>& Session::suites() const
{
  return m_TestSuites;
}

void Session::unhandledException(const Error& error)
{
    if (!m_TestSuites.empty())
    {
        if (!m_TestSuites.back()->tests().empty())
            testFailed(error);
        else
            suiteFailed(error);
    }
    else
    {
        beginSuite("<unknown>");
        suiteFailed(error);
    }
}

void Session::print(const std::string& text)
{
    *m_Log << text;
}

void Session::assertPassed()
{
    if (m_TestSuites.back()->tests().empty())
        throw std::logic_error("Call to assertPassed not preceded by a call to beginTest");
    Test& t = *m_TestSuites.back()->tests().back();
    if (t.assertions() == 0)
        print(" .");
    else
        print(".");
    t.incrementAssertions();
}

std::ostream* Session::log()
{
    return m_Log;
}

void Session::setLog(std::ostream* log)
{
    m_Log = log;
}

}}
