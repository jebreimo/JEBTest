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
#include "Session.hpp"
#include "Test.hpp"

#include "JEB/Xml/XmlWriter.hpp"
#undef JEB

namespace JEB { namespace Test {

struct Counters
{
    Counters() : assertions(0), tests(0), failedTests(0) {}
    size_t assertions;
    size_t tests;
    size_t failedTests;
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
        name += (*it)->name() + ".";
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
        if ((*it)->tests().empty() || (*it)->assertions())
            ++counters.tests;
        counters.assertions += (*it)->assertions();
        if (!(*it)->tests().empty())
        {
            parents.push_back(*it);
            counters += writeTextReport(os, (*it)->tests(), parents);
            parents.pop_back();
        }
        if ((*it)->failed())
        {
            ++counters.failedTests;
            os << testName(parents, *it) << ": FAILED (assertion no."
               << ((*it)->assertions() + 1) << ")\n"
               << "  " << (*it)->error() << "\n";
            const std::vector<Error>& context = (*it)->error().context();
            if (!context.empty())
            {
                for (auto c = context.begin(); c != context.end(); ++c)
                    os << "    " << c->text() << "\n";
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
    size_t testSuiteFailures = 0;
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

void writeXmlReport(std::ostream& os, const Session& session)
{}

}}
