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
