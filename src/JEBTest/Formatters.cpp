//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-10-28.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "JEBTest/Formatters.hpp"
#include "Yconvert/Convert.hpp"

namespace JEBTest
{
    std::ostream& operator<<(std::ostream& os, const std::wstring& s)
    {
        return os << Yconvert::convertTo<std::string>(
            s,
            Yconvert::Encoding::WCHAR_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& operator<<(std::ostream& os, const wchar_t* s)
    {
        return os << Yconvert::convertTo<std::string>(
            std::basic_string_view(s),
            Yconvert::Encoding::WCHAR_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& operator<<(std::ostream& os, const std::u16string& s)
    {
        return os << Yconvert::convertTo<std::string>(
            s,
            Yconvert::Encoding::UTF_16_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& operator<<(std::ostream& os, const char16_t* s)
    {
        return os << Yconvert::convertTo<std::string>(
            std::basic_string_view(s),
            Yconvert::Encoding::UTF_16_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& operator<<(std::ostream& os, const std::u32string& s)
    {
        return os << Yconvert::convertTo<std::string>(
            s,
            Yconvert::Encoding::UTF_32_NATIVE,
            Yconvert::Encoding::UTF_8);
    }

    std::ostream& operator<<(std::ostream& os, const char32_t* s)
    {
        return os << Yconvert::convertTo<std::string>(
            std::basic_string_view(s),
            Yconvert::Encoding::UTF_32_NATIVE,
            Yconvert::Encoding::UTF_8);
    }
}
