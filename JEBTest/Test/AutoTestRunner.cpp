/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "AutoTestRunner.hpp"

#include <algorithm>
#include "AutoTest.hpp"
#include "Exceptions.hpp"
#include "Session.hpp"
#include "TestScope.hpp"

namespace JEB { namespace Test {

AutoTestRunner::AutoTestRunner()
{
}

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
    for (auto test = m_Tests.begin(); test != m_Tests.end(); ++test)
    {
        TestScope scope;
        auto& session = Session::instance();
        auto& path = (*test)->path();
        auto name = begin(path);
        for (; name != end(path); ++name)
        {
            if (session.isTestEnabled(*name))
                scope.push(*name, true);
        }
        if (name == end(path) && session.isTestEnabled((*test)->name()))
        {
            scope.push((*test)->name());
            try
            {
                (*test)->function()();
            }
            catch (const TestFailure&)
            {}
            catch (const CriticalFailure&)
            {}
        }
    }
}

}}
