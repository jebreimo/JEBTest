#include <algorithm>
#include "Conversion.hpp"
#include "Utf8/OutIterator.hpp"
#include "Utf16/BiIterator.hpp"

namespace JEB { namespace String {

std::string utf16ToUtf8(const std::wstring& s)
{
    std::string result;
    result.reserve(s.size());
    std::copy(Utf16::begin(s), Utf16::end(s), Utf8::backInserter(result));
    return result;
}

}}