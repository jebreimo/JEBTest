#ifndef JEB_SYS_DIRECTORY_HPP
#define JEB_SYS_DIRECTORY_HPP

#include <string>
#include "DirectoryIterator.hpp"

namespace JEB { namespace Sys {

class Directory
{
public:
    Directory();
    Directory(const std::string& path);

    std::string path() const;
    std::string name() const;

    DirectoryIterator begin() const;
    DirectoryIterator end() const;

    bool exists() const;
private:
    std::string m_Path;
};

}}

#endif
