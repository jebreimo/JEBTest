/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBTEST_TEST_TEST_HPP
#define JEBTEST_TEST_TEST_HPP

#include <ctime>
#include <memory>
#include <string>
#include "Error.hpp"

namespace JEB { namespace Test {

typedef std::shared_ptr<class Test> TestPtr;

class Test
{
public:
    Test(const std::string& name);

    size_t assertions() const;
    void incrementAssertions();

    /** @brief Returns the depth of the test hierarchy this test is the
      *     root of.
      *
      * @returns 1 + the maximum depth of its children.
      */
    size_t depth() const;

    const std::vector<Error>& errors() const;
    void addError(const Error& error);
    void addError(Error&& error);

    /** @brief Returns true if the test failed (i.e. error() is set).
      */
    bool failed() const;

    /** @brief Returns true if the test or any of its sub-tests failed.
      */
    bool failedHierarchy() const;

    const std::string& name() const;

    clock_t startTime() const;
    void setStartTime(clock_t startTime);

    clock_t endTime() const;
    void setEndTime(clock_t endTime);

    double elapsedTime() const;

    void addTest(TestPtr test);
    std::vector<TestPtr>& tests();
    const std::vector<TestPtr>& tests() const;
    TestPtr findTest(const std::string& name) const;
private:
    size_t m_Assertions;
    std::vector<Error> m_Errors;
    std::string m_Name;
    clock_t m_StartTime;
    clock_t m_EndTime;
    std::vector<TestPtr> m_Tests;
    std::vector<std::pair<std::string, std::string>> m_Filter;
};

}}

#endif
