/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_TEST_MACROS_HPP
#define JEB_TEST_MACROS_HPP

#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>
#include "AutoTest.hpp"
#include "Comparers.hpp"
#include "Exceptions.hpp"
#include "Formatters.hpp"
#include "MacroUtilities.hpp"
#include "Report.hpp"
#include "Session.hpp"

/** @file
 *  @brief Defines all macros for tests, test suites and test setup.
 *
 *  The macros in this file fall in following categories:
 *  - macros for defining the main function and executing all test suites
 *  - macros for defining test suites and adding and executing tests
 *  - macros for doing the actual testing, e.g. JT_ASSERT and JT_EQUAL
 */

/** @brief Internal macro. Used by other macros to create unique variable names.
 */
#define JT_PRIV_UNIQUE_NAME_TRICK(a, b) a##b
/** @brief Internal macro. Used by other macros to create unique variable names.
 */
#define JT_PRIV_UNIQUE_NAME(a, b) JT_PRIV_UNIQUE_NAME_TRICK(a, b)

/** @brief Starts a scope for running tests and test suites.
 *
 *  All reports and messages are written to the console (command line window)
 */
#define JT_CONSOLE_BEGIN() \
    try {

/** @brief Ends a scope for running tests and test suites.
 *
 *  All reports and messages are written to the console (command line window)
 */
#define JT_CONSOLE_END() \
    } catch (const std::exception& ex) { \
        ::JEB::Test::Session::instance().unhandledException(::JEB::Test::Error(__FILE__, __LINE__, std::string("Unhandled exception: \"") + ex.what() + "\"")); \
    } catch (...) { \
        ::JEB::Test::Session::instance().unhandledException(::JEB::Test::Error(__FILE__, __LINE__, "Unknown exception")); \
    } \
    ::JEB::Test::Session::instance().print(""); \
    ::JEB::Test::Session::instance()::writeReports()

/** @brief Creates a main function for console programs that run test suites.
 *
 *  The created main function will run all tests in all test suites defined
 *  with the JT_TESTSUITE macro or added explicitly with a AutoTest variable.
 *
 *  All reports and messages are written to the console (command line window)
 */
#define JT_CONSOLE_MAIN() \
    int main() \
    { \
        try \
        { \
            JT_CONSOLE_BEGIN(); \
            ::JEB::Test::AutoTestRunner::instance().run(); \
            JT_CONSOLE_END(); \
        } \
        catch (std::exception& ex) \
        { \
            std::cerr << "EXCEPTION: " << ex.what() << std::endl; \
        } \
        return (int)::JEB::Test::Session::instance().numberOfFailedTests(); \
    }

/** @brief Defines a test suite.
 *
 *  The arguments to this macro are the function names of the test functions.
 *  The test functions are executed in the order they are given.
 *  There are no restrictions to how many functions that can be added.
 *
 *  The test suite's name in reports will be the current file name.
 */
