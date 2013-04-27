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

#define JT_PRIV_UNIQUE_NAME_TRICK(a, b) a##b
#define JT_PRIV_UNIQUE_NAME(a, b) JT_PRIV_UNIQUE_NAME_TRICK(a, b)

#define JT_CONSOLE_BEGIN() \
    try {

#define JT_CONSOLE_END() \
    } catch (const std::exception& ex) { \
        ::JEB::Test::Session::instance().unhandledException(::JEB::Test::Error(__FILE__, __LINE__, std::string("Unhandled exception: \"") + ex.what() + "\"")); \
    } catch (...) { \
        ::JEB::Test::Session::instance().unhandledException(::JEB::Test::Error(__FILE__, __LINE__, "Unknown exception")); \
    } \
    ::JEB::Test::Session::instance().print(""); \
    ::JEB::Test::Session::instance().writeReport(std::cout)

#define JT_CONSOLE_MAIN() \
    int main() \
    { \
        JT_CONSOLE_BEGIN(); \
        ::JEB::Test::AutoSuiteRunner::instance().run(); \
        JT_CONSOLE_END(); \
        return (int)::JEB::Test::Session::instance().numberOfFailedSuites(); \
    }

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
    static ::JEB::Test::AutoSuite JT_PRIV_UNIQUE_NAME(JT_suite_instance_, __LINE__)(__FILE__, JT_PRIV_UNIQUE_NAME(JT_suite_, __LINE__))

#define JT_RUN_TESTSUITE(name, ...) \
    ::JEB::Test::Session::instance().beginSuite( \
            ::JEB::Test::extractSuiteName(#name)); \
    try { \
        name(__VA_ARGS__); \
        ::JEB::Test::Session::instance().endSuite(); \
    } catch (const ::JEB::Test::TestSuiteFailure& ex) { \
        ::JEB::Test::Session::instance().suiteFailed(ex.error()); \
    }

#define JT_RUN_TEST(name, ...) \
    ::JEB::Test::Session::instance().beginTest( \
            ::JEB::Test::extractTestName(#name)); \
    try { \
        name(__VA_ARGS__); \
        ::JEB::Test::Session::instance().endTest(); \
    } catch (const ::JEB::Test::TestFailure& ex) { \
        ::JEB::Test::Session::instance().testFailed(ex.error()); \
    }

#define JT_THROWS(expr, exception) \
    try { \
        expr; \
        throw ::JEB::Test::TestFailure(__FILE__, __LINE__, #expr " didn't throw exception \"" #exception "\""); \
    } catch (const exception&) { \
        ::JEB::Test::Session::instance().assertPassed(); \
    }

#define JT_IMPL_ASSERT(cond, file, line, msg) \
    { \
        if (cond) { \
            ::JEB::Test::Session::instance().assertPassed(); \
        } else { \
            throw ::JEB::Test::TestFailure(file, line, msg); \
        } \
    }

#define JT_ASSERT(cond) \
    JT_IMPL_ASSERT((cond), __FILE__, __LINE__, "Assertion failed: " #cond)

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

#define JT_EQUAL(a, b) \
    JT_IMPL_ASSERT(::JEB::Test::compare((a), (b)), __FILE__, __LINE__, \
                   ::JEB::Test::formatComparison((a), #a, (b), #b, "!="))

#define JT_EQUAL_REALS(a, b, epsilon) \
    JT_IMPL_ASSERT(::JEB::Test::compareReals((a), (b), (epsilon)), __FILE__, __LINE__, \
                   ::JEB::Test::formatComparison((a), #a, (b), #b, "!="))

#define JT_UNEQUAL(a, b) \
    JT_IMPL_ASSERT(!::JEB::Test::compare((a), (b)), __FILE__, __LINE__, \
                   ::JEB::Test::formatComparison((a), #a, (b), #b, "=="))

#define JT_FAIL(msg) \
    throw ::JEB::Test::TestFailure(__FILE__, __LINE__, msg)

#define JT_FAIL_TESTSUITE(msg) \
    throw ::JEB::Test::TestSuiteFailure(__FILE__, __LINE__, msg)

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
