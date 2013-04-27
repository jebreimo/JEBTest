#include "MacroUtilities.hpp"

#include "JEB/Sys/Path.hpp"
#include "JEB/String/String.hpp"

#undef JEB

using namespace JEBTestLib::String;
using namespace JEBTestLib::Sys;

namespace JEB { namespace Test {

std::string extractTestName(const std::string& name)
{
    if (startsWith(name, "test_", FindFlags::CaseInsensitive))
        return name.substr(5);
    return name;
}

std::vector<std::string> extractTestNames(const std::string& names)
{
    std::vector<std::string> list = split(names, ",");
    for (auto it = list.begin(); it != list.end(); it++)
        *it = extractTestName(trim(*it));
    return list;
}

std::string extractSuiteName(const std::string& path)
{
    std::string name = Path::baseName(Path::removeExtension(path));
    if (startsWith(name, "testsuite_"/*, FindFlags::CaseInsensitive*/))
        return name.substr(10);
    return name;
}

}}
