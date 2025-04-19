//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-10-28.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "JEBTest/Formatters.hpp"

#include <iomanip>

#include "Yconvert/Convert.hpp"
#include "Ystring/Algorithms.hpp"

namespace JEBTest
{
    std::ostream& operator<<(std::ostream& os, const std::wstring& s)
    {
        return os << Yconvert::convert_to<std::string>(
            s,
            Yconvert::Encoding::WSTRING_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& operator<<(std::ostream& os, const wchar_t* s)
    {
        return os << Yconvert::convert_to<std::string>(
            std::basic_string_view(s),
            Yconvert::Encoding::WSTRING_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& streamChar32(std::ostream& os, char32_t c)
    {
        if (c < 128)
            return os << char(c);

        auto flags = os.setf(std::ios::hex);
        auto fill = os.fill('0');

        if (c < 0x100)
            os << "\\x" << std::setw(2) << c;
        else if (c < 0x10000)
            os << "\\u" << std::setw(4) << c;
        else
            os << "\\U" << std::setw(8) << c;

        os.fill(fill);
        os.setf(flags);

        return os;
    }

    std::ostream& operator<<(std::ostream& os, wchar_t c)
    {
        return streamChar32(os, char32_t(c));
    }

    std::ostream& operator<<(std::ostream& os, const std::u8string& s)
    {
        return os << JEBTest_Ystring::to_string_view(s);
    }

    std::ostream& operator<<(std::ostream& os, const char8_t* s)
    {
        return os << reinterpret_cast<const char*>(s);
    }

    std::ostream& operator<<(std::ostream& os, char8_t c)
    {
        return streamChar32(os, char32_t(c));
    }

    std::ostream& operator<<(std::ostream& os, const std::u16string& s)
    {
        return os << Yconvert::convert_to<std::string>(
            s,
            Yconvert::Encoding::UTF_16_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& operator<<(std::ostream& os, const char16_t* s)
    {
        return os << Yconvert::convert_to<std::string>(
            std::basic_string_view(s),
            Yconvert::Encoding::UTF_16_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& operator<<(std::ostream& os, char16_t c)
    {
        return streamChar32(os, char32_t(c));
    }

    std::ostream& operator<<(std::ostream& os, const std::u32string& s)
    {
        return os << Yconvert::convert_to<std::string>(
            s,
            Yconvert::Encoding::UTF_32_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& operator<<(std::ostream& os, const char32_t* s)
    {
        return os << Yconvert::convert_to<std::string>(
            std::basic_string_view(s),
            Yconvert::Encoding::UTF_32_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& operator<<(std::ostream& os, char32_t c)
    {
        return streamChar32(os, c);
    }
}
