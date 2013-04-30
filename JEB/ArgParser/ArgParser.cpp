#include "ArgParser.hpp"

#include "ArgParserImpl.hpp"

namespace JEB
{

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

const std::string& ArgParser::usage() const
{
    return m_Impl->usage();
}

void ArgParser::setUsage(const std::string& usage)
{
    m_Impl->setUsage(usage);
}

void ArgParser::addFlag(const std::string& opts,
                        bool enable,
                        const std::string& name,
                        const std::string& help)
{
    m_Impl->addFlag(opts, enable, name, help);
}

void ArgParser::addValue(const std::string& opts,
                         const std::string& value,
                         const std::string& name,
                         const std::string& help)
{
    m_Impl->addValue(opts, value, name, help);
}

void ArgParser::addOption(const std::string& opts,
                          const std::string& name,
                          const std::string& valueName,
                          const std::string& help)
{
    m_Impl->addOption(opts, name, valueName, help);
}

void ArgParser::addList(const std::string& opts,
                        const std::string& name,
                        const std::string& valueName,
                        const std::string& help)
{
    m_Impl->addList(opts, name, valueName, help);
}

void ArgParser::addListValue(const std::string& opts,
                             const std::string& value,
                             const std::string& name,
                             const std::string& help)
{
    m_Impl->addListValue(opts, value, name, help);
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

}
