#ifndef JEB_STRING_FROMSTRING_HPP
#define JEB_STRING_FROMSTRING_HPP

#include <sstream>
#include <string>
#include "JEB/JEBDefinitions.hpp"

namespace JEB {

template <typename T>
bool fromString(const std::string& s, T& value)
{
    std::istringstream stream(s);
    stream >> value;
    return !stream.fail();
}

template <typename T>
bool fromString(const std::wstring& s, T& value)
{
    std::wistringstream stream(s);
    stream >> value;
    return !stream.fail();
}

template <>
inline bool fromString<bool>(const std::string& s, bool& value)
{
    if (s == "1" || s == "true")
        value = true;
    else if (s == "0" || s == "false")
        value = false;
    else
        return false;

    return true;
}

template <>
inline bool fromString<bool>(const std::wstring& s, bool& value)
{
    if (s == L"1" || s == L"true")
        value = true;
    else if (s == L"0" || s == L"false")
        value = false;
    else
        return false;

    return true;
}

template <>
inline bool fromString<std::string>(const std::string& s, std::string& value)
{
    value = s;
    return true;
}

template <>
inline bool fromString<std::wstring>(const std::wstring& s, std::wstring& value)
{
    value = s;
    return true;
}

bool fromString(const std::string& s, double value);
bool fromString(const std::wstring& s, double value);
bool fromString(const std::string& s, long& value, int base = 10);
bool fromString(const std::wstring& s, long& value, int base = 10);

}

#endif
