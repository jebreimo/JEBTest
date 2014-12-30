/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "Session.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "JUnitReport.hpp"
#include "ParseArguments.hpp"
#include "Test.hpp"
#include "TextReport.hpp"
#include "VisualStudioReport.hpp"

#include "JEBString/JEBUtf8.hpp"
#include "JEBIO/Paths/PathFilter.hpp"
#include "JEBIO/Streams/StreamRedirection.hpp"

namespace JEBTest {

using namespace JEBTest_JEBString;
using namespace JEBTest_JEBIO;

Session::Session()
    : m_AllTestsEnabled(true),
      m_EnabledReports(0),
      m_Log(&std::cerr),
      m_StartOfLine(true),
      m_TestFilter(new PathFilter),
      m_Verbose(true)
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

bool Session::parseCommandLine(int argc, char* argv[])
{
    auto args = parse_arguments(argc, argv);
    if (args->parse_arguments_result != Arguments::RESULT_OK)
        return false;
    if (args->junit)
        setReportEnabled(JUnitReport, true);
    if (args->text || !args->junit)
        setReportEnabled(TextReport, true);
    if (!args->logfile.empty())
        setLogFile(args->logfile);
    m_ReportFileName = args->report;
    setAllTestsEnabled(args->exclude || args->test_name.empty());
    for (auto it = begin(args->test_name); it != end(args->test_name); ++it)
        setTestEnabled(*it, !args->exclude);
    m_Verbose = args->verbose;
    return true;
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
        throw std::runtime_error("Can't create report file: " + fileName);
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
        if (isRunnningInVisualStudio())
            writeVisualStudioReport(func, session);
        else
            func(std::cout, session);
    }
    else if (!forceExtension ||
             Utf8::endsWith(fileName, fileNameExtension,
                            FindFlags::CaseInsensitive))
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
        writeReport(writeJUnitReport, m_ReportFileName, ".xml",
                    (m_EnabledReports & ~JUnitReport) != 0, *this);
}

void Session::beginTest(const std::string& name /*= "<unnamed>"*/,
                        bool silent /*= false*/)
{
    TestPtr test;
    if (!m_ActiveTest.empty())
        test = m_ActiveTest.back()->findTest(name);
    else
        test = findTest(name);
    if (!test)
    {
        test = TestPtr(new Test(name));
        if (!m_ActiveTest.empty())
            m_ActiveTest.back()->addTest(test);
        else
            m_Tests.push_back(test);
    }
    m_ActiveTest.push_back(test);
    m_TestFilter->descend(name);
    if (!silent)
        printInfo(getTestName());
    m_ActiveTest.back()->setStartTime(clock());
}

void Session::endTest()
{
    if (m_ActiveTest.empty())
        throw std::logic_error("Call to endTest not preceded by a call "
                               "to beginTest");
    m_ActiveTest.back()->setEndTime(clock());
    m_ActiveTest.pop_back();
    m_TestFilter->ascend();
}

void Session::testFailed(const Error& error)
{
    if (m_ActiveTest.empty())
        throw std::logic_error("Call to testFailed was not preceded by "
                               "a call to beginTest.");
    m_ActiveTest.back()->addError(error);
    printInfo(std::string("    ") + error.text() + "\n");
}

void Session::assertPassed()
{
    if (m_ActiveTest.empty())
        throw std::logic_error("Call to assertPassed not preceded by a "
                               "call to beginTest.");
    if (m_ActiveTest.back()->assertions() == 0)
        printInfo(" .", false);
    else
        printInfo(".", false);
    m_ActiveTest.back()->incrementAssertions();
}

size_t Session::numberOfFailedTests() const
{
    size_t failures = 0;
    for (auto test = begin(m_Tests); test != end(m_Tests); ++test)
        failures += (*test)->failedHierarchy() ? 1 : 0;
    return failures;
}

bool Session::areAllTestsEnabled() const
{
    return m_AllTestsEnabled;
}

void Session::setAllTestsEnabled(bool enable)
{
    m_TestFilter->setType(enable ? InclusiveFilter : ExclusiveFilter);
}

bool Session::isTestEnabled(const std::string& name) const
{
    return m_TestFilter->shouldDescend(name);
}

void Session::setTestEnabled(const std::string& name, bool enable)
{
    if (enable)
        m_TestFilter->includePath(name);
    else
        m_TestFilter->excludePath(name);
}

const std::vector<TestPtr>& Session::tests() const
{
  return m_Tests;
}

void Session::print(const std::string& text, bool startOnNewLine)
{
    if (startOnNewLine && !m_StartOfLine)
        *m_Log << '\n';
    *m_Log << text;
    m_StartOfLine = text.empty() ? m_StartOfLine : text.back() == '\n';
}

void Session::printInfo(const std::string& text, bool startOnNewLine)
{
    if (!m_Verbose)
        return;
    if (startOnNewLine && !m_StartOfLine)
        *m_Log << '\n';
    *m_Log << text;
    m_StartOfLine = text.empty() ? m_StartOfLine : text.back() == '\n';
}

std::ostream* Session::log()
{
    return m_Log;
}

void Session::setLog(std::ostream* log)
{
    m_Log = log;
}

bool Session::verbose() const
{
    return m_Verbose;
}

void Session::setVerbose(bool verbose)
{
    m_Verbose = verbose;
}

TestPtr Session::findTest(const std::string& name)
{
    auto it = std::find_if(
            begin(m_Tests), end(m_Tests),
            [&](const TestPtr& t){return t->name() == name;});
    if (it != end(m_Tests))
        return *it;
    else
        return TestPtr();
}

std::string Session::getTestName() const
{
    std::vector<std::string> names;
    for (auto it = begin(m_ActiveTest); it != end(m_ActiveTest); ++it)
        names.push_back((*it)->name());
    return Utf8::join(names, "/");
}

std::string Session::getTestName(const std::string& name) const
{
    std::vector<std::string> names;
    for (auto it = begin(m_ActiveTest); it != end(m_ActiveTest); ++it)
        names.push_back((*it)->name());
    names.push_back(name);
    return Utf8::join(names, "/");
}

void Session::setLogFile(const std::string& fileName)
{
    m_LogFile.open(fileName);
    m_Log = &m_LogFile;
    m_Redirections.push_back(StreamRedirection(std::cout, m_LogFile));
    m_Redirections.push_back(StreamRedirection(std::cerr, m_LogFile));
    m_Redirections.push_back(StreamRedirection(std::clog, m_LogFile));
}

}
