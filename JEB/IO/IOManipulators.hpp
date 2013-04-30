#ifndef JEB_IOMANIPULATORS_HPP
#define JEB_IOMANIPULATORS_HPP

#include <ostream>
#include <string>
#include "JEB/JEBDefinitions.hpp"

namespace JEB
{

template <typename CharT>
struct OStreamFill {size_t n; CharT ch;};

template <typename CharT>
struct OStreamFillStr {size_t n; const std::basic_string<CharT>* str;};

template <typename CharT>
OStreamFill<CharT> fill(size_t n, CharT ch)
{
    OStreamFill<CharT> f = {n, ch};
    return f;
}

template <typename CharT>
OStreamFillStr<CharT> fill(size_t n, const std::basic_string<CharT>& str)
{
    OStreamFill<CharT> f = {n, &str};
    return f;
}

inline OStreamFill<char> spaces(size_t n)
{
    OStreamFill<char> f = {n, ' '};
    return f;
}

inline OStreamFill<wchar_t> wspaces(size_t n)
{
    OStreamFill<wchar_t> f = {n, ' '};
    return f;
}

template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const OStreamFill<CharT>& fill)
{
    for (size_t i = 0; i < fill.n; ++i)
        os.put(fill.ch);
    return os;
}

template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const OStreamFillStr<CharT>& fill)
{
    for (size_t i = 0; i < fill.n; ++i)
        os.write(fill.c_str(), fill.size());
    return os;
}
}

#endif
