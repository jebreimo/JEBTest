#ifndef ARGPARSERIMPL_HPP
#define ARGPARSERIMPL_HPP

#include <iosfwd>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "ArgParser.hpp"

/** @file
  * @brief Defines the ArgParserImpl class.
  */

namespace JEB
{

class ArgIterator;
class HelpTextFormatter;

typedef std::unique_ptr<ParsedArgs> ParsedArgs_p;

/** @brief Parses command line arguments and writes nicely formatted
  *     help texts.
  */
class ArgParserImpl
{
public:
    ArgParserImpl(ArgParser* owner);
    ~ArgParserImpl();

    ArgIterator* argIterator();
    const ArgIterator* argIterator() const;

    HelpTextFormatter* helpTextFormatter();
    const HelpTextFormatter* helpTextFormatter() const;

    bool ignoreArguments() const;
    void setIgnoreArguments(bool ignoreAguments);

    bool optionsPrecedeArguments() const;
    void setOptionsPrecedeArguments(bool optionsPrecedeArguments);

    const std::string& programName() const;
    void setProgramName(const std::string& programName);

    bool ignoreUnknownOptions() const;
    void setIgnoreUnknownOptions(bool ignoreUnknownOptions);

    /** @brief Adds @a helpText to the help text.
      *
      * Use this function to add usage instructions, headings or any other
      * you want interspersed with your options.
      *
      * @note Any instances of "%prog" in the @a helpText is replaced with the
      * file name part of argv[0].
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
    static void handleList(ArgParser* argParser,
                           const OptionData* od);
    static void handleOption(ArgParser* argParser,
                             const OptionData* od);
    static void handleValue(ArgParser* argParser,
                            const OptionData* od);
    static void handleListValue(ArgParser* argParser,
                                const OptionData* od);

    void addCallback(const std::string& opts,
                     OptionCallback callback,
                     void* context,
                     const std::string& valueName,
                     const std::string& help);

    std::auto_ptr<ArgIterator> m_ArgIt;
    std::auto_ptr<HelpTextFormatter> m_HelpTextFormatter;

    bool m_IgnoreArguments;
    bool m_OptionsPrecedeArguments;

    typedef std::pair<OptionCallback, void*> OptionCallbackWithContext;
    std::map<std::string, OptionCallbackWithContext> m_OptionCallbacks;

    std::list<std::string> m_OptionCallbackContexts;

    bool m_IgnoreUnknownOptions;

    typedef std::pair<std::string, std::string> ValueCallbackContext;
    std::list<ValueCallbackContext> m_ValueCallbackContexts;

    ArgParser* m_Owner;
};

}

#endif // ARGPARSERIMPL_HPP
