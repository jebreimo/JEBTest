#ifndef JEB_ARGITERATOR_HPP
#define JEB_ARGITERATOR_HPP

#include <set>
#include <string>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace ArgParser {

class ArgIterator
{
public:
    enum ArgumentType
    {
        None,
        Argument,
        Flag,
        Option,
        InvalidFlag,
        InvalidOption,
        UnknownOption
    };

    ArgIterator();

    bool ignoresOptions() const;
    void setIgnoresOptions(bool ignoresOptions);

    const char* argument() const;
    const std::string& name() const;
    ArgumentType type() const;
    const std::string& value() const;

    void addFlag(const std::string& flag);
    void removeFlag(const std::string& flag);
    void addOption(const std::string& option);
    void removeOption(const std::string& option);

    void setArguments(int argc, const char* const * argv);
    bool nextArgument();
private:
    void nextLongOption();
    void nextShortOption();

    int m_Argc;
    const char* const * m_Argv;
    std::string m_CurrentValue;
    std::string m_CurrentName;
    ArgumentType m_CurrentType;
    std::set<std::string> m_Flags;
    bool m_IgnoresOptions;
    int m_Index;
    std::set<std::string> m_Options;
    int m_SubIndex;
};

}}

#endif
