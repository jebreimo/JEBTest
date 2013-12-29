#ifndef JEB_INTERVAL_HPP
#define JEB_INTERVAL_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>
#include "JEB/Algorithms/Algorithms.hpp"
#include "JEB/Math/Limits.hpp"

namespace JEB { namespace Interval {

static const double MinimumGapSize = 0.000001;

template <typename T>
struct DefaultPolicy
{
    static bool inside(const std::pair<T, T>& interval, T value)
    {
        return false;
    }

    static bool adjacent(T intervalEnd, T intervalStart)
    {
        return next(intervalEnd) == intervalStart;
    }

    static T next(T intervalEnd, T stepSize = 1)
    {
        return intervalEnd;
    }

    static T previous(T intervalStart, T stepSize = 1)
    {
        return intervalStart;
    }
};

template <typename T>
struct Exclusive : public DefaultPolicy<T>
{
    static bool inside(const std::pair<T, T>& interval, T value)
    {
        return interval.first < value && value < interval.second;
    }
};

template <typename T>
struct LeftInclusive : public DefaultPolicy<T>
{
    static bool inside(const std::pair<T, T>& interval, T value)
    {
        return interval.first <= value && value < interval.second;
    }

    static T previous(T intervalStart, T stepSize = 1)
    {
        return static_cast<T>(intervalStart - stepSize);
    }
};

template <typename T>
struct RightInclusive : public DefaultPolicy<T>
{
    static bool inside(const std::pair<T, T>& interval, T value)
    {
        return interval.first < value && value <= interval.second;
    }

    static T next(T intervalEnd, T stepSize = 1)
    {
        return static_cast<T>(intervalEnd + stepSize);
    }
};

template <typename T>
struct Inclusive
{
    static bool inside(const std::pair<T, T>& interval, T value)
    {
        return interval.first <= value && value <= interval.second;
    }

    static bool adjacent(T intervalEnd, T intervalStart)
    {
        return next(intervalEnd) == intervalStart;
    }

    static T next(T intervalEnd, T stepSize = 1)
    {
        return static_cast<T>(intervalEnd + stepSize);
    }

    static T previous(T intervalStart, T stepSize = 1)
    {
        return static_cast<T>(intervalStart - stepSize);
    }
};

class TolerantLeftInclusive
{
public:
    TolerantLeftInclusive(double mimiumGapSize = MinimumGapSize)
        : m_MinimumGapSize(mimiumGapSize)
    {}

    static bool inside(const std::pair<double, double>& interval, double value)
    {
        return interval.first <= value && value < interval.second;
    }

    bool adjacent(double intervalEnd, double intervalStart)
    {
        double gap = intervalStart - intervalEnd;
        return 0 <= gap && gap < m_MinimumGapSize;
    }

