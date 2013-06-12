#ifndef JEB_ARGPARSER_HPP
#define JEB_ARGPARSER_HPP

#include <iosfwd>
#include <memory>
#include <string>
#include "OptionData.hpp"
#include "ParsedArgs.hpp"

/** @file
  * @brief Defines the ArgParser class.
  *
  * How to process some options and pass all unrecognized arguments on
  * to another parser?
  * --------------------------------------------------------------------
  * Assuming there is a function
  *
  *     void otherArgumentFunction(int argc, char*[] argv);
  *
  * you can for instance do as follows:
  *
  *     ArgParser parser;
  *     parser.setIgnoreUnknownOptions();
  *     parser.setIgnoreArgs();
  *
  *     ... add the options that this parser should recognize ...
  *
  *     ParsedArgs args = parser.parse(argc, argv);
  *
  *     std::vector<char*> otherArgs = args.unprocessedArgs();
  *     otherArgumentFunction(otherArgs.size(), &otherArgs[0]);
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

    bool ignoreArguments() const;
    void setIgnoreArguments(bool ignoreAguments);

    ArgParserImpl* impl();
    const ArgParserImpl* impl() const;

    bool optionsPrecedeArguments() const;
    void setOptionsPrecedeArguments(bool optionsPrecedeArguments);

    const std::string& programName() const;
    void setProgramName(const std::string& programName);

    bool ignoreUnknownOptions() const;
    void setIgnoreUnknownOptions(bool ignoreUnknownOptions);

    /** @brief Set the "usage" part of the help text.
      *
      * Any instances of "%prog" in the usage text is replaced with the
      * file name part argv[0].
      */
    void addHelpText(const std::string& helpText);

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
