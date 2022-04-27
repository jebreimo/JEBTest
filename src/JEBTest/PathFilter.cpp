//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "PathFilter.hpp"
#include <algorithm>
#include <cassert>
#include <utility>

namespace JEBTest
{
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
        explicit FilterState(std::string  name = {});

        FilterState descend(const std::string& name);
        bool shouldDescend(const std::string& name);

        void excludePath(std::string path);
        void includePath(std::string path);

        PathFilterType type() const;
        void setType(PathFilterType type);
    private:
        std::vector<std::string> m_Exclude;
        std::vector<std::string> m_Include;
        std::string m_Name;
        PathFilterType m_Type;
    };

    FilterState::FilterState(std::string  name)
        : m_Name(std::move(name)),
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

    void FilterState::excludePath(std::string path)
    {
        m_Exclude.push_back(move(path));
    }

    void FilterState::includePath(std::string path)
    {
        m_Include.push_back(move(path));
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

    PathFilter::~PathFilter() = default;

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

    void PathFilter::excludePath(std::string path)
    {
        m_States.front().excludePath(move(path));
    }

    void PathFilter::includePath(std::string path)
    {
        m_States.front().includePath(move(path));
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
                if (it->size() < name.size())
                    continue;
                auto its = mismatch(begin(name), end(name), begin(*it));
                if ((its.first == end(name)) &&
                    (its.second == end(*it) || *its.second == '/'))
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
                if (it->size() < name.size())
                    continue;
                auto its = mismatch(begin(name), end(name), begin(*it));
                if (its.first != end(name))
                    continue;
                if (its.second == end(*it))
                    result = true;
                else if (*its.second == '/')
                    next.emplace_back(std::next(its.second), end(*it));
            }
            return result;
        }
    }
}
