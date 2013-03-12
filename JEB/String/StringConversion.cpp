#include "StringConversion.hpp"
#include <algorithm>
#include "Utf8/Decode.hpp"
#include "Utf8/Encode.hpp"
#include "Utf8/OutIterator.hpp"
#include "Utf16/BiIterator.hpp"
#include "Utf16/Decode.hpp"
#include "Utf16/Encode.hpp"

namespace JEB { namespace String {

std::pair<size_t, size_t> convert(const char* srcBuffer, size_t srcSize,
                                  Encoding::Enum srcEncoding,
                                  char* dstBuffer, size_t dstSize,
                                  Encoding::Enum dstEncoding)
{
    if (srcEncoding == dstEncoding)
    {
        if (dstSize < srcSize)
            srcSize = dstSize;
        std::memcpy(dstBuffer, srcBuffer, srcSize);
        return std::make_pair(srcSize, srcSize);
    }

    bool (*nextCodePoint)(uint32_t&, const char*& it, const char* end) = 0;
    switch (srcEncoding)
    {
    case Encoding::Utf8:
        nextCodePoint = Utf8::nextCodePoint<const char*>;
        break;
    case Encoding::Utf16LE:
        nextCodePoint = Utf16::nextCodePointLE<const char*>;
        break;
    case Encoding::Utf16BE:
        nextCodePoint = Utf16::nextCodePointBE<const char*>;
        break;
    default:
        throw std::invalid_argument("Unsupported input encoding");
    };

    bool (*encode)(char*&, char*, uint32_t) = NULL;
    switch (dstEncoding)
    {
    case Encoding::Utf8:
        encode = Utf8::encode<char*>;
        break;
    case Encoding::Utf16LE:
        encode = Utf16::encodeLE<char*>;
        break;
    case Encoding::Utf16BE:
        encode = Utf16::encodeBE<char*>;
        break;
    default:
        throw std::invalid_argument("Unsupported output encoding");
    };

    const char* srcIt = srcBuffer;
    const char* prevSrcIt = srcIt;
    const char* srcEnd = srcBuffer + srcSize;
    char* dstIt = dstBuffer;
    char* dstEnd = dstBuffer + dstSize;
    uint32_t codePoint;
    while (dstIt < dstEnd && nextCodePoint(codePoint, srcIt, srcEnd))
    {
        if (!encode(dstIt, dstEnd, codePoint))
            return std::make_pair((size_t)(prevSrcIt - srcBuffer),
                                  (size_t)(dstIt - dstBuffer));
        prevSrcIt = srcIt;
    }
    return std::make_pair((size_t)(srcIt - srcBuffer),
                          (size_t)(dstIt - dstBuffer));
}

std::string utf16ToUtf8(const std::wstring& s)
{
    std::string result;
    result.reserve(s.size());
    std::copy(Utf16::begin(s), Utf16::end(s), Utf8::backInserter(result));
    return result;
}

}}
