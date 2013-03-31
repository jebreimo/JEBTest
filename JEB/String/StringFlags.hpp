#ifndef JEB_STRINGFLAGS_HPP
#define JEB_STRINGFLAGS_HPP

#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String {

namespace Encoding
{
    enum Enum
    {
        Unknown,

        Ascii,
        Utf8,
        Latin1,
        Windows1252,
        Utf16,
        Utf16BE,
        Utf16LE = Utf16,
        Utf32,
        Utf32BE,
        Utf32LE = Utf32,
        Utf7,
        Utf1,
        UtfEbcdic,
        Scsu,
        Bocu1,
        Ucs2,
        Gb18030,

        Maximum
    };
}

namespace FindFlags
{
    enum Enum
    {
        Defaults = 0,
        CaseInsensitive = 1
    };
    typedef unsigned Flags;
}

namespace SplitFlags
{
    enum Enum
    {
        Defaults = 0,
        CaseInsensitive = 1,
        IgnoreEmpty = 2,
        MergeTokens = 4
    };
    typedef unsigned Flags;
    inline bool caseInsensitive(Flags flags) {return (flags & CaseInsensitive) != 0;}
    inline bool ignoreEmpty(Flags flags) {return (flags & IgnoreEmpty) != 0;}
    inline bool mergeTokens(Flags flags) {return (flags & MergeTokens) != 0;}
}

namespace DecodeResult
{
    enum Enum
    {
        Ok = 0,
        EndOfString = 1,
        Incomplete = 2,
        Invalid = 4,
        StartOfString = 8 //< Returned by prevCodePoint
    };
}
}}

#endif
