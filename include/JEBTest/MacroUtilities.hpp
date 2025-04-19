//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <functional>

namespace JEBTest
{
    void runTests(const char* file, int line, const char* testNamesString,
                  std::function<void()>* testFuncs, size_t testFuncSize);

    template <size_t N>
    void runTests(const char* file, int line, const char* testNamesString,
                  std::function<void()> (&testFuncs)[N])
    {
        runTests(file, line, testNamesString, testFuncs, N);
    }
}
