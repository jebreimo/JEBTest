#ifndef JEB_IOMANIPULATORS_HPP
#define JEB_IOMANIPULATORS_HPP

#include <ostream>
#include <string>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace IO {

template <typename ValueT>
struct OSFiller
{
    OSFiller(size_t n, const ValueT& value)
        : n(n), value(value) {}
    OSFiller(size_t n, ValueT&& value)
        : n(n), value(std::move(value)) {}
    size_t n;
    ValueT value;
};

template <typename StreamT, typename ValueT>
StreamT& operator<<(StreamT& os, OSFiller<ValueT>&& filler)
{
    for (size_t i = 0; i < filler.n; ++i)
        os << filler.value;
    return os;
}

template <typename ValueT>
OSFiller<ValueT> fill(size_t n, ValueT&& str)
{
    return OSFiller<ValueT>(n, str);
}

inline OSFiller<char> spaces(size_t n)
{
    return fill(n, ' ');
}

template <typename FwdIt, typename StringT>
struct OSJoiner
{
    OSJoiner(FwdIt first, FwdIt last, StringT separator)
        : first(first), last(last), separator(separator)
    {}

    FwdIt first, last;
    StringT separator;
};

template <typename StreamT, typename FwdIt, typename StringT>
StreamT& operator<<(StreamT& os, OSJoiner<FwdIt, StringT>&& joiner)
{
    if (joiner.first != joiner.last)
    {
        os << *joiner.first;
        for (auto it = std::next(joiner.first); it != joiner.last; ++it)
            os << joiner.separator << *it;
    }
    return os;
}

template <typename FwdIt, typename StringT>
OSJoiner<FwdIt, StringT> join(FwdIt first, FwdIt last, StringT&& separator)
{
    return OSJoiner<FwdIt, StringT>(first, last, separator);
}

}}

#endif
