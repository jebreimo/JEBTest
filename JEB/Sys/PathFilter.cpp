/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "PathFilter.hpp"
#include <cassert>
#include "JEB/Algorithms/Algorithms.hpp"

namespace JEB { namespace Sys {

namespace
{
    bool containsName(const std::vector<std::string>& current,
                      const std::string& name);
    bool updateFilter(const std::vector<std::string>& current,
                      const std::string& name,
                      std::vector<std::string>& next);
}

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

FilterState::FilterState(const std::string& name)
    : m_Name(name),
      m_Type(InclusiveFilter)
{}

FilterState FilterState::descend(const std::string& name)
{
    FilterState nextState(name);
    bool exc = updateFilter(m_Exclude, name, nextState.m_Exclude);
    bool inc = updateFilter(m_Include, name, nextState.m_Include);
    if (exc != inc)
        nextState.m_Type = exc ? ExclusiveFilter : InclusiveFilter;
    else
        nextState.m_Type = m_Type;
    return nextState;
}

bool FilterState::shouldDescend(const std::string& name)
{
    bool inc = containsName(m_Include, name);
    bool exc = containsName(m_Exclude, name);
    if (inc)
        return true;
    else if (exc)
        return false;
    else
        return m_Type == InclusiveFilter;
}

void FilterState::excludePath(const std::string& path)
{
    m_Exclude.push_back(path);
}

void FilterState::includePath(const std::string& path)
{
    m_Include.push_back(path);
}

PathFilterType FilterState::type() const
{
    return m_Type;
}

void FilterState::setType(PathFilterType type)
{
    m_Type = type;
}

PathFilter::PathFilter()
    : m_States(1)
{}

PathFilter::~PathFilter()
{}

bool PathFilter::descend(const std::string& name)
{
    m_States.push_back(m_States.back().descend(name));
    return m_States.back().type() == InclusiveFilter;
}

bool PathFilter::shouldDescend(const std::string& name)
{
    return m_States.back().shouldDescend(name);
}

bool PathFilter::ascend()
{
    assert(m_States.size() > 1);
    m_States.pop_back();
    return m_States.back().type() == InclusiveFilter;
}

void PathFilter::excludePath(const std::string& path)
{
    m_States.front().excludePath(path);
}

void PathFilter::includePath(const std::string& path)
{
    m_States.front().includePath(path);
}

PathFilterType PathFilter::type() const
{
    return m_States.front().type();
}

void PathFilter::setType(PathFilterType type)
{
    m_States.front().setType(type);
}

namespace
{
    bool containsName(const std::vector<std::string>& current,
                      const std::string& name)
    {
        for (auto it = begin(current); it != end(current); ++it)
        {
            auto its = Algorithms::mismatch(begin(*it), end(*it),
                                            begin(name), end(name));
            if ((its.second == end(name)) &&
                (its.first == end(*it) || *its.first == '/'))
            {
                return true;
            }
        }
        return false;
    }

    bool updateFilter(const std::vector<std::string>& current,
                      const std::string& name,
                      std::vector<std::string>& next)
    {
        bool result = false;
        for (auto it = begin(current); it != end(current); ++it)
        {
            auto its = Algorithms::mismatch(begin(*it), end(*it),
                                            begin(name), end(name));
            if (its.second == end(name))
            {
                if (its.first == end(*it))
                    result = true;
                else if (*its.first == '/')
                    next.push_back(std::string(std::next(its.first), end(*it)));
            }
        }
        return result;
    }
}

}}
