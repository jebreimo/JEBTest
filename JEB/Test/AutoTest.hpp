/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
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
