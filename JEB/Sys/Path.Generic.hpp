#include <string>
#include <utility>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Sys { namespace Path { namespace Generic {


/** @brief Returns the extension of path @a p, including the leading ".".

    If @a p doesn't have any extension, the function returns the
    empty string.
*/
std::string extension(const std::string& p);

std::string removeExtension(const std::string& p;

std::pair<std::string, std::string> splitExtension(const std::string& p);

}}}}
