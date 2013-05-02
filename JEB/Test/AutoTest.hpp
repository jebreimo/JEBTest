#ifndef JEB_TEST_AUTOTEST_HPP
#define JEB_TEST_AUTOTEST_HPP

#include <string>

namespace JEB { namespace Test {

class AutoTest
{
public:
    typedef void (*Func)();

    AutoTest(const std::string& fileName, Func suiteFunc);

    const Func& function() const;
    void setFunction(const Func& function);

    std::string name() const;
private:
    Func m_Function;
    std::string m_Name;
};

}}

#endif
