#include "Environment.hpp"

#include <cstdlib>
#include "EnvironmentIterator.hpp"

namespace JEB { namespace Sys { namespace Environment {

const char EnvPathSep = ':';

std::string value(const std::string& name)
{
    const char* v = getenv(name.c_str());
    if (v)
        return std::string(v);
    else
        return std::string();
}

void setValue(const std::string& name, const std::string& value)
{
    setenv(name.c_str(), value.c_str(), 1);
}

void setDefaultValue(const std::string& name, const std::string& value)
{
    setenv(name.c_str(), value.c_str(), 0);
}

bool tryGetValue(const std::string& name, std::string& value)
{
    const char* v = getenv(name.c_str());
    if (!v)
        return false;
    value = v;
    return true;
}

}}}
