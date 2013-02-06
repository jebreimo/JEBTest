#include "Users.hpp"
#include <pwd.h>
#include <unistd.h>

namespace JEB { namespace Sys { namespace Users {

int userId()
{
    return getuid();
}

int groupId()
{
    return getgid();
}

std::string userName()
{
    return userName(userId());
}

std::string userName(int uid)
{
    passwd* p = getpwuid(uid);
    if (!p)
        return std::string();

    return std::string(p->pw_name);
}

std::string homePath()
{
    return homePath(userId());
}

std::string homePath(int uid)
{
    passwd* p = getpwuid(uid);
    if (!p)
        return std::string();
    return std::string(p->pw_dir);
}

std::string homePath(const std::string& login)
{
    passwd* p = getpwnam(login.c_str());
    if (!p)
        return std::string();
    return std::string(p->pw_dir);
}

}}}
