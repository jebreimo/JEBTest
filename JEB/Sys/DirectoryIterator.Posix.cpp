#include "DirectoryIterator.Posix.hpp"

#include <cassert>
#include <cstring>
#include <dirent.h>
#include <errno.h>
#include <stdexcept>
#include "Directory.hpp"

namespace JEB { namespace Sys {

DirectoryIterator DirectoryIterator::begin(const Directory* directory, const std::string& path)
{
    DIR* dir = opendir(path.c_str());
    if (!dir)
        throw std::runtime_error(strerror(errno));
    return DirectoryIterator(directory, dir);
}

DirectoryIterator DirectoryIterator::end(const Directory* directory, const std::string& path)
{
    return DirectoryIterator(directory, NULL);
}

DirectoryIterator::DirectoryIterator(const Directory* directory, DIR* dir)
    : m_Directory(directory),
      m_Dir(dir),
      m_Entry(NULL)
{
    assert(directory);
    if (dir)
        m_Entry = readdir(dir);
}

DirectoryIterator::DirectoryIterator(const DirectoryIterator& other)
    : m_Directory(other.m_Directory),
      m_Dir(NULL),
      m_Entry(NULL)
{
    if (other.m_Dir)
    {
        m_Dir = opendir(m_Directory->path().c_str());
        if (!m_Dir)
            throw std::runtime_error(strerror(errno));
        long ix = telldir(other.m_Dir);
        seekdir(m_Dir, ix ? ix - 1 : ix);
        m_Entry = readdir(m_Dir);
    }
}

DirectoryIterator::DirectoryIterator(DirectoryIterator&& other)
    : m_Directory(other.m_Directory),
      m_Dir(NULL),
      m_Entry(NULL)
{
    std::swap(m_Dir, other.m_Dir);
    std::swap(m_Entry, other.m_Entry);
}

DirectoryIterator::~DirectoryIterator()
{
    if (m_Dir)
        closedir(m_Dir);
}

DirectoryIterator& DirectoryIterator::operator=(const DirectoryIterator& other)
{
    DirectoryIterator copy = other;
    std::swap(m_Directory, copy.m_Directory);
    std::swap(m_Dir, copy.m_Dir);
    std::swap(m_Entry, copy.m_Entry);
    return *this;
}

DirectoryIterator& DirectoryIterator::operator=(DirectoryIterator&& other)
{
    std::swap(m_Directory, other.m_Directory);
    std::swap(m_Dir, other.m_Dir);
    std::swap(m_Entry, other.m_Entry);
    return *this;
}

bool DirectoryIterator::operator==(const DirectoryIterator& other) const
{
    return m_Directory == other.m_Directory &&
           m_Entry == other.m_Entry;
}

bool DirectoryIterator::operator!=(const DirectoryIterator& other) const
{
    return m_Directory != other.m_Directory ||
           m_Entry != other.m_Entry;
}

DirectoryIterator& DirectoryIterator::operator++()
{
    assert(m_Dir);
    m_Entry = readdir(m_Dir);
    return *this;
}

DirectoryIterator DirectoryIterator::operator++(int)
{
    assert(m_Dir);
    DirectoryIterator copy = *this;
    m_Entry = readdir(m_Dir);
    return copy;
}

std::string DirectoryIterator::operator*() const
{
    if (!m_Entry)
        throw std::logic_error("No directory entry.");
    return std::string(m_Entry->d_name, m_Entry->d_namlen);
}

std::pair<DIR*, dirent*> DirectoryIterator::data() const
{
    return std::make_pair(m_Dir, m_Entry);
}

}}
