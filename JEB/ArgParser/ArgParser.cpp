#include "ArgParser.hpp"

#include "ArgParserImpl.hpp"

namespace JEB { namespace ArgParser {

ArgParser::ArgParser()
{
  m_Impl.reset(new ArgParserImpl(this));
}

ArgParser::ArgParser(ArgParser&& rhs)
    : m_Impl(std::move(rhs.m_Impl))
{
}

ArgParser::~ArgParser()
{
}

ArgParser& ArgParser::operator=(ArgParser&& rhs)
{
    m_Impl = std::move(rhs.m_Impl);
    return *this;
}

ArgIterator* ArgParser::argIterator()
{
    return m_Impl->argIterator();
}

const ArgIterator* ArgParser::argIterator() const
{
    return m_Impl->argIterator();
}

HelpTextFormatter* ArgParser::helpTextFormatter()
{
    return m_Impl->helpTextFormatter();
}

const HelpTextFormatter* ArgParser::helpTextFormatter() const
{
    return m_Impl->helpTextFormatter();
}

bool ArgParser::ignoreArguments() const
{
    return m_Impl->ignoreArguments();
}

void ArgParser::setIgnoreArguments(bool ignoreAguments)
{
    m_Impl->setIgnoreArguments(ignoreAguments);
}

ArgParserImpl* ArgParser::impl()
{
    return m_Impl.get();
}

const ArgParserImpl* ArgParser::impl() const
{
    return m_Impl.get();
}

bool ArgParser::optionsPrecedeArguments() const
{
    return m_Impl->optionsPrecedeArguments();
}

void ArgParser::setOptionsPrecedeArguments(bool optionsPrecedeArguments)
{
    m_Impl->setOptionsPrecedeArguments(optionsPrecedeArguments);
}

const std::string& ArgParser::programName() const
{
    return m_Impl->programName();
}

void ArgParser::setProgramName(const std::string& programName)
{
    m_Impl->setProgramName(programName);
}

bool ArgParser::ignoreUnknownOptions() const
{
    return m_Impl->ignoreUnknownOptions();
}

void ArgParser::setIgnoreUnknownOptions(bool ignoreUnknownOptions)
{
    m_Impl->setIgnoreUnknownOptions(ignoreUnknownOptions);
}

void ArgParser::addHelpText(const std::string& helpText)
{
    m_Impl->addHelpText(helpText);
}

void ArgParser::addFlag(const std::string& name,
                        const std::string& opts,
                        bool enable,
                        const std::string& help)
{
    m_Impl->addFlag(name, opts, enable, help);
}

void ArgParser::addValue(const std::string& name,
                         const std::string& opts,
                         const std::string& value,
                         const std::string& help)
{
    m_Impl->addValue(name, opts, value, help);
}

void ArgParser::addOption(const std::string& name,
                          const std::string& opts,
                          const std::string& valueName,
                          const std::string& help)
{
    m_Impl->addOption(name, opts, valueName, help);
}

void ArgParser::addList(const std::string& name,
                        const std::string& opts,
                        const std::string& valueName,
                        const std::string& help)
{
    m_Impl->addList(name, opts, valueName, help);
}

void ArgParser::addListValue(const std::string& name,
                             const std::string& opts,
                             const std::string& value,
                             const std::string& help)
{
    m_Impl->addListValue(name, opts, value, help);
}

void ArgParser::addFlagCallback(const std::string& opts,
                                OptionCallback callback,
                                void* context,
                                const std::string& help)
{
    m_Impl->addFlagCallback(opts, callback, context, help);
}

void ArgParser::addOptionCallback(const std::string& opts,
                                  OptionCallback callback,
                                  void* context,
                                  const std::string& valueName,
                                  const std::string& help)
{
    m_Impl->addOptionCallback(opts, callback, context, valueName, help);
}

ParsedArgs ArgParser::parse(int argc, const char* const * argv)
{
    return m_Impl->parse(argc, argv);
}

bool ArgParser::parse(int argc, const char* const * argv, ParsedArgs& pa)
{
    return m_Impl->parse(argc, argv, pa);
}

bool ArgParser::processCurrentArg(ParsedArgs& pa)
{
    return m_Impl->processCurrentArg(pa);
}

void ArgParser::writeHelp() const
{
    m_Impl->writeHelp();
}

void ArgParser::writeHelp(std::ostream& os) const
{
    m_Impl->writeHelp(os);
}

void ArgParser::writeErrors(const ParsedArgs& pa) const
{
    m_Impl->writeErrors(pa);
}

void ArgParser::writeErrors(std::ostream& os, const ParsedArgs& pa) const
{
    m_Impl->writeErrors(os, pa);
}

void ArgParser::writeMessage(const std::string& msg) const
{
    m_Impl->writeMessage(msg);
}

void ArgParser::writeMessage(std::ostream& os, const std::string& msg) const
{
    m_Impl->writeMessage(os, msg);
}

}}
