#ifndef JEB_SYS_DIRECTORYITERATOR_WIN32_HPP
#define JEB_SYS_DIRECTORYITERATOR_WIN32_HPP

#define NOMINMAX

#include <iterator>
#include <string>
#include <windows.h>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Sys {

class Directory;

class DirectoryIterator : std::iterator<std::input_iterator_tag, std::string, void, void, void>
{
public:
    static DirectoryIterator begin(const Directory* directory, const std::string& path);
    static DirectoryIterator end(const Directory* directory, const std::string& path);

    DirectoryIterator(const Directory* directory);
    DirectoryIterator(DirectoryIterator&& other);
    DirectoryIterator(const DirectoryIterator& other);
    ~DirectoryIterator();

    DirectoryIterator& operator=(DirectoryIterator&& other);
    DirectoryIterator& operator=(const DirectoryIterator&);

    bool operator==(const DirectoryIterator& other) const;
    bool operator!=(const DirectoryIterator& other) const;

    DirectoryIterator& operator++();
    DirectoryIterator operator++(int);

    std::string operator*() const;

    const WIN32_FIND_DATA* data() const;
private:
    void findFirst(const std::string& path);

    const Directory* m_Directory;
    HANDLE m_hFind;
    WIN32_FIND_DATA m_FindData;
};

}}

#endif