#define JT_TESTSUITE(...) \
    static void JT_PRIV_UNIQUE_NAME(JT_suite_, __LINE__)() \
    { \
        void (*tests[])() = {__VA_ARGS__}; \
        std::vector<std::string> testNames = ::JEB::Test::extractTestNames(#__VA_ARGS__); \
        for (size_t i = 0; i < testNames.size(); i++) \
        { \
            ::JEB::Test::Session::instance().beginTest(testNames[i]); \
            try { \
                tests[i](); \
                ::JEB::Test::Session::instance().endTest(); \
            } catch (const ::JEB::Test::TestFailure& ex) { \
                ::JEB::Test::Session::instance().testFailed(ex.error()); \
                break; \
            } \
        } \
    } \
    static ::JEB::Test::AutoTest JT_PRIV_UNIQUE_NAME(JT_suite_instance_, __LINE__)(__FILE__, JT_PRIV_UNIQUE_NAME(JT_suite_, __LINE__))

/** @brief Macro for explicitly running a test suite with arguments.
 *
 *  Normally you'll just use JT_TESTSUITE to define your test suite, but
 *  if your tests need a common set of data, for instance the contents of a
 *  file, it may make sense to create a "test suite function" that reads the
 *  file first, then run each test function with the contents of that file
 *  as input arguments. This function simplifies executing such a function.
 *
 *  @param name the name of the test suite function
 *  @param ... comma separated arguments that will be passed on to @a name.
 *
 *  Examples
 *  --------
 *  Execute a test suite function named testsuite_Shapes that takes no
 *  arguments:
 *
 *      void testsuite_Shapes() {...}
 *
 *      JT_RUN_TESTSUITE(testsuite_Shapes);
 *
 *  Execute a test suite function named testsuite_SvgShapes that takes a file
 *  name as argument:
 *
 *      void testsuite_SvgShapes(std::string fileName) {...}
 *
 *      JT_RUN_TESTSUITE(testsuite_SvgShapes, "my_svg_file.svg");
 */
// #define JT_RUN_TESTSUITE(name, ...) \
//     if (::JEB::Test::Session::instance().isTestEnabled(#name)) \
//     { \
//         ::JEB::Test::Session::instance().beginTest( \
//                 ::JEB::Test::extractSuiteName(#name)); \
//         try { \
//             name(__VA_ARGS__); \
//             ::JEB::Test::Session::instance().endTest(); \
//         } catch (const ::JEB::Test::TestSuiteFailure& ex) { \
//             ::JEB::Test::Session::instance().suiteFailed(ex.error()); \
//         } \
//     }

/** @brief Macro for explcitly running a test with arguments.
 */
#define JT_RUN_TEST(name, ...) \
    if (::JEB::Test::Session::instance().isTestEnabled(#name)) \
    { \
        ::JEB::Test::Session::instance().beginTest(#name); \
        try { \
            name(__VA_ARGS__); \
            ::JEB::Test::Session::instance().endTest(); \
        } catch (const ::JEB::Test::TestFailure& ex) { \
            ::JEB::Test::Session::instance().testFailed(ex.error()); \
        } \
    }

/** @brief Macro for verifying that an expression throws an exception.
 *
 *  The test fails if @a expr doesn't throw an exception of type @a exception.
 *
 *  @param expr the expression that will be executed, typically a function call
 *  @param exception the type name of the exception that @a expr is expected
 *      to throw
 */
#define JT_THROWS(expr, exception) \
    try { \
        expr; \
        throw ::JEB::Test::TestFailure(__FILE__, __LINE__, #expr " didn't throw exception \"" #exception "\""); \
    } catch (const exception&) { \
        ::JEB::Test::Session::instance().assertPassed(); \
    }

/** @brief Internal macro. Used by other assert macros.
 */
#define JT_IMPL_ASSERT(cond, file, line, msg) \
    { \
        if (cond) { \
            ::JEB::Test::Session::instance().assertPassed(); \
        } else { \
            throw ::JEB::Test::TestFailure(file, line, msg); \
        } \
    }

/** @brief Verifies that condition @a cond is true.
 *
 *  The test fails if @a cond is false.
 */
#define JT_ASSERT(cond) \
    JT_IMPL_ASSERT((cond), __FILE__, __LINE__, "Assertion failed: " #cond)

/** @brief Verifies that condition @a cond is true.
 *
 *  Use this macro to provide extra information about the condition if it
 *  fails.
 *
 *  @param cond the condition
 *  @param msg a string that that will be include in the test report if
 *      @a cond is false.
 */
#define JT_ASSERT_MSG(cond, msg) \
    { \
        if (cond) { \
            ::JEB::Test::Session::instance().assertPassed(); \
        } else { \
            std::ostringstream JT_os; \
            JT_os << "Assertion failed: " #cond ". " << msg; \
            throw ::JEB::Test::TestFailure(__FILE__, __LINE__, JT_os.str()); \
        } \
    }

/** @brief Verifies that @a a equals @a b.
 *
 *  Requirements for a and b:
 *  - there must be an equality operator (==) that accepts @a a and @a b as
 *    left and right hand arguments respectively.
 *  - there must be an iostream output operator (<<) that accepts @a a.
 *  - if @a b is not of the same type as @a a, there must also be an iostream
 *    output operator that accepts @a b.
 */
#define JT_EQUAL(a, b) \
    JT_IMPL_ASSERT(::JEB::Test::compare((a), (b)), __FILE__, __LINE__, \
                   ::JEB::Test::formatComparison((a), #a, (b), #b, "!="))

/** @brief Verifies that real number @a a is sufficiently close to @a b.
 */
#define JT_EQUAL_REALS(a, b, epsilon) \
    JT_IMPL_ASSERT(::JEB::Test::compareReals((a), (b), (epsilon)), __FILE__, __LINE__, \
                   ::JEB::Test::formatComparison((a), #a, (b), #b, "!="))

/** @brief Verifies that @a a is not equal to @a b.
 *
 *  Requirements to @a a and @a b are the same as in JT_EQUAL.
 */
#define JT_UNEQUAL(a, b) \
    JT_IMPL_ASSERT(!::JEB::Test::compare((a), (b)), __FILE__, __LINE__, \
                   ::JEB::Test::formatComparison((a), #a, (b), #b, "=="))

/** @brief Force a test failure with the given error message.
 */
#define JT_FAIL(msg) \
    throw ::JEB::Test::TestFailure(__FILE__, __LINE__, msg)

/** @brief Force a test suite failure with the given error message.
 */
// #define JT_FAIL_TESTSUITE(msg) \
//     throw ::JEB::Test::TestSuiteFailure(__FILE__, __LINE__, msg)

/** @brief Provide extra information when calling a function from within a test.
 *
 *  If a test function calls another function that uses JT-macros to test
 *  various conditions, surround the calls to the other function with this
 *  macro to include call stack information in the test report.
 *
 *  To reduce code duplication it often makes sense to place the different
 *  assert macros in a function that is called from the actual test function.
 *  The test report will in such cases only contain the line number of the
 *  assert that failed, which may not provide much information if this
 *  assertion is executed many times. This macro helps solving that problem.
 */
#define JT_SUB(expr) \
    try \
    { \
        expr; \
    } \
    catch (::JEB::Test::TestFailure& ex) \
    { \
        ex.addContext(__FILE__, __LINE__, #expr); \
        throw ex; \
    }

#endif
