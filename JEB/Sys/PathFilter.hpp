/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_PATHFILTER_HPP
#define JEB_PATHFILTER_HPP

#include <string>
#include <vector>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Sys {

enum PathFilterType
{
    ExclusiveFilter,
    InclusiveFilter
};

class FilterState
{
public:
    FilterState(const std::string& name = std::string());

    FilterState descend(const std::string& name);
    bool shouldDescend(const std::string& name);

    void excludePath(const std::string& path);
    void includePath(const std::string& path);

    PathFilterType type() const;
    void setType(PathFilterType type);
private:
    std::vector<std::string> m_Exclude;
    std::vector<std::string> m_Include;
    std::string m_Name;
    PathFilterType m_Type;
};

class PathFilter
{
public:
    PathFilter();

    bool descend(const std::string& name);
    bool shouldDescend(const std::string& name);
    bool ascend();

    void excludePath(const std::string& path);
    void includePath(const std::string& path);

    PathFilterType type() const;
    void setType(PathFilterType type);
private:
    std::vector<FilterState> m_States;
};

}}

#endif
