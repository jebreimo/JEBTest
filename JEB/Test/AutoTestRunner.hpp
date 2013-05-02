#ifndef JEB_TEST_AUTOTESTRUNNER_HPP
#define JEB_TEST_AUTOTESTRUNNER_HPP

#include <vector>

namespace JEB { namespace Test {

class AutoTest;

class AutoTestRunner
{
public:
    static AutoTestRunner& instance();

    void addTest(const AutoTest* suite);
    void run();
private:
    AutoTestRunner();

    std::vector<const AutoTest*> m_Tests;
};

}}

#endif
