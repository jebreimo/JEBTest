#ifndef JEB_TEST_TESTSUITE_HPP
#define JEB_TEST_TESTSUITE_HPP

#include "Test.hpp"

namespace JEB { namespace Test {

typedef std::shared_ptr<class Test> TestPtr;

class TestSuite
{
public:
    TestSuite(const std::string& name);

    const Error& error() const;
    void setError(const Error& error);

    bool failed() const;
    void setFailed(bool failed);

    const std::string& name() const;

    void addTest(TestPtr test);
    std::vector<TestPtr>& tests();
    const std::vector<TestPtr>& tests() const;
private:
    Error m_Error;
    bool m_Failed;
    std::string m_Name;
    std::vector<TestPtr> m_Tests;
};

}}

#endif
