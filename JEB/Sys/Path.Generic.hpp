#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Sys { namespace Path { namespace Generic {

struct Parameters
{
    uint32_t dirSep;
    uint32_t pathSep;
    uint32_t extSep;
};

std::string baseName(const std::string& p, const Parameters& params);

/** @brief Returns the extension of path @a p, including the leading ".".

    If @a p doesn't have any extension, the function returns the
    empty string.
*/
std::string extension(const std::string& p, const Parameters& params);

std::string join(const std::string& left, const std::string& right,
                 const Parameters& params);

std::string normalize(const std::string& p, const Parameters& params);

std::string removeExtension(const std::string& p, const Parameters& params);

std::vector<std::string> split(const std::string path, const Parameters& params);

void splitExtension(std::string& name,
                    std::string& extension,
                    const std::string& p);

std::pair<std::string, std::string> splitExtension(const std::string& p);

}}}}
