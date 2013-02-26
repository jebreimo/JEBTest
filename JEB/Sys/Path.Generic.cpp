#include "Path.Generic.hpp"

#include <cstring>
#include <errno.h>
#include <fstream>
#include <stdexcept>
#include <sys/stat.h>
#include <unistd.h>
#include "JEB/String/String.hpp"

namespace JEB { namespace Sys { namespace Path { namespace Generic {

std::string extension(const std::string& p)
{
    return splitExtension(p).second;
}

std::string removeExtension(const std::string& p)
{
    return splitExtension(p).first;
}

std::pair<std::string, std::string> splitExtension(const std::string& p)
{
    std::pair<std::string, std::string> parts = String::splitLastToken(p, (uint32_t)'.');
    if (parts.first.empty() || parts.second.empty() || parts.first.back() == DirSep)
        return std::make_pair(p, std::string());
    return parts;
}

}}}}
