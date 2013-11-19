/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "Report.hpp"

#include <iomanip>
#include <iostream>
#include "JEB/Xml/XmlWriter.hpp"
#undef JEB

#include "Session.hpp"
#include "Test.hpp"

namespace JEB { namespace Test {

using namespace JEBTestLib::Xml;

struct Counters
{
    Counters() : assertions(), tests(), failedTests(), errors() {}
    size_t assertions;
    size_t tests;
    size_t failedTests;
    size_t errors;
};

Counters& operator+=(Counters& lhs, const Counters& rhs)
{
    lhs.assertions += rhs.assertions;
    lhs.tests += rhs.tests;
    lhs.failedTests += rhs.failedTests;
    return lhs;
}

static std::string testName(const std::vector<TestPtr>& parents,
                            const TestPtr& test)
{
    std::string name;
    for (auto it = parents.begin(); it != parents.end(); ++it)
        name += (*it)->name() + "/";
    name += test->name();
    return name;
}

static Counters writeTextReport(
        std::ostream& os,
        const std::vector<TestPtr>& tests,
        std::vector<TestPtr>& parents)
{
    Counters counters;
    for (auto it = tests.begin(); it != tests.end(); ++it)
    {
        if ((*it)->failed() || (*it)->tests().empty() || (*it)->assertions())
            ++counters.tests;
        counters.assertions += (*it)->assertions();
        if (!(*it)->tests().empty())
        {
            parents.push_back(*it);
            counters += writeTextReport(os, (*it)->tests(), parents);
            parents.pop_back();
        }
        auto& errors = (*it)->errors();
        if ((*it)->failed())
        {
            ++counters.failedTests;
            os << testName(parents, *it) << ": FAILED (assertion "
               << ((*it)->assertions()) << ")\n";
        }
        else if (!errors.empty())
        {
            os << testName(parents, *it) << ": SUCCEEDED WITH WARNINGS\n";
        }
        for (auto err = begin(errors); err != end(errors); ++err)
        {
            ++counters.errors;
            os << "    " << *err << "\n";
            const std::vector<Error>& context = err->context();
            if (!context.empty())
            {
                os << "    Called from:\n";
                for (auto c = context.begin(); c != context.end(); ++c)
                    os << "        " << c->text() << "\n";
            }
        }
    }
    return counters;
}

void writeTextReport(std::ostream& os, const Session& session)
{
    if (session.tests().empty())
    {
        os << "No tests were executed.\n";
        return;
    }
    os << "\n=== Test Report ===\n";
    std::vector<TestPtr> parents;
    Counters counters = writeTextReport(os, session.tests(), parents);
    os << counters.assertions << " assertions passed.\n"
       << (counters.tests - counters.failedTests) << " tests passed.\n"
       << counters.failedTests << " tests failed.\n";
    if (counters.failedTests)
        os << "=== TESTS FAILED ===\n";
    else
        os << "=== TESTS PASSED ===\n";
    os.flush();
}

void addTestCases(std::map<std::string, std::vector<TestPtr>>& testCases,
                  std::string path, TestPtr test)
{
    if (test->assertions() > 0)
        testCases[path].push_back(test);
    auto subtests = test->tests();
    if (!subtests.empty())
    {
        path += "/";
        path += test->name();
        auto subtests = test->tests();
        for (auto it = begin(subtests); it != end(subtests); ++it)
            addTestCases(testCases, path, *it);
    }
}

std::map<std::string, std::vector<TestPtr>> getTestCases(
        const std::vector<TestPtr>& tests)
{
    std::map<std::string, std::vector<TestPtr>> testCases;
    for (auto it = begin(tests); it != end(tests); ++it)
        addTestCases(testCases, std::string(), *it);
    return testCases;
}

void writeXmlTestCase(XmlWriter& writer, const Test& test)
{
    writer.beginElement("testcase");
    writer.attribute("name", test.name());
    if (test.assertions() != 0)
    {
        writer.attribute("assertions", (int64_t)test.assertions());
        writer.attribute("name", "NONE");
        writer.attribute("time", test.elapsedTime());
        auto& errors = test.errors();
        for (auto it = begin(errors); it != end(errors); ++it)
        {
            if (it->level() == Error::System)
                writer.beginElement("error");
            else
                writer.beginElement("failure");
            writer.attribute("message", it->message());
            writer.endElement();
        }
    }
    auto testCases = test.tests();
    for (auto it = begin(testCases); it != end(testCases); ++it)
    {
        writeXmlTestCase(writer, **it);
    }
    writer.endElement();
}

void writeXmlReport(std::ostream& os, const Session& session)
{
    auto testCases = getTestCases(session.tests());
    XmlWriter writer(os);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("testsuites");
    //auto testSuites = session.tests();
    for (auto it = begin(testCases); it != end(testCases); ++it)
    {
        //addTestCases(testCases, *it);
        writer.beginElement("testsuite");
        writer.attribute("name", it->first);
        for (auto t = begin(it->second); t != end(it->second); ++t)
        {
            writeXmlTestCase(writer, **t);
        }
        writer.endElement();
    }
    writer.endElement();
}

}}
