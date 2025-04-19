//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "Session.hpp"

namespace JEBTest
{
    class TestScope
    {
    public:
        TestScope()
            : m_Count(0)
        {}

        explicit TestScope(const std::string& name)
            : m_Count(1)
        {
            Session::instance().beginTest(name);
        }

        ~TestScope()
        {
            while (m_Count--)
                Session::instance().endTest();
        }

        void push(const std::string& name, bool silent = false)
        {
            Session::instance().beginTest(name, silent);
            ++m_Count;
        }
    private:
        int m_Count;
    };
}
