#include "FromString.hpp"

#include <cctype>
#include <cstdlib>
#include <locale>

namespace JEB {

bool fromString(const std::string& s, double value)
{
    char* end;
    value = std::strtod(s.c_str(), &end);
    return end != s.c_str() && (*end == '\0' || std::isspace(*end));
}

bool fromString(const std::wstring& s, double value)
{
    wchar_t* end;
    value = std::wcstod(s.c_str(), &end);
    return end != s.c_str() && (*end == '\0' || std::isspace(*end));
}

bool fromString(const std::string& s, long& value, int base)
{
    char* end;
    value = std::strtol(s.c_str(), &end, base);
    return end != s.c_str() && (*end == '\0' || std::isspace(*end));
}

bool fromString(const std::wstring& s, long& value, int base)
{
    wchar_t* end;
    value = std::wcstol(s.c_str(), &end, base);
    return end != s.c_str() && (*end == '\0' || std::isspace(*end));
}
}
