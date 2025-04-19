//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "JEBTest/AutoTestRunner.hpp"

#include <algorithm>
#include <iostream>
#include "JEBTest/AutoTest.hpp"
#include "JEBTest/Exceptions.hpp"
#include "JEBTest/Session.hpp"
#include "JEBTest/TestScope.hpp"

namespace JEBTest
{
    AutoTestRunner::AutoTestRunner() = default;

    AutoTestRunner& AutoTestRunner::instance()
    {
        static AutoTestRunner runner;
        return runner;
    }

    void AutoTestRunner::addTest(const AutoTest* suite)
    {
        m_Tests.push_back(suite);
    }

    static bool hasHigherPriority(const AutoTest* a, const AutoTest* b)
    {
        if (a->priority() >= 0 && b->priority() >= 0)
            return a->priority() < b->priority();
        else
            return a->priority() > b->priority();
    }

    void AutoTestRunner::run()
    {
        std::sort(m_Tests.begin(), m_Tests.end(), hasHigherPriority);
        for (auto& test : m_Tests)
        {
            TestScope scope;
            auto& session = Session::instance();
            auto& path = test->path();
            auto name = begin(path);
            for (; name != end(path); ++name)
            {
                if (session.isTestEnabled(*name))
                    scope.push(*name, true);
            }
            if (name == end(path) && session.isTestEnabled(test->name()))
            {
                scope.push(test->name());
                try
                {
                    test->function()();
                }
                catch (const TestFailure&)
                {}
                catch (const CriticalFailure&)
                {}
            }
        }
    }

    int runAllTests()
    {
        try
        {
            try
            {
                AutoTestRunner::instance().run();
            }
            catch (...)
            {
            }
            Session::instance().print("");
            Session::instance().flushLog();
            Session::instance().writeReports();
        }
        catch (std::exception& ex)
        {
            std::cerr << "EXCEPTION: " << ex.what() << "\n";
            return 1;
        }
        return int(Session::instance().numberOfFailedTests());
    }

    int runAllTests(int argc, char** argv)
    {
        try
        {
            if (!Session::instance().parseCommandLine(argc, argv))
                return 1;
            runAllTests();
        }
        catch (std::exception& ex)
        {
            std::cerr << "EXCEPTION: " << ex.what() << "\n";
            return 1;
        }
        return int(Session::instance().numberOfFailedTests());
    }
}
