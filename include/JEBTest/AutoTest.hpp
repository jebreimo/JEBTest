//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <functional>
#include <string>
#include <vector>

namespace JEBTest
{
    class AutoTest
    {
    public:
        typedef std::function<void()> Func;

        AutoTest(std::string fileName, Func func,
                 const std::string& path = {}) noexcept;

        AutoTest(std::string fileName, Func func,
                 const std::string& path, int priority) noexcept;

        ~AutoTest();

        const Func& function() const;

        void setFunction(const Func& function);

        std::string name() const;

        const std::vector<std::string>& path() const;

        int priority() const;
    private:
        Func m_Function;
        std::string m_Name;
        std::vector<std::string> m_Path;
        int m_Priority;
    };
}
