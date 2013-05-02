#include "AutoTestRunner.hpp"

#include "AutoTest.hpp"
#include "Exceptions.hpp"
#include "Session.hpp"

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
            Session::instance().beginTest((*suite)->name());
            try
            {
                (*suite)->function()();
                Session::instance().endTest();
            }
            catch (const TestFailure& ex)
            {
                Session::instance().testFailed(ex.error());
            }
        }
    }
}

}}
