#ifndef JEB_SYS_PATH_HPP
#define JEB_SYS_PATH_HPP


#if defined(__APPLE__)
    #define JEB_IS_POSIX
#else
    #define JEB_IS_WIN
#endif

#if defined(JEB_IS_POSIX)
    #include "Path.Posix.hpp"
    namespace JEB { namespace Sys { namespace Path {
        using namespace JEB::Sys::Path::Posix;
    }}}
#elif defined(JEB_IS_WIN)
    #include "Path.Win.hpp"
    namespace JEB { namespace Sys { namespace Path {
        using namespace JEB::Sys::Path::Win;
    }}}
#endif

// #include <string>
// #include <vector>

// TODO: Create Path.Common.hpp, Path.Posix.hpp and Path.Win.hpp, and make Path.hpp a system-sensitive wrapper.
// TODO: Path.hpp should be a simple "using namespace JEB::Sys::WinPath" etc.

// namespace JEB { namespace Sys {namespace Path
// {

// // std::string absPath(const std::string& p);

// std::string baseName(const std::string& p);

// // std::string commonPrefix(const std::string& a, const std::string& b);

// // std::string commonSuffix(const std::vector<std::string>& names);

// std::string currentPath();

// // std::string dirName();

// // uint32_t dirSeparator();

// // namespace ExistsFlags
// // {
// //     enum Enum
// //     {
// //         FollowSymbolicLinks
// //     };
// // }

// // bool exists(const std::string& str, ExistsFlags::Enum flags);

// // std::string expandVars(const std::string& path);

// std::string expandUser(const std::string& path);

// // time_t accessTime(const std::string& path);
// // time_t creationTime(const std::string& path);
// // time_t modificationTime(const std::string& path);

// // size_t size(const std::string& path);

// // bool isAbsPath(const std::string& path);

// // bool isDir(const std::string& path);
// // bool isExecutable(const std::string& path);
// // bool isFile(const std::string& path);
// // bool isSymLink(const std::string& path);
// // bool isMount(const std::string& path);
// // std::string normalizeCase(const std::string& path);
// // std::string realPath(const std::string& path);
// // std::string relativePath(const std::string& path);
// // bool areSameFile(const std::string& path1, const std::string& path2);

// // std::pair<std::string, std::string> splitDrive(const std::string& path);
// // std::pair<std::string, std::string> splitUnc(const std::string& path);

// // bool supportsUnicode();

// /** @brief Returns the extension of path @a p, including the leading ".".

//     If @a p doesn't have any extension, the function returns the
//     empty string.
// */
// std::string extension(const std::string& p);

// std::string homePath();

// std::string join(const std::string& left, const std::string& right);

// std::string normalize(const std::string& p);

// // std::string pathList();

// // uint32_t pathListSeparator();

// std::string removeExtension(const std::string& p);

// std::pair<std::string, std::string> split(const std::string path);

// void splitExtension(std::string& name,
//                     std::string& extension,
//                     const std::string& p);

// std::pair<std::string, std::string> splitExtension(const std::string& p);

// // std::string getSystemDefaultPathList();

// std::string getOSXDefaultPath();

// }}}

// #include "Path_Impl.hpp"

#endif
