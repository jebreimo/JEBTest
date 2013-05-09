/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_SESSION_HPP
#define JEB_SESSION_HPP

#include <iosfwd>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace JEB { namespace Test {

class Error;
typedef std::shared_ptr<class Test> TestPtr;

enum ReportFormat
{
    TextReport = 1,
    JUnitReport = 2
};

class Session
{
public:
    static Session& instance();

    bool reportEnabled(ReportFormat format) const;
    void setReportEnabled(ReportFormat format, bool enabled);

    const std::string& reportFileName() const;
    void setReportFileName(const std::string& fileName);

    void writeReports();

    void beginTest(const std::string& name = "<unnamed>");
    void endTest();
    void testFailed(const Error& error);
    void assertPassed();

    // void criticalError(const Error& error);
    // void fatalError(const Error& error);
    void unhandledException(const Error& error);

    size_t numberOfFailedTests() const;

    bool areAllTestsEnabled() const;
    void setAllTestsEnabled(bool enable);
    bool isTestEnabled(const std::string& name) const;
    void setTestEnabled(const std::string& name, bool enable);

    const std::vector<TestPtr>& tests() const;

    void print(const std::string& text);

    std::ostream* log();
    void setLog(std::ostream* log);
private:
    Session();
    ~Session();
    std::string getTestName(const std::string& name) const;

    std::vector<TestPtr> m_ActiveTest;
    bool m_AllTestsEnabled;
    unsigned m_EnabledReports;
    std::map<std::string, bool> m_EnabledTests;
    std::ostream* m_Log;
    std::string m_ReportFileName;
    std::vector<TestPtr> m_Tests;
};

}}

#endif
