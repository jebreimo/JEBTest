/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBTEST_TEST_AUTOTESTRUNNER_HPP
#define JEBTEST_TEST_AUTOTESTRUNNER_HPP

#include <vector>

namespace JEBTest {

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

}

#endif
