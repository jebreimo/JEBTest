#include "Users.hpp"
#include <stdexcept>
#include <LMCons.h>
#include <ShlObj.h>
#include <Windows.h>

namespace JEB { namespace Sys { namespace Users {

int userId()
{
    throw std::logic_error("userId() not supported in Windows");
}

std::string userName()
{
    char buffer[UNLEN + 1];
    DWORD size = sizeof(buffer) / sizeof(*buffer);
    GetUserNameA(buffer, &size);
    // TODO: use wchar_t-version and convert to utf-8
    return std::string(buffer);
}

std::string userName(int uid)
{
    throw std::logic_error("userId() not supported in Windows");
}

std::string homePath()
{
    wchar_t* path;
    HRESULT result = SHGetKnownFolderPath(FOLDERID_UsersFiles, 0, NULL, &path);
    // TODO: convert path to utf-8.
    return std::string();
}

std::string homePath(int uid)
{
    throw std::logic_error("homePath(uid) not supported in Windows");
}

std::string homePath(const std::string& login)
{
    return std::string();
}

}}}
