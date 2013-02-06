#include "Split.hpp"

#include "JEB/Iterators/PairInserter.hpp"
#include "JEB/Unicode/CaseInsensitive.hpp"
#include "JEB/String/StringPredicates.hpp"
#include "JEB/String/Generic/SplitIterator.hpp"
#include "Finder.hpp"

namespace JEB { namespace String { namespace Utf8 {

template <typename OutIterator, typename SplitIterator>
void splitWithIterators(OutIterator outIt,
                        SplitIterator splitIt,
                        size_t maxSplits,
                        bool ignoreEmpty);

template <typename StringCollection>
void split(StringCollection& dst,
           const std::string& str,
           size_t maxSplits,
           SplitFlags::Flags flags)
{
    splitWithFinder(dst,
                    str,
                    tokenFinder(String::isWhitespace(),
                                SplitFlags::mergeTokens(flags)),
                    maxSplits,
                    SplitFlags::ignoreEmpty(flags));
}

template <typename StringCollection>
void split(StringCollection& dst,
           const std::string& str,
           const std::string& sep,
           size_t maxSplits,
           SplitFlags::Flags flags)
{
    if (!SplitFlags::caseInsensitive(flags))
        splitWithFinder(dst, str, firstFinder(sep), maxSplits, SplitFlags::ignoreEmpty(flags));
    else
        splitWithFinder(dst, str, firstFinder(sep, Unicode::CaseInsensitiveEqual<uint32_t>()), maxSplits, SplitFlags::ignoreEmpty(flags));
}

template <typename StringCollection, typename Finder>
void splitWithFinder(StringCollection& dst,
                     const std::string& str,
                     Finder finder,
                     size_t maxSplits,
                     bool ignoreEmpty)
{
    splitWithFinder(dst,
                    str.begin(), str.end(),
                    finder,
                    maxSplits,
                    ignoreEmpty);
}

template <typename StringCollection, typename FwdIt, typename Finder>
void splitWithFinder(StringCollection& dst,
                     FwdIt begin, FwdIt end,
                     Finder finder,
                     size_t maxSplits,
                     bool ignoreEmpty)
{
    return splitWithIterators(std::back_inserter(dst),
                              makeSplitIterator(begin, end, finder),
                              maxSplits,
                              ignoreEmpty);
}

template <typename Finder>
std::pair<std::string, std::string> splitPairWithFinder(
        const std::string& str,
        Finder finder)
{
    return splitPairWithFinder(str.begin(), str.end(), finder);
}

template <typename FwdIt, typename Finder>
std::pair<std::string, std::string> splitPairWithFinder(
        FwdIt begin, FwdIt end,
        Finder finder)
{
    std::pair<std::string, std::string> result;
    splitWithIterators(JEB::backInserter(result),
                       makeSplitIterator(begin, end, finder),
                       2,
                       false);
    return result;
}

template <typename OutIterator, typename SplitIterator>
void splitWithIterators(OutIterator outIt,
                        SplitIterator splitIt,
                        size_t maxSplits,
                        bool ignoreEmpty)
{
    while (--maxSplits != 0 && splitIt.next())
    {
        if (!ignoreEmpty || !splitIt.empty())
            *outIt++ = std::string(splitIt.begin(), splitIt.end());
    }
    if (!splitIt.eof() && (!ignoreEmpty || !splitIt.emptyRemainder()))
        *outIt++ = std::string(splitIt.beginRemainder(),
                               splitIt.endRemainder());
}

}}}
