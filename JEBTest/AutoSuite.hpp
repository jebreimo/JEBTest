#ifndef JEB_TEST_AUTOSUITE_HPP
#define JEB_TEST_AUTOSUITE_HPP

#include <string>

namespace JEB { namespace Test {

class AutoSuite
{
public:
    typedef void (*Func)();

    AutoSuite(const std::string& fileName, Func suiteFunc);

    const Func& function() const;
    void setFunction(const Func& function);

    std::string name() const;
    // void setName(const std::string& name);
private:
    Func m_Function;
    std::string m_Name;
};

}}

#endif
