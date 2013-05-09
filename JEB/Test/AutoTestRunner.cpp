/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "AutoTestRunner.hpp"

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

void AutoTestRunner::run()
{
    for (auto suite = m_Tests.begin(); suite != m_Tests.end(); ++suite)
    {
        if (Session::instance().isTestEnabled((*suite)->name()))
        {
            TestScope scope((*suite)->name());
            try
            {
                (*suite)->function()();
            }
            catch (const TestFailure& ex)
            {
                Session::instance().testFailed(ex.error());
            }
        }
    }
}

}}
