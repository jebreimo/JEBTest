#ifndef JEB_ARGPARSER_HPP
#define JEB_ARGPARSER_HPP

#include <iosfwd>
#include <memory>
#include <string>
#include "OptionData.hpp"
#include "ParsedArgs.hpp"

/** @file
  * @brief Defines the ArgParser class.
  */

namespace JEB
{

class ArgIterator;
class ArgParser;
class ArgParserImpl;
class HelpTextFormatter;
struct OptionData;

typedef void (*OptionCallback)(ArgParser* argParser,
                               const OptionData* optionData);

/** @brief Parses command line arguments and writes nicely formatted
  *     help texts.
  */
class ArgParser
{
public:
    ArgParser();
    ArgParser(ArgParser&& rhs);
    ~ArgParser();
    ArgParser& operator=(ArgParser&& rhs);

    ArgIterator* argIterator();
    const ArgIterator* argIterator() const;

    HelpTextFormatter* helpTextFormatter();
    const HelpTextFormatter* helpTextFormatter() const;

    ArgParserImpl* impl();
    const ArgParserImpl* impl() const;

    bool optionsPrecedeArguments() const;
    void setOptionsPrecedeArguments(bool optionsPrecedeArguments);

    const std::string& programName() const;
    void setProgramName(const std::string& programName);

    const std::string& usage() const;

    /** @brief Set the "usage" part of the help text.
      *
      * Any instances of "%prog" in the usage text is replaced with the
      * file name part argv[0].
      */
    void setUsage(const std::string& usage);

    void addFlag(const std::string& opts,
                 bool enable,
                 const std::string& name,
                 const std::string& help);
    void addValue(const std::string& opts,
                  const std::string& value,
                  const std::string& name,
                  const std::string& help);
    void addOption(const std::string& opts,
                   const std::string& name,
                   const std::string& valueName,
                   const std::string& help);
    void addList(const std::string& opts,
                 const std::string& name,
                 const std::string& valueName,
                 const std::string& help);
    void addListValue(const std::string& opts,
                      const std::string& value,
                      const std::string& name,
                      const std::string& help);
    void addFlagCallback(const std::string& opts,
                         OptionCallback callback,
                         void* context,
                         const std::string& help);
    void addOptionCallback(const std::string& opts,
                           OptionCallback callback,
                           void* context,
                           const std::string& valueName,
                           const std::string& help);

    ParsedArgs parse(int argc, const char* const * argv);
    bool parse(int argc, const char* const * argv, ParsedArgs& args);

    bool processCurrentArg(ParsedArgs& args);

    void writeHelp() const;
    void writeHelp(std::ostream& os) const;
    void writeErrors(const ParsedArgs& pa) const;
    void writeErrors(std::ostream& os, const ParsedArgs& pa) const;
    void writeMessage(const std::string& msg) const;
    void writeMessage(std::ostream& os, const std::string& msg) const;
private:
    std::unique_ptr<ArgParserImpl> m_Impl;
};

}

#endif
