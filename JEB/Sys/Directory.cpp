#include "Directory.hpp"

#include "Path.hpp"

namespace JEB { namespace Sys {

Directory::Directory()
    : m_Path(Path::currentPath())
{
}

Directory::Directory(const std::string& path)
    : m_Path(Path::normalize(path))
{
}

bool Directory::exists() const
{
    return false;
}

std::string Directory::path() const
{
    return m_Path;
}

std::string Directory::name() const
{
    return Path::baseName(m_Path);
}

DirectoryIterator Directory::begin() const
{
    return DirectoryIterator::begin(this, m_Path);
}

DirectoryIterator Directory::end() const
{
    return DirectoryIterator::end(this, m_Path);
}

}}
