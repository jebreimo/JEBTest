//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-12.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "AutoTestRunner.hpp"
#include "Macros.hpp"

int main(int argc, char* argv[])
{
    return JEBTest::runAllTests(argc, argv);
}
