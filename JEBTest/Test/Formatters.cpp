/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "Formatters.hpp"
#include "JEB/String/StringConversion.hpp"

#undef JEB

namespace JEB { namespace Test {

std::ostream& operator<<(std::ostream& os, const std::wstring& s)
{
    return os << JEBTestLib::String::utf16ToUtf8(s);
}

std::ostream& operator<<(std::ostream& os, const wchar_t* s)
{
    return os << JEBTestLib::String::utf16ToUtf8(s);
}

}}
