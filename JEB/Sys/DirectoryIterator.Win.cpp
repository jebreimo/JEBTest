#include "DirectoryIterator.Win.hpp"

#include <cassert>
#include <stdexcept>
#include "Directory.hpp"

namespace JEB { namespace Sys {

DirectoryIterator DirectoryIterator::begin(const Directory* directory, const std::string& path)
{
    DirectoryIterator di(directory);
    di.findFirst(path);
    return di;
}

DirectoryIterator DirectoryIterator::end(const Directory* directory, const std::string& path)
{
    return DirectoryIterator(directory);
}

DirectoryIterator::DirectoryIterator(const Directory* directory)
    : m_Directory(directory),
      m_hFind(NULL)
{
    assert(directory);
}

DirectoryIterator::DirectoryIterator(const DirectoryIterator& other)
    : m_Directory(other.m_Directory),
      m_hFind(NULL)
{
    if (other.m_hFind)
    {
        findFirst(m_Directory->path());
        if (!m_hFind)
            throw std::runtime_error("Unable to copy DirectoryIterator");
        while (**this != *other && FindNextFile(m_hFind, &m_FindData))
            ;
    }
}

DirectoryIterator::DirectoryIterator(DirectoryIterator&& other)
    : m_Directory(other.m_Directory),
      m_hFind(NULL)
{
    std::swap(m_hFind, other.m_hFind);
    m_FindData = other.m_FindData;
}

DirectoryIterator::~DirectoryIterator()
{
    if (m_hFind)
        FindClose(m_hFind);
}

DirectoryIterator& DirectoryIterator::operator=(const DirectoryIterator& other)
{
    DirectoryIterator copy = other;
    std::swap(m_Directory, copy.m_Directory);
    std::swap(m_hFind, copy.m_hFind);
    m_FindData = copy.m_FindData;
    return *this;
}

DirectoryIterator& DirectoryIterator::operator=(DirectoryIterator&& other)
{
    std::swap(m_Directory, other.m_Directory);
    std::swap(m_hFind, other.m_hFind);
    m_FindData = other.m_FindData;
    return *this;
}

bool DirectoryIterator::operator==(const DirectoryIterator& other) const
{
    return m_Directory == other.m_Directory;
}

bool DirectoryIterator::operator!=(const DirectoryIterator& other) const
{
    return m_Directory != other.m_Directory;
}

DirectoryIterator& DirectoryIterator::operator++()
{
    if (m_hFind && !FindNextFile(m_hFind, &m_FindData))
    {
        FindClose(m_hFind);
        m_hFind = NULL;
    }
    return *this;
}

DirectoryIterator DirectoryIterator::operator++(int)
{
    DirectoryIterator copy = *this;
    if (m_hFind && !FindNextFile(m_hFind, &m_FindData))
    {
        FindClose(m_hFind);
        m_hFind = NULL;
    }
    return copy;
}

std::string DirectoryIterator::operator*() const
{
    return std::string(m_FindData.cFileName);
}

const WIN32_FIND_DATA* DirectoryIterator::data() const
{
    return &m_FindData;
}

void DirectoryIterator::findFirst(const std::string& path)
{
    m_hFind = FindFirstFile(path.c_str(), &m_FindData);
}

}}
