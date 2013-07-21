#include "Environment.hpp"

#include <cstdlib>
#include "JEB/Collections/MapUtilities.hpp"
#include "EnvironmentIterator.hpp"

#if defined(__APPLE__)
    #define JEB_HAS_UNIX_PATHS
#elif (WIN32)
    #define JEB_HAS_WIN_PATHS
#endif

namespace JEB { namespace Sys { namespace Environment {

// #ifdef JEB_HAS_UNIX_PATHS
// const char EnvPathSep = ':';
// #else
// const char EnvPathSep = ';';
// #endif

void names(std::vector<std::string>& names)
{
    EnvironmentIterator it;
    while (it.hasNext())
        names.push_back(it.next().first);
}

void read(std::map<std::string, std::string>& values)
{
    EnvironmentIterator it;
    while (it.hasNext())
        values.insert(it.next());
}

std::vector<std::string> splitPaths(const std::string& path)
{
    return String::splitWhere(path, [](uint32_t c){return c == EnvPathSep;});
}

bool tryGetPaths(const std::string& name, std::vector<std::string>& paths)
{
    std::string value;
    if (!tryGetValue(name, value))
        return false;
    paths = splitPaths(value);
    return true;
}

}}}
