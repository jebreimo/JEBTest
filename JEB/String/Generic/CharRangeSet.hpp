#ifndef JEB_CHARRANGESET_HPP
#define JEB_CHARRANGESET_HPP

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include "JEB/Collections/Interval.hpp"
#include "EscapedString.hpp"

namespace JEB { namespace String { namespace Generic {

class CharRangeSet
{
public:
    typedef uint32_t Char;
    typedef std::pair<Char, Char> Range;

    CharRangeSet();
    CharRangeSet(CharRangeSet&& other);
    CharRangeSet(const CharRangeSet& other);

    CharRangeSet& operator=(CharRangeSet&& other);
    CharRangeSet& operator=(const CharRangeSet& other);

    template <typename StrFwdIt>
    static CharRangeSet parse(StrFwdIt beg, StrFwdIt end);

    void add(Char c);
    void add(const Range& range);
    void addAll();

    CharRangeSet complement() const;

    bool has(Char c) const;
    bool hasAll(const Range& range) const;
    bool hasAny(const Range& range) const;

    size_t numberOfCharacters() const;

    size_t size() const;
private:
    std::vector<Range> m_Ranges;
};

class CharRangeSetPredicate : public std::unary_function<uint32_t, bool>
{
public:
    CharRangeSetPredicate(const std::shared_ptr<CharRangeSet>& rangeSet)
        : m_RangeSet(rangeSet)
    {}

    ~CharRangeSetPredicate()
    {}

    bool operator()(uint32_t ch) const
    {
        return m_RangeSet->has(ch);
    }
private:
    std::shared_ptr<CharRangeSet> m_RangeSet;
};

template <typename StrFwdIt>
CharRangeSet CharRangeSet::parse(StrFwdIt beg, StrFwdIt end)
{
    enum State {ExpectFirst, ExpectDash, ExpectSecond};
    State state = ExpectFirst;
    CharRangeSet set;
    Range range;

    for (StrFwdIt it = beg; it != end;)
    {
        std::pair<uint32_t, bool> ch = unescapeNext(it, end);
        if (state == ExpectSecond)
        {
            range.second = ch.first;
            if (!Interval::valid(range))
                throw std::invalid_argument("Invalid range in expression.");
            set.add(range);
            state = ExpectFirst;
        }
        else if (ch.first == '-' && !ch.second && state == ExpectDash)
        {
            state = ExpectSecond;
        }
        else if (state == ExpectDash)
        {
            set.add(range.first);
            range.first = ch.first;
        }
        else
        {
            range.first = ch.first;
            state = ExpectDash;
        }
    }
    if (state == ExpectDash)
        set.add(range.first);
    return set;
}

}}}

#endif
