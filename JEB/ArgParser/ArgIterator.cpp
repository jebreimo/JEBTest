#include "ArgIterator.hpp"
#include "JEB/Collections/SetUtilities.hpp"
#include "JEB/String/String.hpp"

namespace JEB { namespace ArgParser {

ArgIterator::ArgIterator()
    : m_Argc(0),
      m_Argv(NULL),
      m_CurrentType(None),
      m_IgnoresOptions(false),
      m_Index(-1),
      m_SubIndex(0)
{
}

bool ArgIterator::ignoresOptions() const
{
    return m_IgnoresOptions;
}

void ArgIterator::setIgnoresOptions(bool ignoresOptions)
{
    m_IgnoresOptions = ignoresOptions;
}

const char* ArgIterator::argument() const
{
    if (m_Index >= m_Argc)
        return nullptr;
    return m_Argv[m_Index];
}

const std::string& ArgIterator::name() const
{
    return m_CurrentName;
}

ArgIterator::ArgumentType ArgIterator::type() const
{
    return m_CurrentType;
}

const std::string& ArgIterator::value() const
{
    return m_CurrentValue;
}

void ArgIterator::addFlag(const std::string& flag)
{
    m_Flags.insert(flag);
}

void ArgIterator::removeFlag(const std::string& flag)
{
    m_Flags.erase(flag);
}

void ArgIterator::addOption(const std::string& option)
{
    m_Options.insert(option);
}

void ArgIterator::removeOption(const std::string& option)
{
    m_Options.erase(option);
}

void ArgIterator::setArguments(int argc, const char* const * argv)
{
    m_Argc = argc;
    m_Argv = argv;
    m_Index = -1;
    m_CurrentName.clear();
    m_CurrentValue.clear();
    m_CurrentType = None;
}

bool ArgIterator::nextArgument()
{
    if (m_Index >= m_Argc)
        return false;

    if (m_SubIndex != 0 && m_Argv[m_Index][m_SubIndex] == '\0')
        m_SubIndex = 0;
    if (m_SubIndex == 0 && ++m_Index == m_Argc)
    {
        m_CurrentName.clear();
        m_CurrentValue.clear();
        m_CurrentType = None;
        return false;
    }

    if (m_IgnoresOptions || m_Argv[m_Index][0] != '-' || m_Argv[m_Index][1] == '\0')
    {
        m_CurrentName.clear();
        m_CurrentType = Argument;
        if (m_SubIndex != 0)
        {
            m_CurrentValue = &m_Argv[m_Index][m_SubIndex];
            m_SubIndex = 0;
        }
        else
        {
            m_CurrentValue = m_Argv[m_Index];
        }
    }
    else if (m_SubIndex != 0)
    {
        nextShortOption();
    }
    else if (m_Argv[m_Index][1] != '-' || m_Argv[m_Index][2] == '\0')
    {
        m_SubIndex = 1;
        nextShortOption();
    }
    else
    {
        nextLongOption();
    }

    return true;
}

void ArgIterator::nextLongOption()
{
    std::vector<std::string> parts = String::split(m_Argv[m_Index], "=", 2);
    if (parts.size() == 1)
    {
        m_CurrentValue.clear();
        if (has(m_Flags, parts[0]))
            m_CurrentType = Flag;
        else if (has(m_Options, parts[0]))
            m_CurrentType = InvalidOption;
        else
            m_CurrentType = UnknownOption;
    }
    else
    {
        m_CurrentValue = parts[1];
        if (has(m_Options, parts[0]))
            m_CurrentType = Option;
        else if (has(m_Flags, parts[0]))
            m_CurrentType = InvalidFlag;
        else
            m_CurrentType = UnknownOption;
    }
    m_CurrentName = parts[0];
}

void ArgIterator::nextShortOption()
{
    char buf[2] = {'-', m_Argv[m_Index][m_SubIndex++]};
    m_CurrentName.assign(buf, 2);
    if (has(m_Flags, m_CurrentName))
    {
        m_CurrentValue.clear();
        m_CurrentType = Flag;
    }
    else if (has(m_Options, m_CurrentName))
    {
        if (m_Argv[m_Index][m_SubIndex] != '\0')
        {
            m_CurrentValue = &m_Argv[m_Index][m_SubIndex];
            m_CurrentType = Option;
        }
        else if (++m_Index != m_Argc)
        {
            m_CurrentValue = m_Argv[m_Index];
            m_CurrentType = Option;
        }
        else
        {
            m_CurrentValue.clear();
            m_CurrentType = InvalidOption;
        }
        m_SubIndex = 0;
    }
    else
    {
        m_CurrentValue.clear();
        m_CurrentType = UnknownOption;
    }
}

}}
