#include "ParsedArgs.hpp"
#include "JEB/String/MapUtilities.hpp"

namespace JEB { namespace ArgParser {

std::string ParsedArgs::s_EmptyString;
ParsedArgs::StringList ParsedArgs::s_EmptyStringList;

ParsedArgs::ParsedArgs()
{
}

ParsedArgs::ParsedArgs(ParsedArgs&& rhs)
    : m_Options(std::move(rhs.m_Options)),
      m_ListOptions(std::move(rhs.m_ListOptions)),
      m_Arguments(std::move(rhs.m_Arguments)),
      m_InvalidOptions(std::move(rhs.m_InvalidOptions))
{
}

ParsedArgs::~ParsedArgs()
{
}

ParsedArgs& ParsedArgs::operator=(ParsedArgs&& rhs)
{
    m_Options = std::move(rhs.m_Options);
    m_ListOptions = std::move(rhs.m_ListOptions);
    m_Arguments = std::move(rhs.m_Arguments);
    m_InvalidOptions = std::move(rhs.m_InvalidOptions);
    return *this;
}

ParsedArgs::operator bool() const
{
    return m_InvalidOptions.empty();
}

bool ParsedArgs::operator!() const
{
    return !m_InvalidOptions.empty();
}

const std::string& ParsedArgs::argument(size_t index) const
{
    return m_Arguments[index];
}

void ParsedArgs::addArgument(const std::string& arg)
{
    m_Arguments.push_back(arg);
}

size_t ParsedArgs::argumentCount() const
{
    return m_Arguments.size();
}

const std::vector<std::string>& ParsedArgs::arguments() const
{
    return m_Arguments;
}

size_t ParsedArgs::invalidOptionCount() const
{
    return m_InvalidOptions.size();
}

void ParsedArgs::invalidOption(size_t index, std::string& option, std::string& reason) const
{
    option = m_InvalidOptions[index].first;
    reason = m_InvalidOptions[index].second;
}

void ParsedArgs::addInvalidOption(const std::string& option, const std::string& reason)
{
    m_InvalidOptions.push_back(std::make_pair(option, reason));
}

std::vector<char*> ParsedArgs::unprocessedArgs() const
{
    std::vector<char*> tmp;
    if (tmp.empty())
    {
        for (auto str = m_UnprocessedArgs.begin(); str != m_UnprocessedArgs.end(); ++str)
            tmp.push_back(const_cast<char*>(str->c_str()));
    }
    return tmp;
}

void ParsedArgs::addUnprocessedArg(const std::string& arg)
{
    m_UnprocessedArgs.push_back(arg);
}

const std::vector<std::string>& ParsedArgs::list(const std::string& name) const
{
    StringListMap::const_iterator it = m_ListOptions.find(name);
    if (it == m_ListOptions.end())
        return s_EmptyStringList;
    else
        return it->second;
}

void ParsedArgs::addListValue(const std::string& name, const std::string& value)
{
    m_ListOptions[name].push_back(value);
}

bool ParsedArgs::hasOption(const std::string& name) const
{
    return m_Options.find(name) != m_Options.end();
}

const std::string& ParsedArgs::option(const std::string& name) const
{
    auto it = m_Options.find(name);
    return it != m_Options.end() ? it->second : s_EmptyString;
}

void ParsedArgs::setOption(const std::string& name, const std::string& value)
{
    m_Options[name] = value;
}

}}
