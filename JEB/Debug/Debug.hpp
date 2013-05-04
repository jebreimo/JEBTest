#ifndef JEB_DEBUG_HPP
#define JEB_DEBUG_HPP

#include <iomanip>
#include <iostream>
#include "CpuTimer.hpp"

#ifdef JEB_USE_EXTERN_DEST
extern std::ostream* JEB_Stream;
#else
static std::ostream* JEB_Stream = &std::clog;
#endif

#define JEB_CHECKPOINT() \
    *JEB_Stream << __FILE__ "[" << __LINE__ << "]: " << __FUNCTION__ \
                << std::endl
#define JEB_MESSAGE(msg) \
    *JEB_Stream << __FILE__ "[" << __LINE__ << "]: " << __FUNCTION__ \
                << "\n\t" << msg << std::endl
#define JEB_SHOW(var) \
    *JEB_Stream << __FILE__ "[" << __LINE__ << "]: " << __FUNCTION__ \
                << "\n\t" #var " = " << (var) << std::endl
#define JEB_SHOW2(var1, var2) \
    *JEB_Stream << __FILE__ "[" << __LINE__ << "]: " << __FUNCTION__ \
                << "\n\t" #var1 " = " << (var1) \
                << "\n\t" #var2 " = " << (var2) << std::endl
#define JEB_SHOW3(var1, var2, var3) \
    *JEB_Stream << __FILE__ "[" << __LINE__ << "]: " << __FUNCTION__ \
                << "\n\t" #var1 " = " << (var1) \
                << "\n\t" #var2 " = " << (var2) \
                << "\n\t" #var3 " = " << (var3) << std::endl
#define JEB_SHOW4(var1, var2, var3, var4) \
    *JEB_Stream << __FILE__ "[" << __LINE__ << "]: " << __FUNCTION__ \
                << "\n\t" #var1 " = " << (var1) \
                << "\n\t" #var2 " = " << (var2) \
                << "\n\t" #var3 " = " << (var3) \
                << "\n\t" #var4 " = " << (var4) << std::endl
#define JEB_SHOW5(var1, var2, var3, var4, var5) \
    *JEB_Stream << __FILE__ "[" << __LINE__ << "]: " << __FUNCTION__ \
                << "\n\t" #var1 " = " << (var1) \
                << "\n\t" #var2 " = " << (var2) \
                << "\n\t" #var3 " = " << (var3) \
                << "\n\t" #var4 " = " << (var4) \
                << "\n\t" #var5 " = " << (var5) << std::endl

#define JEB_PRIVATE_UNIQUE_NAME_EXPANDER2(name, lineno) name##_##lineno
#define JEB_PRIVATE_UNIQUE_NAME_EXPANDER1(name, lineno) \
    JEB_PRIVATE_UNIQUE_NAME_EXPANDER2(name, lineno)
#define JEB_PRIVATE_UNIQUE_NAME(name) \
    JEB_PRIVATE_UNIQUE_NAME_EXPANDER1(name, __LINE__)

#define JEB_PRIVATE_AS_STRING_TRICK(a) #a
#define JEB_PRIVATE_AS_STRING(a) JEB_PRIVATE_AS_STRING_TRICK(a)

#define JEB_PRIVATE_CONTEXT() \
    (std::string(__FILE__ "[" JEB_PRIVATE_AS_STRING(__LINE__) "]: ") + \
    __FUNCTION__)

#define JEB_TIMEIT() \
    ::JEB::ScopedTimer JEB_PRIVATE_UNIQUE_NAME(JEB_ScopedTimer) \
        (JEB_PRIVATE_CONTEXT() + "\n\telapsed time = ", *JEB_Stream)

namespace JEB { namespace internal { namespace debug {

    template <typename It>
    void write(std::ostream& os, It begin, It end)
    {
        if (begin != end)
            os << *begin++;
        for (; begin != end; begin++)
            os << ", " << *begin;
    }

    template <typename Container>
    void writeContainer(std::ostream& os, const Container& c)
    {
        write(os, std::begin(c), std::end(c));
    }

    template <typename It>
    void writePretty(std::ostream& os, It begin, It end)
    {
        size_t i = 0;
        for (; begin != end; begin++)
            os << std::setw(6) << i++ << ": " << *begin << "\n\t";
    }

    template <typename Container>
    void writeContainerPretty(std::ostream& os, const Container& c)
    {
        writePretty(os, std::begin(c), std::end(c));
    }
}}}

#define JEB_SHOW_RANGE(begin, end) \
    { \
        *JEB_Stream << __FILE__ "[" << __LINE__ \
                    << "]:\n\t(" #begin " ... " #end ") = ["; \
        ::JEB::internal::debug::write(*JEB_Stream, (begin), (end)); \
        *JEB_Stream << "]" << std::endl; \
    }

#define JEB_SHOW_CONTAINER(c) \
    { \
        *JEB_Stream << __FILE__ "[" << __LINE__ << "]: " << __FUNCTION__ \
                    << "\n\t" #c " = ["; \
        ::JEB::internal::debug::writeContainer(*JEB_Stream, (c)); \
        *JEB_Stream << "]" << std::endl; \
    }

#define JEB_PRETTY_RANGE(begin, end) \
    { \
        *JEB_Stream << __FILE__ "[" << __LINE__ \
                    << "]:\n\t(" #begin " ... " #end ") = [\n\t"; \
        ::JEB::internal::debug::writePretty(*JEB_Stream, (begin), (end)); \
        *JEB_Stream << "]" << std::endl; \
    }

#define JEB_PRETTY_CONTAINER(c) \
    { \
        *JEB_Stream << __FILE__ "[" << __LINE__ << "]: " << __FUNCTION__ \
                    << "\n\t" #c " = [\n\t"; \
        ::JEB::internal::debug::writeContainerPretty(*JEB_Stream, (c)); \
        *JEB_Stream << "]" << std::endl; \
    }

#endif
