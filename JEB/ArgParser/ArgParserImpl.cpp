#include "ArgParserImpl.hpp"

#include <cassert>
#include <stdexcept>
#include <iostream>
#include "JEB/Collections/MapUtilities.hpp"
#include "JEB/String/String.hpp"
#include "JEB/Sys/Path.hpp"
#include "ArgIterator.hpp"
#include "HelpTextFormatter.hpp"

namespace JEB { namespace ArgParser {

ArgParserImpl::ArgParserImpl(ArgParser* owner)
    : m_ArgIt(new ArgIterator()),
      m_HelpTextFormatter(new HelpTextFormatter()),
      m_IgnoreArguments(false),
      m_OptionsPrecedeArguments(true),
      m_Owner(owner),
      m_IgnoreUnknownOptions(false)
{
}

ArgParserImpl::~ArgParserImpl()
{
}

ArgIterator* ArgParserImpl::argIterator()
{
    return m_ArgIt.get();
}

const ArgIterator* ArgParserImpl::argIterator() const
{
    return m_ArgIt.get();
}

HelpTextFormatter* ArgParserImpl::helpTextFormatter()
{
    return m_HelpTextFormatter.get();
}

const HelpTextFormatter* ArgParserImpl::helpTextFormatter() const
{
    return m_HelpTextFormatter.get();
}

bool ArgParserImpl::ignoreArguments() const
{
    return m_IgnoreArguments;
}

void ArgParserImpl::setIgnoreArguments(bool ignoreAguments)
{
    m_IgnoreArguments = ignoreAguments;
}

bool ArgParserImpl::optionsPrecedeArguments() const
{
    return m_OptionsPrecedeArguments;
}

void ArgParserImpl::setOptionsPrecedeArguments(bool optionsPrecedeArguments)
{
    m_OptionsPrecedeArguments = optionsPrecedeArguments;
}

const std::string& ArgParserImpl::programName() const
{
    return m_HelpTextFormatter->programName();
}

void ArgParserImpl::setProgramName(const std::string& programName)
{
    m_HelpTextFormatter->setProgramName(programName);
}


bool ArgParserImpl::ignoreUnknownOptions() const
{
    return m_IgnoreUnknownOptions;
}

void ArgParserImpl::setIgnoreUnknownOptions(bool ignoreUnknownOptions)
{
    m_IgnoreUnknownOptions = ignoreUnknownOptions;
}

void ArgParserImpl::addHelpText(const std::string& helpText)
{
    m_HelpTextFormatter->addText(helpText);
}

void ArgParserImpl::addFlag(const std::string& name,
                            const std::string& opts,
                            bool enable,
                            const std::string& help)
{
    addValue(name, opts, enable ? "1" : "0", help);
}

void ArgParserImpl::addValue(const std::string& name,
                             const std::string& opts,
                             const std::string& value,
                             const std::string& help)
{
    m_ValueCallbackContexts.push_back(ValueCallbackContext(name, value));
    addFlagCallback(opts,
                    &handleValue,
                    static_cast<void*>(&m_ValueCallbackContexts.back()),
                    help);
}

void ArgParserImpl::addOption(const std::string& name,
                              const std::string& opts,
                              const std::string& valueName,
                              const std::string& help)
{
    m_OptionCallbackContexts.push_back(name);
    addOptionCallback(opts,
                      &handleOption,
                      static_cast<void*>(&m_OptionCallbackContexts.back()),
                      valueName,
                      help);
}

void ArgParserImpl::addList(const std::string& name,
                            const std::string& opts,
                            const std::string& valueName,
                            const std::string& help)
{
    m_OptionCallbackContexts.push_back(name);
    addOptionCallback(opts,
                      &handleList,
                      static_cast<void*>(&m_OptionCallbackContexts.back()),
                      valueName,
                      help);
}

void ArgParserImpl::addListValue(const std::string& name,
                                 const std::string& opts,
                                 const std::string& value,
                                 const std::string& help)
{
    m_ValueCallbackContexts.push_back(ValueCallbackContext(name, value));
    addFlagCallback(opts,
                    &handleListValue,
                    static_cast<void*>(&m_ValueCallbackContexts.back()),
                    help);
}

void ArgParserImpl::addFlagCallback(const std::string& opts,
                                    OptionCallback callback,
                                    void* context,
                                    const std::string& help)
{
    addCallback(opts, callback, context, "", help);
}

void ArgParserImpl::addOptionCallback(const std::string& opts,
                                      OptionCallback callback,
                                      void* context,
                                      const std::string& valueName,
                                      const std::string& help)
{
    if (valueName.empty())
        addCallback(opts, callback, context, "VALUE", help);
    else
        addCallback(opts, callback, context, valueName, help);
}

ParsedArgs ArgParserImpl::parse(int argc, const char* const * argv)
{
    ParsedArgs pa;
    parse(argc, argv, pa);
    return pa;
}

bool ArgParserImpl::parse(int argc, const char* const * argv, ParsedArgs& pa)
{
    assert(argc > 0);
    if (m_HelpTextFormatter->programName().empty())
        m_HelpTextFormatter->setProgramName(Sys::Path::baseName(argv[0]));
    m_ArgIt->setArguments(argc - 1, argv + 1);
    m_ArgIt->setIgnoresOptions(false);
    bool success = true;
    while (m_ArgIt->nextArgument())
        success &= processCurrentArg(pa);
    return success;
}

bool ArgParserImpl::processCurrentArg(ParsedArgs& pa)
{
    switch (m_ArgIt->type())
    {
    case ArgIterator::Argument:
        if (!m_IgnoreArguments)
        {
            pa.addArgument(m_ArgIt->value());
            if (m_OptionsPrecedeArguments && !m_ArgIt->ignoresOptions())
                m_ArgIt->setIgnoresOptions(true);
        }
        else
        {
            pa.addUnprocessedArg(m_ArgIt->argument());
        }
        return true;
    case ArgIterator::Flag:
    case ArgIterator::Option:
        {
            OptionCallbackWithContext ocwc;
            if (Collections::tryGet(m_OptionCallbacks, m_ArgIt->name(), ocwc))
            {
                OptionData od(&pa, m_ArgIt->name(), m_ArgIt->value(), ocwc.second);
                ocwc.first(m_Owner, &od);
            }
        }
        return true;
    case ArgIterator::InvalidFlag:
        pa.addInvalidOption(m_ArgIt->name(), "invalid flag");
        return false;
    case ArgIterator::InvalidOption:
        pa.addInvalidOption(m_ArgIt->name(), "invalid option");
        return false;
    case ArgIterator::UnknownOption:
        if (!m_IgnoreUnknownOptions)
            pa.addInvalidOption(m_ArgIt->name(), "unknown option");
        else
            pa.addUnprocessedArg(m_ArgIt->argument());
        return false;
    default:
        return false;
    }
}

void ArgParserImpl::writeHelp() const
{
    m_HelpTextFormatter->useConsoleTextWidth();
    writeHelp(std::cout);
}

void ArgParserImpl::writeHelp(std::ostream& os) const
{
    m_HelpTextFormatter->write(os);
}

void ArgParserImpl::writeErrors(const ParsedArgs& apr) const
{
    writeErrors(std::cerr, apr);
}

void ArgParserImpl::writeErrors(std::ostream& os, const ParsedArgs& pa) const
{
    for (size_t i = 0; i < pa.invalidOptionCount(); ++i)
    {
        std::string option, reason;
        pa.invalidOption(i, option, reason);
        m_HelpTextFormatter->writeMessage(os, option + ": " + reason);
    }
}

void ArgParserImpl::writeMessage(const std::string& msg) const
{
    writeMessage(std::cerr, msg);
}

void ArgParserImpl::writeMessage(std::ostream& os, const std::string& msg) const
{
    m_HelpTextFormatter->writeMessage(os, msg);
}

static bool isShortOption(const std::string& option)
{
    return option.size() == 2 && option[0] == '-';
}

static bool isLongOption(const std::string& option)
{
    return option.size() > 2 && option[0] == '-' && option[1] == '-';
}

void ArgParserImpl::addCallback(const std::string& opts,
                                OptionCallback callback,
                                void* context,
                                const std::string& valueName,
                                const std::string& help)
{
    assert(callback);
    OptionCallbackWithContext ocbwc(callback, context);
    std::vector<std::string> parts = String::split(opts);
    OptionHelpText_sp oht(new OptionHelpText);
    for (std::vector<std::string>::const_iterator it = parts.begin();
         it != parts.end();
         ++it)
    {
        if (!m_OptionCallbacks.insert(std::make_pair(*it, ocbwc)).second)
            throw std::invalid_argument(*it + ": defined twice");
        if (isShortOption(*it))
            oht->addShortOption(*it);
        else if (isLongOption(*it))
            oht->addLongOption(*it);
        else
            throw std::invalid_argument(*it + ": not a proper option");
        if (valueName.empty())
            m_ArgIt->addFlag(*it);
        else
            m_ArgIt->addOption(*it);
    }
    oht->setHelpText(help);
    oht->setValueName(valueName);
    m_HelpTextFormatter->addOption(oht);
}

void ArgParserImpl::handleList(ArgParser* /*argParser*/,
                               const OptionData* od)
{
    std::string* name = static_cast<std::string*>(od->context);
    od->parsedArgs->addListValue(*name, od->value);
}

void ArgParserImpl::handleOption(ArgParser* /*argParser*/,
                                 const OptionData* od)
{
    std::string* name = static_cast<std::string*>(od->context);
    od->parsedArgs->setOption(*name, od->value);
}

void ArgParserImpl::handleValue(ArgParser* /*argParser*/,
                                const OptionData* od)
{
    ValueCallbackContext* nameValue = static_cast<ValueCallbackContext*>(od->context);
    od->parsedArgs->setOption(nameValue->first, nameValue->second);
}

void ArgParserImpl::handleListValue(ArgParser* /*argParser*/,
                                    const OptionData* od)
{
    ValueCallbackContext* nameValue = static_cast<ValueCallbackContext*>(od->context);
    od->parsedArgs->addListValue(nameValue->first, nameValue->second);
}

}}
