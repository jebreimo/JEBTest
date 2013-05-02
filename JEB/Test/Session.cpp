/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "Session.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "Test.hpp"

#include "JEB/String/String.hpp"
#undef JEB

namespace JEB { namespace Test {

Session::Session()
    : m_AllTestsEnabled(true),
      m_Log(&std::cerr)
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

// void Session::beginSuite(const std::string& name)
// {
//     TestSuitePtr ts(new TestSuite(name));
//     if (m_ActiveTest.empty())
//     {
//         m_TestSuites.push_back(ts);
//         m_ActiveTest.push_back(ts);
//     }
//     else
//     {
//         TestSuitePtr parent = std::dynamic_pointer_cast<TestSuite>(m_ActiveTest.back());
//         if (!parent)
//             throw std::logic_error("Call to beginSuite when endTest was expected");
//         parent->addTest(ts);
//     }
//     print(std::string("Running test suite ") + name + "\n");
// }

// void Session::endSuite()
// {
//     // TODO: update report code
//     // TODO: better handling of tests outside test suites
//     if (m_ActiveTest.empty() ||
//         !std::dynamic_pointer_cast<TestSuite>(m_ActiveTest.back()))
//     {
//         throw std::logic_error("Call to endSuite not preceded by a call to beginSuite");
//     }
//     m_ActiveTest.
//     if (m_TestSuites.empty())
//         throw std::logic_error("Call to endSuite not preceded by a call to beginSuite");
// }

// void Session::suiteFailed(const Error& error)
// {
//     // if (m_TestSuites.empty())
//     //     throw std::logic_error("Call to suiteFailed not preceded by a call to beginSuite");
//     Test& ts = *m_TestSuites.back();
//     if (ts.tests().empty())
//         print("\n");
//     ts.setFailed(true);
//     ts.setError(error);
//     print(std::string("  ") + error.text() + "\n");
// }

void Session::beginTest(const std::string& name)
{
    TestPtr t(new Test(name));
    if (!m_ActiveTest.empty())
        m_ActiveTest.back()->addTest(t);
    else
        m_Tests.push_back(t);
    m_ActiveTest.push_back(t);
    print(std::string("  Running test ") + name);
}

void Session::endTest()
{
    if (m_ActiveTest.empty())
        throw std::logic_error("Call to endTest not preceded by a call to beginTest");
    m_ActiveTest.pop_back();
    print("\n");
}

void Session::testFailed(const Error& error)
{
    if (m_ActiveTest.empty())
        throw std::logic_error("Call to testFailed not preceded by a call to beginTest");
    print("\n");
    m_ActiveTest.back()->setError(error);
    while (!m_ActiveTest.empty())
    {
        m_ActiveTest.back()->setFailed(true);
        m_ActiveTest.pop_back();
    }
    print(std::string("    ") + error.text() + "\n");
}

void Session::assertPassed()
{
    if (m_ActiveTest.empty())
        throw std::logic_error("Call to assertPassed not preceded by a call to beginTest");
    if (m_ActiveTest.back()->assertions() == 0)
        print(" .");
    else
        print(".");
    m_ActiveTest.back()->incrementAssertions();
}

void Session::unhandledException(const Error& error)
{
    if (m_ActiveTest.empty())
        beginTest("<unknown>");
    testFailed(error);
}

size_t Session::numberOfFailedTests() const
{
    size_t failures = 0;
    for (auto test = m_Tests.begin(); test != m_Tests.end(); ++test)
        failures += (*test)->failed() ? 1 : 0;
    return failures;
}

bool Session::areAllTestsEnabled() const
{
    return m_AllTestsEnabled;
}

void Session::setAllTestsEnabled(bool enable)
{
    m_AllTestsEnabled = enable;
}

bool Session::isTestEnabled(const std::string& name) const
{
    if (m_EnabledTests.empty())
        return m_AllTestsEnabled;
    auto match = m_EnabledTests.find(getTestName(name));
    return match == m_EnabledTests.end() ? m_AllTestsEnabled : match->second;
}

void Session::setTestEnabled(const std::string& name, bool enable)
{
    m_EnabledTests[name] = enable;
}

const std::vector<TestPtr>& Session::tests() const
{
  return m_Tests;
}

void Session::print(const std::string& text)
{
    *m_Log << text;
}

std::ostream* Session::log()
{
    return m_Log;
}

void Session::setLog(std::ostream* log)
{
    m_Log = log;
}

std::string Session::getTestName(const std::string& name) const
{
    std::vector<std::string> names;
    for (auto it = m_ActiveTest.begin(); it != m_ActiveTest.end(); ++it)
        names.push_back((*it)->name());
    names.push_back(name);
    return JEBTestLib::String::join(names, "/");
}

}}
