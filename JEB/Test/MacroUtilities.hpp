#ifndef JEB_MACRO_UTILITIES_HPP
#define JEB_MACRO_UTILITIES_HPP

#include <string>
#include <vector>

namespace JEB { namespace Test {

std::vector<std::string> extractTestNames(const std::string& names);
// std::string extractTestName(const std::string& name);
std::string extractSuiteName(const std::string& path);

}}

#endif
