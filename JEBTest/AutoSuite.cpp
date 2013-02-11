#include "AutoSuite.hpp"

#include "AutoSuiteRunner.hpp"
#include "MacroUtilities.hpp"

namespace JEB { namespace Test {

AutoSuite::AutoSuite(const std::string& fileName, Func suiteFunc)
    : m_Function(suiteFunc),
      m_Name(fileName)
{
    AutoSuiteRunner::instance().addSuite(this);
}

const AutoSuite::Func& AutoSuite::function() const
{
    return m_Function;
}

void AutoSuite::setFunction(const Func& function)
{
    m_Function = function;
}

std::string AutoSuite::name() const
{
    return ::JEB::Test::extractSuiteName(m_Name);
}

// void AutoSuite::setName(const std::string& name)
// {
//     m_Name = name;
// }

}}
