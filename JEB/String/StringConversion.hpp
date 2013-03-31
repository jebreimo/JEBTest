#include <string>
#include <vector>
#include "JEB/JEBDefinitions.hpp"
#include "StringFlags.hpp"

namespace JEB { namespace String {

// template <typename InpIt, typename OutIt>
// bool convert(InpIt begin, InpIt end,
//              Encoding::Enum inEncoding,
//              OutIt outBeg, OutIt outEnd,
//              Encoding::Enum outEncoding)
// {

// }

class StringConverter
{
public:
    enum ErrorMethod {THROW_EXCEPTION, IGNORE, USE_VALUE, INSERT_CHARACTER};
    static StringConverter create(Encoding::Enum srcEncoding,
                                  Encoding::Enum dstEncoding);

    std::pair<size_t, size_t> convert(const char* srcBuffer, size_t srcSize,
                                      char* dstBuffer, size_t dstSize);
    ErrorMethod errorMethod() const;
    void setErrorMethod(ErrorMethod errorMethod);

    uint32_t invalidCharacterSubstitute() const;
    void setInvalidCharacterSubstitute(uint32_t chr);

    Encoding::Enum destinationEncoding() const;
    Encoding::Enum sourceEncoding() const;
private:
    typedef int (*NextCodePointFunc)(uint32_t&, const char*&, const char*);
    typedef bool (*EncodeFunc)(char*&, char*, uint32_t);

    StringConverter(NextCodePointFunc nextCodePoint, EncodeFunc encode,
                    Encoding::Enum srcEncoding, Encoding::Enum dstEncoding);

    Encoding::Enum m_DestinationEncoding;
    Encoding::Enum m_SourceEncoding;
    NextCodePointFunc m_NextCodePoint;
    EncodeFunc m_Encode;
    ErrorMethod m_ErrorMethod;
    uint32_t m_InvalidCharacterSubstitute;
};

std::pair<size_t, size_t> convert(const char* srcBuffer, size_t srcSize,
                                  Encoding::Enum srcEncoding,
                                  char* dstBuffer, size_t dstSize,
                                  Encoding::Enum dstEncoding);

std::string utf16ToUtf8(const std::wstring& s);
// std::string utf16LEToUtf8(const std::wstring& s);
// std::string utf16BEToUtf8(const std::wstring& s);

// std::wstring utf8ToUtf16(const std::string& s);
// std::wstring utf8ToUtf16LE(const std::string& s);
// std::wstring utf8ToUtf16BE(const std::string& s);
// std::vector<uint32_t> utf8ToUtf32(const std::string& s);
// std::vector<uint32_t> utf8ToUtf32LE(const std::string& s);
// std::vector<uint32_t> utf8ToUtf32BE(const std::string& s);

}}