#ifndef JEB_SYS_POSIX_FILEINFO_HPP
#define JEB_SYS_POSIX_FILEINFO_HPP

#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Sys { namespace Posix {

class FileInfo
{
public:
    const std::string& name() const;
    uint64_t size() const;
    uid_t userId() const;
    gid_t groupId() const;
    
};

}}}

#endif
