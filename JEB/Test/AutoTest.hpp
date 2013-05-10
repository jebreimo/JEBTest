/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_TEST_AUTOTEST_HPP
#define JEB_TEST_AUTOTEST_HPP

#include <functional>
#include <string>

namespace JEB { namespace Test {

class AutoTest
{
public:
    typedef std::function<void()> Func;

    AutoTest(const std::string& fileName, Func suiteFunc);
    AutoTest(const std::string& fileName, Func suiteFunc, int priority);

    const Func& function() const;
    void setFunction(const Func& function);

    std::string name() const;

    int priority() const;
private:
    Func m_Function;
    std::string m_Name;
    int m_Priority;
};

}}

#endif
