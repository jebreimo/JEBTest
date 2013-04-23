#include "CharRangeSet.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "JEB/Algorithms/Algorithms.hpp"
//#include "JEB/Collections/PairUtilities.hpp"
#include "EscapedString.hpp"

namespace JEB { namespace String { namespace Generic {

static Interval::Inclusive<uint32_t> INCLUSIVE;

CharRangeSet::CharRangeSet()
{}

CharRangeSet::CharRangeSet(CharRangeSet&& other)
{
    std::swap(m_Ranges, other.m_Ranges);
}

CharRangeSet::CharRangeSet(const CharRangeSet& other)
    : m_Ranges(other.m_Ranges)
{}

CharRangeSet& CharRangeSet::operator=(CharRangeSet&& other)
{
    std::swap(m_Ranges, other.m_Ranges);
    return *this;
}

CharRangeSet& CharRangeSet::operator=(const CharRangeSet& other)
{
    m_Ranges = other.m_Ranges;
    return *this;
}

void CharRangeSet::add(Char c)
{
    add(Range(c, c));
}

void CharRangeSet::add(const Range& range)
{
    typedef std::pair<std::vector<Range>::iterator,
                      std::vector<Range>::iterator> Its;
    Its its = Interval::findInterval(
            m_Ranges.begin(), m_Ranges.end(),
            std::make_pair(Interval::previous(range, INCLUSIVE),
                           Interval::next(range, INCLUSIVE)),
            INCLUSIVE);

    if (its.first == its.second)
    {
        m_Ranges.insert(its.first, range);
    }
    else
    {
        *its.first = Range(std::min(range.first, its.first->first),
                           std::max(range.second, (its.second - 1)->second));
        m_Ranges.erase(its.first + 1, its.second);
    }
}

void CharRangeSet::addAll()
{
    m_Ranges.clear();
    m_Ranges.push_back(Interval::maxInterval<Char>());
}

CharRangeSet CharRangeSet::complement() const
{
    Range remainder = Interval::maxInterval<Char>();
    CharRangeSet result;
    std::vector<Range>::const_iterator it;
    for (it = m_Ranges.begin(); it != m_Ranges.end(); it++)
    {
        if (it->first != remainder.first)
            result.m_Ranges.push_back(Range(remainder.first, it->first - 1));
        remainder.first = it->second + 1;
    }
    if (remainder.first <= remainder.second)
        result.m_Ranges.push_back(remainder);
    return result;
}

bool CharRangeSet::has(Char c) const
{
    return hasAll(Range(c, c));
}

bool CharRangeSet::hasAll(const Range& range) const
{
    std::vector<Range>::const_iterator it = JEB::Algorithms::lower_bound(
            m_Ranges.begin(), m_Ranges.end(),
            range.first,
            [](const Range& r){return r.second;});
    return it != m_Ranges.end() && subInterval(*it, range, INCLUSIVE);
}

bool CharRangeSet::hasAny(const Range& range) const
{
    std::vector<Range>::const_iterator it = JEB::Algorithms::lower_bound(
            m_Ranges.begin(), m_Ranges.end(),
            range.first,
            [](const Range& r){return r.second;});
    return it != m_Ranges.end() && overlaps(*it, range, INCLUSIVE);
}

size_t CharRangeSet::numberOfCharacters() const
{
    return std::accumulate(
            m_Ranges.begin(), m_Ranges.end(),
            (size_t)0,
            [](size_t s, const Range& r){return s + Interval::size(r, INCLUSIVE);});
}

size_t CharRangeSet::size() const
{
    return m_Ranges.size();
}

}}}
