#ifndef JEB_TEST_MACROS_HPP
#define JEB_TEST_MACROS_HPP

#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>
#include "AutoSuite.hpp"
#include "Comparers.hpp"
#include "Exceptions.hpp"
#include "Formatters.hpp"
#include "MacroUtilities.hpp"
#include "Session.hpp"

#define JU_PRIV_UNIQUE_NAME_TRICK(a, b) a##b
#define JU_PRIV_UNIQUE_NAME(a, b) JU_PRIV_UNIQUE_NAME_TRICK(a, b)

#define JU_CONSOLE_BEGIN() \
    try {

#define JU_CONSOLE_END() \
    } catch (const std::exception& ex) { \
        ::JEB::Test::Session::instance().unhandledException(::JEB::Test::Error(__FILE__, __LINE__, std::string("Unhandled exception: \"") + ex.what() + "\"")); \
    } catch (...) { \
        ::JEB::Test::Session::instance().unhandledException(::JEB::Test::Error(__FILE__, __LINE__, "Unknown exception")); \
    } \
    ::JEB::Test::Session::instance().print(""); \
    ::JEB::Test::Session::instance().writeReport(std::cout)

#define JU_CONSOLE_MAIN() \
    int main() \
    { \
        JU_CONSOLE_BEGIN(); \
        ::JEB::Test::AutoSuiteRunner::instance().run(); \
        JU_CONSOLE_END(); \
        return ::JEB::Test::Session::instance().numberOfFailedSuites(); \
    }

#define JU_TESTSUITE(...) \
    static void JU_PRIV_UNIQUE_NAME(JU_suite_, __LINE__)() \
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
    static ::JEB::Test::AutoSuite JU_PRIV_UNIQUE_NAME(JU_suite_instance_, __LINE__)(__FILE__, JU_PRIV_UNIQUE_NAME(JU_suite_, __LINE__))

#define JU_RUN_TESTSUITE(name, ...) \
    ::JEB::Test::Session::instance().beginSuite( \
            ::JEB::Test::extractSuiteName(#name)); \
    try { \
        name(__VA_ARGS__); \
        ::JEB::Test::Session::instance().endSuite(); \
    } catch (const ::JEB::Test::TestSuiteFailure& ex) { \
        ::JEB::Test::Session::instance().suiteFailed(ex.error()); \
    }

#define JU_RUN_TEST(name, ...) \
    ::JEB::Test::Session::instance().beginTest( \
            ::JEB::Test::extractTestName(#name)); \
    try { \
        name(__VA_ARGS__); \
        ::JEB::Test::Session::instance().endTest(); \
    } catch (const ::JEB::Test::TestFailure& ex) { \
        ::JEB::Test::Session::instance().testFailed(ex.error()); \
    }

#define JU_THROWS(expr, exception) \
    try { \
        expr; \
        throw ::JEB::Test::TestFailure(__FILE__, __LINE__, #expr " didn't throw exception \"" #exception "\""); \
    } catch (const exception&) { \
        ::JEB::Test::Session::instance().assertPassed(); \
    }

#define JU_IMPL_ASSERT(cond, file, line, msg) \
    { \
        if (cond) { \
            ::JEB::Test::Session::instance().assertPassed(); \
        } else { \
            throw ::JEB::Test::TestFailure(file, line, msg); \
        } \
    }

#define JU_ASSERT(cond) \
    JU_IMPL_ASSERT((cond), __FILE__, __LINE__, "Assertion failed: " #cond)

#define JU_ASSERT_MSG(cond, msg) \
    { \
        if (cond) { \
            ::JEB::Test::Session::instance().assertPassed(); \
        } else { \
            std::ostringstream JU_os; \
            JU_os << "Assertion failed: " #cond ". " << msg; \
            throw ::JEB::Test::TestFailure(__FILE__, __LINE__, JU_os.str()); \
        } \
    }

#define JU_EQUAL(a, b) \
    JU_IMPL_ASSERT(::JEB::Test::compare((a), (b)), __FILE__, __LINE__, \
                   ::JEB::Test::formatComparison((a), #a, (b), #b, "!="))

#define JU_EQUAL_REALS(a, b, epsilon) \
    JU_IMPL_ASSERT(::JEB::Test::compareReals((a), (b), (epsilon)), __FILE__, __LINE__, \
                   ::JEB::Test::formatComparison((a), #a, (b), #b, "!="))

#define JU_UNEQUAL(a, b) \
    JU_IMPL_ASSERT(!::JEB::Test::compare((a), (b)), __FILE__, __LINE__, \
                   ::JEB::Test::formatComparison((a), #a, (b), #b, "=="))

#define JU_FAIL(msg) \
    throw ::JEB::Test::TestFailure(__FILE__, __LINE__, msg)

#define JU_FAIL_TESTSUITE(msg) \
    throw ::JEB::Test::TestSuiteFailure(__FILE__, __LINE__, msg)

#endif
