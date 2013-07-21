#ifndef JEB_PARSEDARGS_HPP
#define JEB_PARSEDARGS_HPP

#include <map>
#include <string>
#include <vector>
#include <JEB/String/FromString.hpp>

namespace JEB { namespace ArgParser {

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

    /** @brief Returns unrecognized options in a data structure suitable for
     *      passing on to other option parsers.
     *
     *  Returns a vector containing any unrecognized options given to
     *  ArgParser::parseif
     *  ArgParser::treatUnrecognizedOptionsAsErrors is false.
     *
     *  @note The strings in the returned value are deleted by the
     *      destructor of ParsedArgs. Don't try to free them or use them
     *      after the ParsedArgs instance that returned them is deleted or
     *      goes out of scope.
     */
    std::vector<char*> unprocessedArgs() const;
    void addUnprocessedArg(const std::string& arg);

    const std::vector<std::string>& list(const std::string& name) const;
    void addListValue(const std::string& name, const std::string& value);

    bool hasOption(const std::string& name) const;
    const std::string& option(const std::string& name) const;
    void setOption(const std::string& name, const std::string& value);

    template <typename T>
    T option(const std::string& name, T&& defaultValue) const
    {
        T value;
        if (!hasOption(name) || !JEB::String::fromString(option(name), value))
            return defaultValue;
        return value;
    }

    template <typename T>
    bool tryGetOption(const std::string& name, T& value) const
    {
        return hasOption(name) && JEB::String::fromString(option(name), value);
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
    StringList m_UnprocessedArgs;
    OptionErrorList m_InvalidOptions;
    static std::string s_EmptyString;
    static StringList s_EmptyStringList;
};

}}

#endif
