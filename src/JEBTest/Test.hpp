//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <ctime>
#include <memory>
#include <string>
#include "JEBTest/Error.hpp"

namespace JEBTest
{
    typedef std::shared_ptr<class Test> TestPtr;

    class Test
    {
    public:
        explicit Test(std::string name);

        [[nodiscard]] size_t assertions() const;
        void incrementAssertions();

        /** @brief Returns the depth of the test hierarchy this test is the
          *     root of.
          *
          * @returns 1 + the maximum depth of its children.
          */
        [[nodiscard]] size_t depth() const;

        [[nodiscard]] const std::vector<Error>& errors() const;
        void addError(const Error& error);
        void addError(Error&& error);

        /** @brief Returns true if the test failed (i.e. error() is set).
          */
        [[nodiscard]] bool failed() const;

        /** @brief Returns true if the test or any of its sub-tests failed.
          */
        [[nodiscard]] bool failedHierarchy() const;

        [[nodiscard]] const std::string& name() const;

        [[nodiscard]] clock_t startTime() const;
        void setStartTime(clock_t startTime);

        [[nodiscard]] clock_t endTime() const;
        void setEndTime(clock_t endTime);

        [[nodiscard]] double elapsedTime() const;

        void addTest(const TestPtr& test);
        std::vector<TestPtr>& tests();
        [[nodiscard]] const std::vector<TestPtr>& tests() const;
        [[nodiscard]] TestPtr findTest(const std::string& name) const;
    private:
        size_t m_Assertions;
        std::vector<Error> m_Errors;
        std::string m_Name;
        clock_t m_StartTime;
        clock_t m_EndTime;
        std::vector<TestPtr> m_Tests;
        std::vector<std::pair<std::string, std::string>> m_Filter;
    };
}
