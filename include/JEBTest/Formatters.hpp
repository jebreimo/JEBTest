//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <sstream>
#include <typeinfo>

namespace JEBTest
{
    std::ostream& operator<<(std::ostream& os, const std::wstring& s);

    std::ostream& operator<<(std::ostream& os, const wchar_t* s);

    std::ostream& operator<<(std::ostream& os, wchar_t c);

    std::ostream& operator<<(std::ostream& os, const std::u8string& s);

    std::ostream& operator<<(std::ostream& os, const char8_t* s);

    std::ostream& operator<<(std::ostream& os, char8_t c);

    std::ostream& operator<<(std::ostream& os, const std::u16string& s);

    std::ostream& operator<<(std::ostream& os, const char16_t* s);

    std::ostream& operator<<(std::ostream& os, char16_t c);

    std::ostream& operator<<(std::ostream& os, const std::u32string& s);

    std::ostream& operator<<(std::ostream& os, const char32_t* s);

    std::ostream& operator<<(std::ostream& os, char32_t c);

    template<typename T, typename U>
    std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
    {
        return os << "{" << p.first << ", " << p.second << "}";
    }

    template <typename T, typename U>
    std::string formatComparison(const T& t, const char* tName,
                                 const U& u, const char* uName,
                                 const char* operat)
    {
        std::ostringstream ss;
        ss.precision(17);
        ss << tName << " " << operat << " " << uName
           << ":  \"" << t << "\" " << operat << " \"" << u << "\".";
        return ss.str();
    }

    template <typename T, typename U>
    std::string formatComparison(T* t, const char* tName,
                                 U* u, const char* uName,
                                 const char* operat)
    {
        std::ostringstream ss;
        ss << tName << " " << operat << " " << uName
           << ":  (" << typeid(T*).name() << ")\"";
        if (t)
            ss << t;
        else
            ss << "nullptr";
        ss << "\" " << operat << " (" << typeid(U*).name() << ")\"";
        if (u)
            ss << u;
        else
            ss << "nullptr";
        ss << "\".";
        return ss.str();
    }
}
