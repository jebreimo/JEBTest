/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_SESSION_HPP
#define JEB_SESSION_HPP

#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Error.hpp"

namespace JEBTestLib { namespace Sys {

class PathFilter;
class StreamRedirection;

}}

namespace JEB { namespace Test {

typedef std::shared_ptr<class Test> TestPtr;

enum ReportFormat
{
    TextReport = 1,
    JUnitReport = 2,
    FullTextReport = 3
};

class Session
{
public:
    static Session& instance();

    bool parseCommandLine(int argc, char* argv[]);

    bool reportEnabled(ReportFormat format) const;
    void setReportEnabled(ReportFormat format, bool enabled);

    const std::string& reportFileName() const;
    void setReportFileName(const std::string& fileName);

    void writeReports();

    void beginTest(const std::string& name = "<unnamed>");
    void endTest();
    void testFailed(const Error& error);
    void assertPassed();

    size_t numberOfFailedTests() const;

    bool areAllTestsEnabled() const;
    void setAllTestsEnabled(bool enable);
    bool isTestEnabled(const std::string& name) const;
    void setTestEnabled(const std::string& name, bool enable);

    const std::vector<TestPtr>& tests() const;

    void print(const std::string& text, bool startOnNewLine = true);
    void printInfo(const std::string& text, bool startOnNewLine = true);

    std::ostream* log();
    void setLog(std::ostream* log);

    bool verbose() const;
    void setVerbose(bool verbose);
private:
    Session();
    ~Session();
    TestPtr findTest(const std::string& name);
    std::string getTestName(const std::string& name) const;
    void setLogFile(const std::string& fileName);

    std::vector<TestPtr> m_ActiveTest;
    bool m_AllTestsEnabled;
    unsigned m_EnabledReports;
    std::ostream* m_Log;
    std::ofstream m_LogFile;
    std::vector<JEBTestLib::Sys::StreamRedirection> m_Redirections;
    std::string m_ReportFileName;
    bool m_StartOfLine;
    std::unique_ptr<JEBTestLib::Sys::PathFilter> m_TestFilter;
    std::vector<TestPtr> m_Tests;
    bool m_Verbose;
};

}}

#endif
