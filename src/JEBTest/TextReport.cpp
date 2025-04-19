//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "TextReport.hpp"

#include <ostream>
#undef JEB

#include "JEBTest/Session.hpp"
#include "Test.hpp"

namespace JEBTest
{
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
        for (const auto & parent : parents)
            name += parent->name() + "/";
        name += test->name();
        return name;
    }

    static Counters writeTextReport(
            std::ostream& os,
            const std::vector<TestPtr>& tests,
            std::vector<TestPtr>& parents)
    {
        Counters counters;
        for (const auto & test : tests)
        {
            if (test->failed() || test->tests().empty() ||
                    test->assertions())
            {
                ++counters.tests;
            }
            counters.assertions += test->assertions();
            if (!test->tests().empty())
            {
                parents.push_back(test);
                counters += writeTextReport(os, test->tests(), parents);
                parents.pop_back();
            }
            auto& errors = test->errors();
            if (test->failed())
            {
                ++counters.failedTests;
                os << testName(parents, test) << ": FAILED (assertion "
                   << (test->assertions() + 1) << ")\n";
            }
            else if (!errors.empty())
            {
                os << testName(parents, test) << ": SUCCEEDED WITH WARNINGS\n";
            }
            for (const auto& error : errors)
            {
                ++counters.errors;
                os << "    " << error << "\n";
                const std::vector<Error>& context = error.context();
                if (!context.empty())
                {
                    os << "    Called from:\n";
                    for (const auto & c : context)
                        os << "        " << c.text() << "\n";
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
}
