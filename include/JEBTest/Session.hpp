//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Error.hpp"

namespace JEBTest
{
    class PathFilter;
    class StreamRedirection;

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

        void beginTest(const std::string& name = "<unnamed>",
                       bool silent = false);
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
        void flushLog();

        bool verbose() const;
        void setVerbose(bool verbose);
    private:
        Session();
        ~Session();
        TestPtr findTest(const std::string& name);
        std::string getTestName() const;
        std::string getTestName(const std::string& name) const;
        void setLogFile(const std::string& fileName);

        std::vector<TestPtr> m_ActiveTest;
        bool m_AllTestsEnabled;
        unsigned m_EnabledReports;
        std::ostream* m_Log;
        std::ofstream m_LogFile;
        std::vector<StreamRedirection> m_Redirections;
        std::string m_ReportFileName;
        bool m_StartOfLine;
        std::unique_ptr<PathFilter> m_TestFilter;
        std::vector<TestPtr> m_Tests;
        bool m_Verbose;
    };
}
