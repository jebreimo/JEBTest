/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBTEST_JEBTEST_HPP
#define JEBTEST_JEBTEST_HPP

#ifdef _WIN32
  #ifdef NDEBUG
    #pragma comment (lib, "JEBTest.lib")
  #else
    #pragma comment (lib, "JEBTest.debug.lib")
  #endif
#endif

#include "Test/AutoTest.hpp"
#include "Test/AutoTestRunner.hpp"
#include "Test/Macros.hpp"
#include "Test/Session.hpp"

#endif
