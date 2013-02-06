#ifndef JEB_STRING_UTF8_FINDER_HPP
#define JEB_STRING_UTF8_FINDER_HPP

#include "JEB/String/Generic/Finder.hpp"

#include "BiIterator.hpp"
#include "FwdIterator.hpp"

namespace JEB { namespace String { namespace Utf8 {

typedef Utf8::BiIterator<std::string::const_iterator> Iterator;

template <typename Finder>
class FinderAdapter
{
public:
    FinderAdapter(const Finder& finder) : m_Finder(finder) {}

    template <typename FwdIt>
    std::pair<FwdIt, FwdIt> operator()(FwdIt begin, FwdIt end) const
    {
        typedef Utf8::BiIterator<FwdIt> Utf8It;
        std::pair<Utf8It, Utf8It> its = m_Finder(Utf8::begin(begin, end),
                                                 Utf8::end(begin, end));
        return std::make_pair(its.first.beginCodePoint(),
                              its.second.beginCodePoint());
    }

    typedef Utf8::BiIterator<std::string::const_iterator> Utf8BiIt;

    std::pair<Utf8BiIt, Utf8BiIt> operator()(Utf8BiIt begin, Utf8BiIt end) const
    {
        return m_Finder(begin, end);
    }

    typedef Utf8::FwdIterator<std::string::const_iterator> Utf8FwdIt;

    std::pair<Utf8FwdIt, Utf8FwdIt> operator()(Utf8FwdIt begin, Utf8FwdIt end) const
    {
        return m_Finder(begin, end);
    }
private:
    Finder m_Finder;
};

template <typename Finder>
FinderAdapter<Finder> adaptFinder(const Finder& finder)
{
    return FinderAdapter<Finder>(finder);
}

template <typename BinaryFunc>
FinderAdapter<Generic::FirstFinder<Iterator, BinaryFunc>>
firstFinder(const std::string& str, BinaryFunc comparer)
{
    return adaptFinder(Generic::firstFinder(
            Utf8::begin(str), Utf8::end(str), comparer));
}

inline FinderAdapter<Generic::FirstFinder<Iterator, std::equal_to<uint32_t>>>
firstFinder(const std::string& str)
{
    return firstFinder(str, std::equal_to<uint32_t>());
}

template <typename BinaryFunc>
FinderAdapter<Generic::LastFinder<Iterator, BinaryFunc>>
lastFinder(const std::string& str, BinaryFunc comparer)
{
    return adaptFinder(Generic::lastFinder(
            Utf8::begin(str), Utf8::end(str), comparer));
}

inline
FinderAdapter<Generic::LastFinder<Iterator, std::equal_to<uint32_t>>>
lastFinder(const std::string& str)
{
    return lastFinder(str, std::equal_to<uint32_t>());
}

template <typename BinaryFunc>
FinderAdapter<Generic::NthLastFinder<Iterator, BinaryFunc>>
nthLastFinder(const std::string& str, size_t count, BinaryFunc comparer)
{
    return adaptFinder(Generic::nthLastFinder(
            Utf8::begin(str), Utf8::end(str), count, comparer));
}

inline
FinderAdapter<Generic::NthLastFinder<Iterator, std::equal_to<uint32_t>>>
nthLastFinder(const std::string& str, size_t count)
{
    return nthLastFinder(str, count, std::equal_to<uint32_t>());
}

template <typename UnaryFunc>
FinderAdapter<Generic::TokenFinder<UnaryFunc>>
tokenFinder(UnaryFunc predicate, bool compress = false)
{
    return adaptFinder(Generic::TokenFinder<UnaryFunc>(predicate, compress));
}

template <typename UnaryFunc>
FinderAdapter<Generic::LastTokenFinder<UnaryFunc>>
lastTokenFinder(UnaryFunc predicate, bool compress = false)
{
    return adaptFinder(Generic::LastTokenFinder<UnaryFunc>(predicate, compress));
}

}}}

#endif
