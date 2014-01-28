#include "Path.hpp"

#include <cstring>
#include <errno.h>
#include <fstream>
#include <stdexcept>
#include <sys/stat.h>
#include <unistd.h>
#include "JEB/String/StringPredicates.hpp"
#include "Environment.hpp"
#include "Users.hpp"
#include "Path.Generic.hpp"

namespace JEB { namespace Sys { namespace Path { namespace Posix {

const char DirSep = '/';

static const std::string DirSepStr(1, DirSep);

std::string baseName(const std::string& p)
{
    return String::splitLastToken(p, (uint32_t)DirSep).second;
}

std::string currentPath()
{
    char path[PATH_MAX + 1];
    if (!getcwd(path, sizeof(path)))
        throw std::runtime_error(strerror(errno));
    return std::string(path);
}

std::string expandUser(const std::string& path)
{
    if (path.empty() || path.front() != '~')
        return path;
    std::pair<std::string, std::string> parts = String::splitFirstToken(path, DirSep);
    if (parts.first == "~")
    {
        return join(homePath(), parts.second);
    }
    else
    {
        std::string userPath = Users::homePath(parts.first.substr(1, parts.first.size()));
        if (userPath.empty())
            return path;
        return join(userPath, parts.second);
    }
}

std::string extension(const std::string& p)
{
    return splitExtension(p).second;
}

std::string getSystemDefaultPath()
{
    std::ifstream file("/etc/paths");
    if (!file)
        return std::string();
    std::string result;
    while (!file.eof())
    {
        std::string line;
        getline(file, line);
        if (!line.empty())
        {
            if (!result.empty())
                result += ":";
            result += line;
        }
    }
    return result;
}

std::string homePath()
{
    std::string value;
    if (Environment::tryGetValue("HOME", value))
        return value;
    else
        return Users::homePath();
}

bool isExecutable(const std::string& path)
{
    if (access(path.c_str(), X_OK) == 0)
        return true;
    else if (errno != EACCES)
        throw std::runtime_error(strerror(errno));

    return false;
}

bool isFile(const std::string& path)
{
    struct stat buf;
    if (stat(path.c_str(), &buf) != 0)
        return false;
        //throw std::runtime_error(strerror(errno));
    return (buf.st_mode & S_IFREG) == S_IFREG;
}

std::string join(const std::string& left, const std::string& right)
{
    if (left.empty())
        return right;
    else if (right.empty())
        return left;

    bool sepL = left.back() == DirSep;
    bool sepR = right.front() == DirSep;
    if (sepL && sepR)
        return std::string(left.begin(), left.end() - 1) + right;
    else if (sepL || sepR)
        return left + right;
    else
        return left + DirSepStr + right;
}

std::string normalize(const std::string& p)
{
    std::vector<std::string> result;
    std::vector<std::string> parts = String::splitToken(p, DirSep);
    for (auto it = parts.begin(); it != parts.end(); ++it)
    {
        if (*it == "..")
        {
            if (result.empty() || result.back() == "..")
                result.push_back(*it);
            else if (!result.back().empty())
                result.pop_back();
        }
        else if (*it != "." && (result.empty() || !it->empty()))
        {
            result.push_back(*it);
        }
    }
    bool startsAtRoot = !p.empty() && p[0] == DirSep;
    if (result.empty() && !parts.empty())
    {
        if (startsAtRoot)
            return DirSepStr;
        else
            return std::string(".");
    }
    else
    {
        return String::join(result, DirSepStr);
    }
}

std::string removeExtension(const std::string& p)
{
    return splitExtension(p).first;
}

std::pair<std::string, std::string> split(const std::string& path)
{
    return String::splitLastToken(path, DirSep);
}

std::pair<std::string, std::string> splitExtension(const std::string& p)
{
    return Generic::splitExtension(p, JEB::String::isCharacter('/'));
}

}}}}