    static double next(double intervalEnd)
    {
        return intervalEnd;
    }

private:
    double m_MinimumGapSize;
};

template <typename T>
bool valid(const std::pair<T, T>& interval)
{
    return interval.first <= interval.second;
}

template <typename T, typename Policy>
static bool inside(const std::pair<T, T>& interval, T value, Policy policy)
{
    return policy.inside(interval, value);
}

template <typename T, typename Policy>
bool contiguous(const std::pair<T, T>& r1, const std::pair<T, T>& r2, Policy policy)
{
    return policy.adjacent(r2.second, r1.first) ||
           policy.adjacent(r1.second, r2.first);
}

template <typename T, typename Policy>
bool overlaps(const std::pair<T, T>& r1, const std::pair<T, T>& r2, Policy policy)
{
    return policy.inside(r1, r2.first) || policy.inside(r2, r1.first);
}

template <typename T, typename Policy>
bool continuous(const std::pair<T, T>& r1, const std::pair<T, T>& r2, Policy policy)
{
    return overlaps<T, Policy>(r1, r2, policy) ||
           contiguous<T, Policy>(r1, r2, policy);
}

template <typename T, typename Policy>
T next(const std::pair<T, T>& interval, Policy policy, T stepSize = 1)
{
    assert(valid(interval));
    return policy.next(interval.second, stepSize);
}

template <typename T, typename Policy>
T previous(const std::pair<T, T>& interval, Policy policy, T stepSize = 1)
{
    assert(valid(interval));
    return policy.previous(interval.first, stepSize);
}

template <typename T, typename Policy>
bool subInterval(const std::pair<T, T>& interval, const std::pair<T, T>& sub, Policy policy)
{
    return interval.first <= sub.first && sub.second <= interval.second;
}

template <typename T>
std::pair<T, T> add(const std::pair<T, T>& interval, const T& value, Inclusive<T> policy)
{
    assert(valid(interval));
    if (policy.adjacent(value, interval.first))
        return std::make_pair(value, interval.second);
    else if (policy.adjacent(interval.second, value))
        return std::make_pair(interval.first, value);
    else
        return interval;
}

template <typename T, typename Policy>
std::pair<T, T> join(const std::pair<T, T>& r1, const std::pair<T, T>& r2, Policy policy)
{
    assert(valid(r1) && valid(r2));
    if (continuous<T, Policy>(r1, r2, policy))
        return std::make_pair(std::min(r1.first, r2.first),
                              std::max(r1.second, r2.second));
    else
        return r1;
}

template <typename T, typename Policy>
T size(const std::pair<T, T>& interval, Policy policy)
{
    assert(valid(interval));
    return JEB::Interval::next(interval, policy) - interval.first;
}

template <typename T>
std::pair<T, T> maxInterval()
{
    return std::make_pair(Limits::min<T>(), Limits::max<T>());
}

template <typename T>
bool inside(const std::pair<T, T>& interval, T value)
{
    return inside(interval, value, LeftInclusive<T>());
}

template <typename T>
bool contiguous(const std::pair<T, T>& r1, const std::pair<T, T>& r2)
{
    return contiguous(r1, r2, LeftInclusive<T>());
}

template <typename T>
bool overlaps(const std::pair<T, T>& r1, const std::pair<T, T>& r2)
{
    return overlaps(r1, r2, LeftInclusive<T>());
}

template <typename T>
bool continuous(const std::pair<T, T>& r1, const std::pair<T, T>& r2)
{
    return continuous(r1, r2, LeftInclusive<T>());
}

template <typename T>
bool subInterval(const std::pair<T, T>& interval, const std::pair<T, T>& sub)
{
    return subInterval(interval, sub, LeftInclusive<T>());
}

template <typename T>
std::pair<T, T> add(const std::pair<T, T>& interval, const T& value)
{
    return add(interval, value, LeftInclusive<T>());
}

template <typename T>
std::pair<T, T> join(const std::pair<T, T>& r1, const std::pair<T, T>& r2)
{
    return join(r1, r2, LeftInclusive<T>());
}

template <typename T>
T size(const std::pair<T, T>& interval)
{
    return size(interval, LeftInclusive<T>());
}

template <typename RandIt, typename T, typename Policy>
std::pair<RandIt, RandIt> findInterval(RandIt beg, RandIt end,
                                       const std::pair<T, T>& interval,
                                       Policy)
{
    RandIt rbeg = Algorithms::upper_bound(
            beg, end,
            interval.first,
            [](const std::pair<T, T>& p){return p.second;});
    RandIt rend = Algorithms::lower_bound(
            rbeg, end,
            interval.second,
            [](const std::pair<T, T>& p){return p.first;});
    return std::make_pair(rbeg, rend);
}

template <typename RandIt, typename T>
std::pair<RandIt, RandIt> findInterval(RandIt beg, RandIt end,
                                       const std::pair<T, T>& interval,
                                       Inclusive<T>)
{
    RandIt rbeg = Algorithms::lower_bound(
            beg, end,
            interval.first,
            [](const std::pair<T, T>& p){return p.second;});
    RandIt rend = Algorithms::upper_bound(
            rbeg, end,
            interval.second,
            [](const std::pair<T, T>& p){return p.first;});
    return std::make_pair(rbeg, rend);
}

template <typename RandIt, typename OutIt, typename T, typename Policy>
OutIt intersection(RandIt beg, RandIt end,
                   OutIt out,
                   const std::pair<T, T>& interval,
                   Policy policy)
{
    std::pair<RandIt, RandIt> its = findInterval(beg, end, interval, policy);
    if (its.first == its.second)
        return out;

    if (its.first->first < interval.first)
        *out++ = std::make_pair(std::max(its.first->first, interval.first),
                                std::min(its.first->second, interval.second));
    while (++its.first != its.second && its.first->second <= interval.second)
        *out++ = *its.first;
    if (its.first != its.second && interval.second < its.first->second)
        *out++ = std::make_pair(its.first->first, interval.second);

    return out;
}

template <typename T>
bool equivalent(const std::pair<T, T>& a, const std::pair<T, T>& b, T tolerance)
{
    return std::abs(a.first - b.first) <= tolerance &&
            std::abs(a.second - b.second) <= tolerance;
}

template <typename T>
class Equivalent
{
public:
    typedef std::pair<T, T> interval;
    Equivalent(T tolerance) : m_Tolerance(tolerance) {}
    bool operator()(const std::pair<T, T>& a, const std::pair<T, T>& b)
    {
        return equivalentent(a, b,  m_Tolerance);
    }
private:
    T m_Tolerance;
};

}}

#endif
