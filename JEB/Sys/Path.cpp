#include "Path.hpp"

// #include <fstream>
// #include <stdexcept>

// #include <JEB/String/String.hpp>
// #include "Users.hpp"

// namespace JEB { namespace Sys {
// namespace Path
// {

// char DirSep = '/';
// static const std::string DirSepStr(1, DirSep);

// std::string baseName(const std::string& p)
// {
//     return String::splitLastToken(p, (uint32_t)DirSep).second;
// }

// std::string expandUser(const std::string& path)
// {
//     if (path.empty() || path.front() != '~')
//         return path;
//     std::pair<std::string, std::string> parts = String::splitFirst(path, DirSep);
//     if (parts.first == "~")
//     {
//         return join(homePath(), parts.second);
//     }
//     else
//     {
//         std::string userPath = Users::homePath(parts.first.substr(1, parts.first.size()));
//         if (userPath.empty())
//             return path;
//         return join(userPath, parts.second);
//     }
// }

// std::string extension(const std::string& p)
// {
//     return splitExtension(p).second;
// }

// std::string join(const std::string& left, const std::string& right)
// {
//     if (left.empty())
//         return right;
//     else if (right.empty())
//         return left;

//     bool sepL = left.back() == DirSep;
//     bool sepR = right.front() == DirSep;
//     if (sepL && sepR)
//         return std::string(left.begin(), left.end() - 1) + right;
//     else if (sepL || sepR)
//         return left + right;
//     else
//         return left + DirSepStr + right;
// }

// std::string normalize(const std::string& p)
// {
//     std::vector<std::string> result;
//     std::vector<std::string> parts = split(p);
//     for (std::vector<std::string>::const_iterator it = parts.begin(); it != parts.end(); it++)
//     {
//         if (*it == "..")
//         {
//             if (result.empty() || result.back() == "..")
//                 result.push_back(*it);
//             else if (!result.back().empty())
//                 result.pop_back();
//         }
//         else if (*it != "." && (result.empty() || !it->empty()))
//         {
//             result.push_back(*it);
//         }
//     }
//     if (result.empty() && !parts.empty())
//         return std::string(".");
//     else
//         return String::join(result, DirSepStr);
// }

// std::string removeExtension(const std::string& p)
// {
//     return splitExtension(p).first;
// }

// std::vector<std::string> split(const std::string path)
// {
//     return String::splitToken(path, DirSep);
// }

// std::pair<std::string, std::string> splitExtension(const std::string& p)
// {
//     std::pair<std::string, std::string> parts = String::splitLastToken(p, (uint32_t)'.');
//     if (parts.first.empty() || parts.second.empty() || parts.first.back() == DirSep)
//         return std::make_pair(p, std::string());
//     return parts;
// }

// std::string getOSXDefaultPath()
// {
//     std::ifstream file("/etc/paths");
//     if (!file)
//         return std::string();
//     std::string result;
//     while (!file.eof())
//     {
//         std::string line;
//         getline(file, line);
//         if (!line.empty())
//         {
//             if (!result.empty())
//                 result += ":";
//             result += line;
//         }
//     }
//     return result;
// }

// void listDir(std::vector<std::string>& dirs, const std::string& path)
// {
//     // Unix
//     // len = strlen(name);
//     // dirp = opendir(".");
//     // while ((dp = readdir(dirp)) != NULL)
//     //     if (dp->d_namlen == len && !strcmp(dp->d_name, name)) {
//     //         (void)closedir(dirp);
//     //         return FOUND;
//     //     }
//     // (void)closedir(dirp);
//     // return NOT_FOUND;

//     // Win32
//     // #include <windows.h>
//     // #include <tchar.h>
//     // #include <stdio.h>

//     // void _tmain(int argc, TCHAR *argv[])
//     // {
//     //    WIN32_FIND_DATA FindFileData;
//     //    HANDLE hFind;

//     //    if( argc != 2 )
//     //    {
//     //       _tprintf(TEXT("Usage: %s [target_file]\n"), argv[0]);
//     //       return;
//     //    }

//     //    _tprintf (TEXT("Target file is %s\n"), argv[1]);
//     //    hFind = FindFirstFile(argv[1], &FindFileData);
//     //    if (hFind == INVALID_HANDLE_VALUE)
//     //    {
//     //       printf ("FindFirstFile failed (%d)\n", GetLastError());
//     //       return;
//     //    }
//     //    else
//     //    {
//     //       _tprintf (TEXT("The first file found is %s\n"),
//     //                 FindFileData.cFileName);
//     //       FindClose(hFind);
//     //    }
//     // }
// }

// }
// }}
