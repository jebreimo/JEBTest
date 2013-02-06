#ifndef JEB_SYS_ENVIRONMENT_HPP
#define JEB_SYS_ENVIRONMENT_HPP

#include <map>
#include <string>
#include <vector>
#include "JEB/String/String.hpp"

namespace JEB { namespace Sys { namespace Environment {

extern const char EnvPathSep;

std::string value(const std::string& name);
void setValue(const std::string& name, const std::string& value);
void setDefaultValue(const std::string& name, const std::string& value);
void read(std::map<std::string, std::string>& values);
void names(std::vector<std::string>& names);
bool tryGetValue(const std::string& name, std::string& value);

std::vector<std::string> splitPaths(const std::string& path);

bool tryGetPaths(const std::string& name, std::vector<std::string>& paths);

}}}

#endif