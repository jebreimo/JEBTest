#include "AutoSuite.hpp"

#include "AutoSuiteRunner.hpp"

namespace JEB { namespace Unit {

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

const std::string& AutoSuite::name() const
{
    return m_Name;
}

void AutoSuite::setName(const std::string& name)
{
    m_Name = name;
}

}}
