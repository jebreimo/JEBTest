#ifndef JEB_UNIT_AUTOSUITERUNNER_HPP
#define JEB_UNIT_AUTOSUITERUNNER_HPP

#include <vector>

namespace JEB { namespace Unit {

class AutoSuite;

class AutoSuiteRunner
{
public:
    static AutoSuiteRunner& instance();

    void addSuite(const AutoSuite* suite);
    void run();
private:
    AutoSuiteRunner();

    std::vector<const AutoSuite*> m_Suites;
};

}}

#endif
