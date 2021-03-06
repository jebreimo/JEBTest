/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "MacroUtilities.hpp"

#include <algorithm>
#include <cassert>
#include "JEBString/JEBUtf8.hpp"

#include "Exceptions.hpp"
#include "Session.hpp"
#include "TestScope.hpp"

namespace JEBTest {

using namespace JEBTest_JEBString;

namespace
{
    std::vector<std::string> extractTestNames(const std::string& names)
    {
        auto result = Utf8::split(names, ",", 0, SplitFlags::IgnoreEmpty);
        for (auto it = result.begin(); it != result.end(); ++it)
          *it = Utf8::trim(*it);
        return result;
    }
}

void runTests(const char* file, int line, const char* testNamesString,
              std::function<void()>* testFuncs, size_t testFuncsSize)
{
    std::vector<std::string> testNames = extractTestNames(testNamesString);
    assert(testNames.size() == testFuncsSize);
    for (size_t i = 0; i < testNames.size(); i++)
    {
        if (Session::instance().isTestEnabled(testNames[i]))
        {
            TestScope scope(testNames[i]);
            try
            {
                testFuncs[i]();
            }
            catch (const AbstractFailure& ex)
            {
                Session::instance().testFailed(ex.error());
                if (ex.error().type() != Error::Failure)
                    throw;
            }
            catch (const std::exception& ex)
            {
                Session::instance().testFailed(Error(file, line,
                    std::string("Unhandled exception: \"") + ex.what() + "\"",
                    Error::UnhandledException));
                throw;
            }
            catch (...)
            {
                Session::instance().testFailed(Error(file, line,
                    "Unhandled exception (not derived from std::exception)",
                    Error::UnhandledException));
                throw;
            }
        }
    }
}

}
