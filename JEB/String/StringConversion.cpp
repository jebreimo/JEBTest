#include "StringConversion.hpp"
#include <algorithm>
#include "Utf8/Decode.hpp"
#include "Utf8/Encode.hpp"
#include "Utf8/OutIterator.hpp"
#include "Utf16/BiIterator.hpp"
#include "Utf16/Decode.hpp"
#include "Utf16/Encode.hpp"

namespace JEB { namespace String {

typedef int (*NextCodePointFunc)(uint32_t&, const char*&, const char*);
typedef bool (*EncodeFunc)(char*&, char*, uint32_t);

NextCodePointFunc getNextCodePointFunc(Encoding::Enum encoding)
{
    switch (encoding)
    {
    case Encoding::Utf8:
        return Utf8::nextCodePoint<const char*>;
    case Encoding::Utf16LE:
        return  Utf16::nextCodePointLE<const char*>;
    case Encoding::Utf16BE:
        return  Utf16::nextCodePointBE<const char*>;
    default:
        throw std::invalid_argument("Unsupported input encoding");
    };
}

EncodeFunc getEncodeFunc(Encoding::Enum encoding)
{
    switch (encoding)
    {
    case Encoding::Utf8:
        return Utf8::encode<char*>;
    case Encoding::Utf16LE:
        return Utf16::encodeLE<char*>;
    case Encoding::Utf16BE:
        return Utf16::encodeBE<char*>;
    default:
        throw std::invalid_argument("Unsupported output encoding");
    };
}

std::pair<size_t, size_t> convert(const char* srcBuffer, size_t srcSize,
                                  Encoding::Enum srcEncoding,
                                  char* dstBuffer, size_t dstSize,
                                  Encoding::Enum dstEncoding)
{
    // TODO: if source and dest encodings are the same, find last valid
    // char in source and use memcpy.

    NextCodePointFunc nextCodePoint = getNextCodePointFunc(srcEncoding);
    EncodeFunc encode = getEncodeFunc(dstEncoding);

    const char* srcIt = srcBuffer;
    const char* prevSrcIt = srcIt;
    const char* srcEnd = srcBuffer + srcSize;
    char* dstIt = dstBuffer;
    char* dstEnd = dstBuffer + dstSize;
    uint32_t codePoint;
    while (dstIt < dstEnd &&
           nextCodePoint(codePoint, srcIt, srcEnd) == DecodeResult::Ok)
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

StringConverter::StringConverter(NextCodePointFunc nextCodePoint,
                                 EncodeFunc encode,
                                 Encoding::Enum srcEncoding,
                                 Encoding::Enum dstEncoding)
    : m_NextCodePoint(nextCodePoint),
      m_Encode(encode),
      m_SourceEncoding(srcEncoding),
      m_DestinationEncoding(dstEncoding)
{}

StringConverter StringConverter::create(Encoding::Enum srcEncoding,
                                        Encoding::Enum dstEncoding)
{
    return StringConverter(getNextCodePointFunc(srcEncoding),
                           getEncodeFunc(dstEncoding),
                           srcEncoding, dstEncoding);
}

std::pair<size_t, size_t> StringConverter::convert(const char* srcBuffer,
                                                   size_t srcSize,
                                                   char* dstBuffer,
                                                   size_t dstSize)
{
    const char* srcIt = srcBuffer;
    const char* prevSrcIt = srcIt;
    const char* srcEnd = srcBuffer + srcSize;
    char* dstIt = dstBuffer;
    char* dstEnd = dstBuffer + dstSize;
    uint32_t codePoint;
    while (dstIt < dstEnd)
    {
        // if (!m_NextCodePoint(codePoint, srcIt, srcEnd))
        // {
        //     if ()
        // }
        if (!m_Encode(dstIt, dstEnd, codePoint))
            return std::make_pair((size_t)(prevSrcIt - srcBuffer),
                                  (size_t)(dstIt - dstBuffer));
        prevSrcIt = srcIt;
    }
    return std::make_pair((size_t)(srcIt - srcBuffer),
                          (size_t)(dstIt - dstBuffer));
}

StringConverter::ErrorMethod StringConverter::errorMethod() const
{
    return m_ErrorMethod;
}

void StringConverter::setErrorMethod(ErrorMethod errorMethod)
{
    m_ErrorMethod = errorMethod;
}

uint32_t StringConverter::invalidCharacterSubstitute() const
{
    return m_InvalidCharacterSubstitute;
}

void  StringConverter::setInvalidCharacterSubstitute(uint32_t chr)
{
    m_InvalidCharacterSubstitute = chr;
}

Encoding::Enum StringConverter::destinationEncoding() const
{
    return m_DestinationEncoding;
}

Encoding::Enum StringConverter::sourceEncoding() const
{
    return m_SourceEncoding;
}

}}
