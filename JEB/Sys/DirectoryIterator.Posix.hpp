#ifndef JEB_SYS_DIRECTORYITERATOR_POSIX_HPP
#define JEB_SYS_DIRECTORYITERATOR_POSIX_HPP

#include <iterator>
#include <string>
#include <dirent.h>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Sys {

class Directory;

class DirectoryIterator : std::iterator<std::input_iterator_tag, std::string, void, void, void>
{
public:
    static DirectoryIterator begin(const Directory* directory, const std::string& path);
    static DirectoryIterator end(const Directory* directory, const std::string& path);

    DirectoryIterator(const Directory* directory, DIR* dir);
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

    std::pair<DIR*, dirent*> data() const;
private:
    const Directory* m_Directory;
    DIR* m_Dir;
    dirent* m_Entry;
};

}}

#endif