//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "JEBTest/Session.hpp"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include "Argos/Argos.hpp"
#include "Ystring/Algorithms.hpp"
#include "JUnitReport.hpp"
#include "PathFilter.hpp"
#include "StreamRedirection.hpp"
#include "Test.hpp"
#include "TextReport.hpp"
#include "VisualStudioReport.hpp"

namespace JEBTest
{
    namespace
    {
        std::string get_env(const char* var_name)
        {
            if (const auto* var = std::getenv(var_name))
                return var;
            return {};
        }

        std::string_view get_base_name(std::string_view str)
        {
            auto pos = str.find_last_of("/\\");
            return pos == std::string_view::npos ? str : str.substr(pos + 1);
        }

        argos::ParsedArguments parse_arguments(int argc, char* argv[])
        {
            using namespace argos;
            const std::string report_section("REPORT OPTIONS");

            ArgumentParser argument_parser(argv[0]);
            auto report_default = get_env("JEBTEST_REPORT");
            const auto junit_default = get_env("JEBTEST_JUNIT");
            const auto text_default = get_env("JEBTEST_TEXT");
            return argument_parser
                .add(Argument("TEST").count(0, UINT_MAX)
                    .help("The name of the test or tests that will be run."
                          " All tests are run if no test names are given.\n"
                          "\n"
                          "Tests are typically arranged in a two-level"
                          " hierarchy with a parent (with the same name as the"
                          " cpp file) and several child-tests.\n"
                          "\n"
                          "Example:\n"
                          "\n"
                          "If the tests are arranged like this:\n"
                          "\n"
                          "Test1:\n"
                          "    Subtest1:\n"
                          "        Subsubtest1\n"
                          "        Subsubtest2\n"
                          "    Subtest2:\n"
                          "        Subsubtest1\n"
                          "        Subsubtest2\n"
                          "Test2:\n"
                          "    Subtest1\n"
                          "    Subtest2\n"
                          "\n"
                          "- \"Test1\" will run the tests under Test1, tests"
                          " under Test2 are ignored.\n"
                          "- \"Test1/Subtest2\" will run the tests under"
                          " Test1/Subtest2, all other tests are ignored.\n"
                          "\n"
                          "The --exclude option inverts the effect of these"
                          " arguments: all tests except the named ones (and"
                          " those under it) are run."))
                .add(Option{"-e", "--exclude"}
                    .help("Inverts the effect of the TEST arguments."))
                .add(Option{"-l", "--logfile"}.argument("FILE")
                    .help("Redirect all the output the tests normally write"
                          " to stdout or stderr to a file named FILE instead"
                          " (this does not affect the test reports)."))
                .add(Option{"-q", "--quiet"}.alias("--verbse")
                    .constant(false)
                    .help("Don't display extra information while running"
                          " tests (opposite of --verbose)."))
                .add(Option{"-v", "--verbose"}
                    .help("Display extra information while running tests"
                          " (this is the default)."))
                .add(Option{"--junit"}
                    .initial_value(junit_default)
                    .section(report_section)
                    .help("Produce a test report in the JUnit XML format."))
                .add(Option{"--text"}
                    .initial_value(text_default)
                    .section(report_section)
                    .help("Produce a plain text test report that only list"
                          " failed tests (this is the default)."))
                .add(Option{"-f", "--report"}.argument("FILE")
                    .initial_value(report_default)
                    .section(report_section)
                    .help("The name of the report file. FILE will have a"
                          " suitable file type extension appended to it (txt,"
                          " xml etc.). Test reports are written to stdout if"
                          " this option isn't used. If the name is \"-\", a"
                          " name, \"jebTestResult.<program name>\", is"
                          " auto-generated."))
                .add(Option{"--host"}.argument("HOST")
                    .section(report_section)
                    .help("Set the host name. This option has no effect on"
                          " tests; it's only included in the test report."))
                .text(TextId::FINAL_TEXT,
                      "The following environment variables can also be used"
                      " to override the default behavior, but will themselves"
                      " be overridden by the corresponding arguments:\n"
                      "- JEBTEST_REPORT sets the default value for --report.\n"
                      "- JEBTEST_JUNIT sets the default value for --junit"
                      " (\"true\" or \"false\").\n"
                      "- JEBTEST_TEXT sets the default value for --text"
                      " (\"true\" or \"false\").")
                .parse(argc, argv);
        }
    }

    Session::Session()
        : m_AllTestsEnabled(true),
          m_EnabledReports(0),
          m_Log(&std::cerr),
          m_StartOfLine(true),
          m_TestFilter(new PathFilter),
          m_Verbose(true)
    {}

    Session::~Session() = default;

    Session& Session::instance()
    {
        static Session test;
        return test;
    }

    bool Session::parseCommandLine(int argc, char* argv[])
    {
        auto args = parse_arguments(argc, argv);
        setReportEnabled(JUnitReport, args.value("--junit").as_bool());
        setReportEnabled(TextReport, args.value("--text").as_bool());
        setLogFile(args.value("--logfile").as_string());
        m_ReportFileName = args.value("--report").as_string();
        if (m_ReportFileName == "-")
        {
            m_ReportFileName = "jebTestResult."
                               + std::string(get_base_name(argv[0]));
        }
        const auto exclude = args.value("--exclude").as_bool();
        const auto test_names = args.values("TEST").as_strings();
        setAllTestsEnabled(exclude || test_names.empty());
        for (const auto& name : test_names)
        {
            setTestEnabled(name, !exclude);
        }
        m_Verbose = args.value("--verbose").as_bool(true);
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
                     const Session& session)
    {
        if (fileName.empty())
        {
            if (isRunningInVisualStudio())
                writeVisualStudioReport(func, session);
            func(std::cout, session);
        }
        else if (ystring::case_insensitive_ends_with(fileName, fileNameExtension))
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
            writeReport(writeTextReport, m_ReportFileName, ".txt", *this);
        if (reports & JUnitReport)
            writeReport(writeJUnitReport, m_ReportFileName, ".xml", *this);
        if (!m_ReportFileName.empty())
            writeReport(writeTextReport, {}, {}, *this);
    }

    void Session::beginTest(const std::string& name, bool silent)
    {
        TestPtr test;
        if (!m_ActiveTest.empty())
            test = m_ActiveTest.back()->findTest(name);
        else
            test = findTest(name);
        if (!test)
        {
            test = std::make_shared<Test>(name);
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

    void Session::setTestEnabled(std::string name, bool enable)
    {
        if (enable)
            m_TestFilter->includePath(move(name));
        else
            m_TestFilter->excludePath(move(name));
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
        if (!verbose())
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

    void Session::flushLog()
    {
        m_Log->flush();
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
            return {};
    }

    std::string Session::getTestName() const
    {
        std::vector<std::string> names;
        for (const auto& test : m_ActiveTest)
            names.push_back(test->name());
        return ystring::join(names.begin(), names.end(), "/");
    }

    void Session::setLogFile(const std::string& fileName)
    {
        if (!fileName.empty())
        {
            m_LogFile.open(fileName);
            m_Log = &m_LogFile;
            m_Redirections.emplace_back(std::cout, m_LogFile);
            m_Redirections.emplace_back(std::cerr, m_LogFile);
            m_Redirections.emplace_back(std::clog, m_LogFile);
        }
    }
}
