#include "AutoSuiteRunner.hpp"

#include "AutoSuite.hpp"
#include "Exceptions.hpp"
#include "Session.hpp"

namespace JEB { namespace Test {

AutoSuiteRunner::AutoSuiteRunner()
{
}

AutoSuiteRunner& AutoSuiteRunner::instance()
{
    static AutoSuiteRunner runner;
    return runner;
}

void AutoSuiteRunner::addSuite(const AutoSuite* suite)
{
    m_Suites.push_back(suite);
}

void AutoSuiteRunner::run()
{
    for (std::vector<const AutoSuite*>::const_iterator it = m_Suites.begin(); it != m_Suites.end(); it++)
    {
        Session::instance().beginSuite((*it)->name());
        try
        {
            (*it)->function()();
            Session::instance().endSuite();
        }
        catch (const TestSuiteFailure& ex)
        {
            Session::instance().suiteFailed(ex.error());
        }
    }
}

}}
