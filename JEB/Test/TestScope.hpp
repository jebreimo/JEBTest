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
    TestScope(const std::string& name)
    {
        Session::instance().beginTest(name);
    }

    ~TestScope()
    {
        Session::instance().endTest();
    }
};

}}

#endif
