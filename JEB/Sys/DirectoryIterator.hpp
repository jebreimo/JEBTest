#ifndef JEB_SYS_DIRECTORYITERATOR_HPP
#define JEB_SYS_DIRECTORYITERATOR_HPP

#if defined(__APPLE__)
    #define JEB_IS_POSIX
#else
    #define JEB_IS_WIN
#endif

#if defined(JEB_IS_POSIX)
    #include "DirectoryIterator.Posix.hpp"
#elif defined(JEB_IS_WIN)
    #include "DirectoryIterator.Win.hpp"
#endif

#endif
