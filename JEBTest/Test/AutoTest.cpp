/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "AutoTest.hpp"

#include <limits>
#include <boost/filesystem.hpp>
#include "JEBString/JEBUtf8.hpp"

#include "AutoTestRunner.hpp"
#include "MacroUtilities.hpp"

namespace JEB { namespace Test {

using namespace JEBTest_JEBString;

namespace
{
    std::string extractSuiteName(const std::string& path)
    {
        return boost::filesystem::path(path).filename()
                                            .replace_extension()
                                            .string();
    }
}

AutoTest::AutoTest(const std::string& fileName, Func func,
                   const std::string& path)
    : m_Function(func),
      m_Name(fileName),
      m_Priority(std::numeric_limits<int>::max())
{
    if (!path.empty())
        m_Path = Utf8::split(path, "/");
    AutoTestRunner::instance().addTest(this);
}

AutoTest::AutoTest(const std::string& fileName, Func func,
                   const std::string& path, int priority)
    : m_Function(func),
      m_Name(fileName),
      m_Priority(priority)
{
    if (!path.empty())
        m_Path = Utf8::split(path, "/");
    AutoTestRunner::instance().addTest(this);
}

AutoTest::~AutoTest()
{}

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

const std::vector<std::string>& AutoTest::path() const
{
    return m_Path;
}

int AutoTest::priority() const
{
    return m_Priority;
}

}}
