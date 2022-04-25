//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "JEBTest/AutoTest.hpp"

#include <limits>
#include <utility>
#include "Ystring/Algorithms.hpp"
#include "JEBTest/AutoTestRunner.hpp"

namespace JEBTest
{
    using namespace ystring;

    namespace
    {
        const char32_t PATH_SEPARATORS[] = {'/', '\\'};

        std::string extractSuiteName(const std::string& path)
        {
            auto parts = ystring::split(path, PATH_SEPARATORS);
            auto parts2 = ystring::split(parts.back(), ".");
            return std::string(parts2.front());
        }

        std::vector<std::string> splitPath(const std::string& path)
        {
            if (path.empty())
                return {};

            std::vector<std::string> result;
            for (const auto part: ystring::split(path, PATH_SEPARATORS))
                result.emplace_back(part);
            return result;
        }
    }

    AutoTest::AutoTest(std::string fileName, Func func,
                       const std::string& path) noexcept
        : m_Function(std::move(func)),
          m_Name(std::move(fileName)),
          m_Path(splitPath(path)),
          m_Priority(std::numeric_limits<int>::max())
    {
        AutoTestRunner::instance().addTest(this);
    }

    AutoTest::AutoTest(std::string fileName, Func func,
                       const std::string& path, int priority) noexcept
        : m_Function(std::move(func)),
          m_Name(std::move(fileName)),
          m_Path(splitPath(path)),
          m_Priority(priority)
    {
        AutoTestRunner::instance().addTest(this);
    }

    AutoTest::~AutoTest() = default;

    const AutoTest::Func& AutoTest::function() const
    {
        return m_Function;
    }

    void AutoTest::setFunction(const Func& function)
    {
        m_Function = function;
    }

    std::string AutoTest::name() const
    {
        return extractSuiteName(m_Name);
    }

    const std::vector<std::string>& AutoTest::path() const
    {
        return m_Path;
    }

    int AutoTest::priority() const
    {
        return m_Priority;
    }
}
