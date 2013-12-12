/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_TEST_FORMATTERS_HPP
#define JEB_TEST_FORMATTERS_HPP

#include <sstream>

namespace JEB { namespace Test {

template <typename T, typename U>
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
       << ".  Expected \"" << u << "\", but received \"" << t << "\"";
    return ss.str();
}

template <typename T, typename U>
std::string formatComparison(T* t, const char* tName,
                             U* u, const char* uName,
                             const char* operat)
{
    std::ostringstream ss;
    ss << tName << " " << operat << " " << uName
       << ".  Expected \"" << (u ? u : (void*)u)
       << "\", but received \"" << (t ? t : (void*)t) << "\"";
    return ss.str();
}

}}

#endif
