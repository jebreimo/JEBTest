#ifndef JEB_SYS_USERS_HPP
#define JEB_SYS_USERS_HPP

#include <string>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Sys { namespace Users {

int userId();
int groupId();

std::string userName();
std::string userName(int uid);

std::string homePath();
std::string homePath(int uid);
std::string homePath(const std::string& login);

}}}

#endif
