#ifndef JEB_UNIT_FORMATTERS_HPP
#define JEB_UNIT_FORMATTERS_HPP

#include <sstream>

namespace JEB { namespace Unit {

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
    ss << tName << " " << operat << " " << uName
       << "\n    Received: " << t
       << "\n    Expected: " << u;
    return ss.str();
}

}}

#endif
