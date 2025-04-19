//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <string>
#include <vector>

namespace JEBTest
{
    enum PathFilterType
    {
        ExclusiveFilter,
        InclusiveFilter
    };

    class FilterState;

    class PathFilter
    {
    public:
        PathFilter();
        ~PathFilter();

        bool descend(const std::string& name);
        bool shouldDescend(const std::string& name);
        bool ascend();

        void excludePath(std::string path);
        void includePath(std::string path);

        [[nodiscard]] PathFilterType type() const;
        void setType(PathFilterType type);
    private:
        std::vector<FilterState> m_States;
    };
}
