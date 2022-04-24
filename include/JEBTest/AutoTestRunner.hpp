//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <vector>

namespace JEBTest
{
    class AutoTest;

    class AutoTestRunner
    {
    public:
        static AutoTestRunner& instance();

        void addTest(const AutoTest* suite);
        void run();
    private:
        AutoTestRunner();

        std::vector<const AutoTest*> m_Tests;
    };
}
