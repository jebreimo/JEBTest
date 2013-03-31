#include "Path.Win.hpp"

#include <direct.h>
#include <stdexcept>
#include "JEB/String/String.hpp"
#include "Path.Generic.hpp"

namespace JEB { namespace Sys { namespace Path { namespace Win {

char DirSep = '\\';
char DriveSep = ':';
const size_t MaxPath = 1024;

bool isDirSeparator(uint32_t chr)
{
    return chr == DriveSep || chr == DirSep;
}

std::string absPath(const std::string& p)
{
    //if (p.size() == 1)
}

std::string baseName(const std::string& p)
{
    return String::splitLastWhere(p, isDirSeparator).second;
}

std::string currentPath()
{
    char path[MaxPath];
    if (!_getcwd(path, sizeof(path)))
        throw std::runtime_error("Call to _getcwd() failed");
    // TODO: use wchar_t-version and convert to utf-8
    // std::wstring path(MaxPath);
    // if (!_wgetcwd(&path[0], path.size()))
    //     throw std::runtime_error(utf16ToUtf8(_wcserror(NULL)));
    // return utf16ToUtf8(path);

    // size_t size = GetCurrentDirectory(0, NULL);
    // std::wstring path(size);
    // if (GetCurrentDirectory(size, &path[0]) != size)
    //     throw std::runtime_error();
    // return utf16ToUtf8(path);
    return std::string(path);
}

//std::string expandDrive(const std::string& path)
//{
//    if (path.size() < 2 || path[1] != ':' ||
//        (path.size() > 2 && path[3] == '\\'))
//    {
//        return path;
//    }
//}

std::string homePath()
{
    // TODO: return the equivalent of the POSIX version.

    return std::string();
}

std::string join(const std::string& left, const std::string& right)
{
    if (left.empty())
        return right;
    else if (right.empty())
        return left;

    char l = left.back();
    char r = right.front();
    if ((l == DirSep && r == DirSep) || (l == DriveSep && r == DriveSep))
        return std::string(left.begin(), left.end() - 1) + right;
    else if (l == DirSep || r == DirSep || l == DriveSep || r == DriveSep)
        return left + right;
    else
        return left + DirSep + right;
}

std::string normalize(const std::string& p)
{
  return p;
}

std::string removeExtension(const std::string& p)
{
    return splitExtension(p).first;
}

std::pair<std::string, std::string> split(const std::string& path)
{
    return String::splitLastToken(path, DirSep);
}

std::pair<std::string, std::string> splitDrive(const std::string& path)
{
    if (path.size() < 2 || path[1] != ':')
        return std::make_pair(std::string(), path);
    return std::make_pair(path.substr(0, 2), path.substr(2));
}

std::pair<std::string, std::string> splitExtension(const std::string& p)
{
    return Generic::splitExtension(p, isDirSeparator);
}

}}}}
