/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "Session.hpp"

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "Report.hpp"
#include "Test.hpp"

#include "JEB/String/String.hpp"
#undef JEB

namespace JEB { namespace Test {

using namespace JEBTestLib::String;

Session::Session()
    : m_AllTestsEnabled(true),
      m_EnabledReports(0),
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

bool Session::reportEnabled(ReportFormat format) const
{
    return (m_EnabledReports & format) != 0;
}

void Session::setReportEnabled(ReportFormat format, bool enabled)
{
    if (enabled)
        m_EnabledReports |= format;
    else
        m_EnabledReports &= ~format;
}

const std::string& Session::reportFileName() const
{
    return m_ReportFileName;
}

void Session::setReportFileName(const std::string& fileName)
{
    m_ReportFileName = fileName;
}

typedef void (*ReportFunc)(std::ostream&, const Session&);

void writeFileReport(ReportFunc func,
                     const std::string& fileName,
                     const Session& session)
{
    std::ofstream file(fileName);
    if (!file)
        throw std::runtime_error(FORMAT_STRING("Can't create report file: " << fileName));
    func(file, session);
}

void writeReport(ReportFunc func,
                 const std::string& fileName,
                 const std::string& fileNameExtension,
                 bool forceExtension,
                 const Session& session)
{
    if (fileName.empty())
    {
        func(std::cout, session);
    }
    else if (!forceExtension ||
             endsWith(fileName, fileNameExtension, FindFlags::CaseInsensitive))
    {
        writeFileReport(func, fileName, session);
    }
    else
    {
        writeFileReport(func, fileName + fileNameExtension, session);
    }
}

void Session::writeReports()
{
    unsigned reports = m_EnabledReports ? m_EnabledReports : TextReport;
    if (reports & TextReport)
        writeReport(writeTextReport, m_ReportFileName, ".txt",
                    (m_EnabledReports & ~TextReport) != 0, *this);
    if (reports & JUnitReport)
        writeReport(writeTextReport, m_ReportFileName, ".xml",
                    (m_EnabledReports & ~JUnitReport) != 0, *this);
}

void Session::beginTest(const std::string& name)
{
    TestPtr t(new Test(name));
    if (!m_ActiveTest.empty())
        m_ActiveTest.back()->addTest(t);
    else
        m_Tests.push_back(t);
    m_ActiveTest.push_back(t);
    print(std::string("\nRunning test ") + name);
    m_ActiveTest.back()->setStartTime(clock());
}

void Session::endTest()
{
    if (m_ActiveTest.empty())
        throw std::logic_error("Call to endTest not preceded by a call to beginTest");
    m_ActiveTest.back()->setEndTime(clock());
    m_ActiveTest.pop_back();
    print("\n");
}

void Session::testFailed(const Error& error)
{
    if (m_ActiveTest.empty())
        throw std::logic_error("Call to testFailed, criticalError or fatalError was not preceded by a call to beginTest");
    print("\n");
    m_ActiveTest.back()->setError(error);
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

size_t Session::numberOfFailedTests() const
{
    size_t failures = 0;
    for (auto test = m_Tests.begin(); test != m_Tests.end(); ++test)
        failures += (*test)->failedHierarchy() ? 1 : 0;
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
    return join(names, "/");
}

}}
