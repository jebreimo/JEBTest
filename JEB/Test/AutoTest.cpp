#include "AutoTest.hpp"

#include "AutoTestRunner.hpp"
#include "MacroUtilities.hpp"

namespace JEB { namespace Test {

AutoTest::AutoTest(const std::string& fileName, Func suiteFunc)
    : m_Function(suiteFunc),
      m_Name(fileName)
{
    AutoTestRunner::instance().addTest(this);
}

const AutoTest::Func& AutoTest::function() const
{
    return m_Function;
}

void AutoTest::setFunction(const Func& function)
{
    m_Function = function;
}

std::string AutoTest::name() const
{
    return ::JEB::Test::extractSuiteName(m_Name);
}

}}
