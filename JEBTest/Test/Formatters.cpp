/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "Formatters.hpp"
#include "JEBString/JEBUtf8.hpp"

#undef JEB

namespace JEBTest {

using namespace JEBTest_JEBString;

std::ostream& operator<<(std::ostream& os, const std::wstring& s)
{
    return os << Utf8::toUtf8(s, Encoding::Utf16);
}

std::ostream& operator<<(std::ostream& os, const wchar_t* s)
{
    return os << Utf8::toUtf8(s, Encoding::Utf16);
}

}
