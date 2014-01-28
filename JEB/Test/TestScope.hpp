/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_TEST_TESTSCOPE_HPP
#define JEB_TEST_TESTSCOPE_HPP

#include "Session.hpp"

namespace JEB { namespace Test {

class TestScope
{
public:
    TestScope()
        : m_Count(0)
    {}

    TestScope(const std::string& name)
        : m_Count(1)
    {
        Session::instance().beginTest(name);
    }

    ~TestScope()
    {
        while (m_Count--)
            Session::instance().endTest();
    }

    void push(const std::string& name, bool silent = false)
    {
        Session::instance().beginTest(name, silent);
        ++m_Count;
    }
private:
    int m_Count;
};

}}

#endif
