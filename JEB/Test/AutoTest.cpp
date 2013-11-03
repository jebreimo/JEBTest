/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "AutoTest.hpp"

#include <limits>
#include "JEB/Sys/Path.hpp"

#undef JEB

#include "AutoTestRunner.hpp"
#include "MacroUtilities.hpp"

namespace JEB { namespace Test {

using namespace JEBTestLib::Sys;

namespace
{
    std::string extractSuiteName(const std::string& path)
    {
        return Path::baseName(Path::removeExtension(path));
    }
}

AutoTest::AutoTest(const std::string& fileName, Func suiteFunc)
    : m_Function(suiteFunc),
      m_Name(fileName),
      m_Priority(std::numeric_limits<int>::max())
{
    AutoTestRunner::instance().addTest(this);
}

AutoTest::AutoTest(const std::string& fileName, Func suiteFunc, int priority)
    : m_Function(suiteFunc),
      m_Name(fileName),
      m_Priority(priority)
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
    return JEB::Test::extractSuiteName(m_Name);
}

int AutoTest::priority() const
{
    return m_Priority;
}

}}
