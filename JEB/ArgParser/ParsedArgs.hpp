#ifndef JEB_PARSEDARGS_HPP
#define JEB_PARSEDARGS_HPP

#include <map>
#include <string>
#include <vector>
#include "JEB/Collections/MapUtilities.hpp"

namespace JEB
{

class ParsedArgs
{
public:
    ParsedArgs();
    ParsedArgs(ParsedArgs&& rhs);
    ~ParsedArgs();

    ParsedArgs& operator=(ParsedArgs&& rhs);
#if _MSC_VER < 1800
    operator bool() const;
#else
    explicit operator bool() const;
#endif
    bool operator!() const;

    size_t argumentCount() const;
    const std::string& argument(size_t index) const;
    void addArgument(const std::string& arg);
    const std::vector<std::string>& arguments() const;

    size_t invalidOptionCount() const;
    void invalidOption(size_t index, std::string& option, std::string& reason) const;
    void addInvalidOption(const std::string& option, const std::string& reason);

    const std::vector<std::string>& list(const std::string& name) const;
    void addListValue(const std::string& name, const std::string& value);

    template <typename T>
    T option(const std::string& name, const T& defaultValue) const
    {
        return JEB::StringMap::get(m_Options, name, defaultValue);
    }

    template <typename T>
    bool tryGetOption(const std::string& name, T& value) const
    {
        return JEB::StringMap::tryGet(m_Options, name, value);
    }

    template <typename T>
    void setOption(const std::string& name, const T& value)
    {
        JEB::StringMap::set(m_Options, name, value);
    }
private:
    typedef std::map<std::string, std::string> StringMap;
    typedef std::vector<std::string> StringList;
    typedef std::map<std::string, StringList> StringListMap;
    typedef std::pair<std::string, std::string> OptionError;
    typedef std::vector<OptionError> OptionErrorList;
    StringMap m_Options;
    StringListMap m_ListOptions;
    StringList m_Arguments;
    OptionErrorList m_InvalidOptions;
    static StringList s_EmptyStringList;
};

}

#endif
