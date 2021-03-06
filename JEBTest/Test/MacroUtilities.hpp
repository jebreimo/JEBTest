/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBTEST_TEST_MACROUTILITIES_HPP
#define JEBTEST_TEST_MACROUTILITIES_HPP

#include <functional>

namespace JEBTest {

void runTests(const char* file, int line, const char* testNamesString,
              std::function<void()>* testFuncs, size_t testFuncSize);

template <size_t N>
void runTests(const char* file, int line, const char* testNamesString,
              std::function<void()> (&testFuncs)[N])
{
    runTests(file, line, testNamesString, testFuncs, N);
}

}

#endif
