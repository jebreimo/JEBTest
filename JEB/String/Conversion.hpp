#include <string>
#include <vector>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String {

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