#include "MacroUtilities.hpp"

#include "JEB/Sys/Path.hpp"
#include "JEB/String/String.hpp"

#undef JEB

using namespace JEBTestLib::String;
using namespace JEBTestLib::Sys;

namespace JEB { namespace Test {

// std::string extractTestName(const std::string& name)
// {
//     if (startsWith(name, "test_", FindFlags::CaseInsensitive))
//         return name.substr(5);
//     return name;
// }

std::vector<std::string> extractTestNames(const std::string& names)
{
    return split(names, ",");
}

std::string extractSuiteName(const std::string& path)
{
    return Path::baseName(Path::removeExtension(path));
}

}}
