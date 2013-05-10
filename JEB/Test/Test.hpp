/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_TEST_TEST_HPP
#define JEB_TEST_TEST_HPP

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

    const Error& error() const;
    void setError(const Error& error);

    bool failed() const;
    void setFailed(bool failed);

    const std::string& name() const;

    clock_t startTime() const;
    void setStartTime(clock_t startTime);

    clock_t endTime() const;
    void setEndTime(clock_t endTime);

    clock_t elapsedTime() const;

    void addTest(TestPtr test);
    std::vector<TestPtr>& tests();
    const std::vector<TestPtr>& tests() const;
private:
    size_t m_Assertions;
    Error m_Error;
    bool m_Failed;
    std::string m_Name;
    std::vector<TestPtr> m_Tests;
    clock_t m_StartTime;
    clock_t m_EndTime;
};

}}

#endif
