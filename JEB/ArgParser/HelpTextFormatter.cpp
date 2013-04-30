#include "HelpTextFormatter.hpp"

#include <ostream>
#include "JEB/IO/IOManipulators.hpp"
#include "JEB/String/String.hpp"
#include "JEB/Sys/Console.hpp"
#include "JEB/Text/TextFormatter.hpp"

namespace JEB
{

HelpTextFormatter::HelpTextFormatter()
    : m_LeftMargin(2),
      m_MinHelpTextWidth(40),
      m_TextWidth(79)
{
}

HelpTextFormatter::~HelpTextFormatter()
{
}

size_t HelpTextFormatter::minHelpTextWidth() const
{
    return m_MinHelpTextWidth;
}

void HelpTextFormatter::setMinHelpTextWidth(size_t minHelpTextWidth)
{
    m_MinHelpTextWidth = minHelpTextWidth;
}

const std::string& HelpTextFormatter::programName() const
{
    return m_ProgramName;
}

void HelpTextFormatter::setProgramName(const std::string& programName)
{
    m_ProgramName = programName;
}

size_t HelpTextFormatter::textWidth() const
{
    return m_TextWidth;
}

void HelpTextFormatter::setTextWidth(size_t textWidth)
{
    m_TextWidth = textWidth;
}

const std::string& HelpTextFormatter::usage() const
{
    return m_Usage;
}

void HelpTextFormatter::setUsage(const std::string& usage)
{
    m_Usage = usage;
}

void HelpTextFormatter::addOption(OptionHelpText_sp option)
{
    m_Options.push_back(option);
}

void HelpTextFormatter::useConsoleTextWidth()
{
    unsigned height, width;
    if (Console::size(&height, &width))
    {
        m_TextWidth = width - 1;
        if (m_TextWidth < 20)
            m_LeftMargin = 0;
        m_MinHelpTextWidth = std::max(std::min<size_t>(10, m_TextWidth),
                                      m_TextWidth / 2);
    }
}

void HelpTextFormatter::write(std::ostream& stream) const
{
    writeUsage(stream);
    writeOptions(stream);
}

bool HelpTextFormatter::writeOption(const std::string& option, std::ostream& stream) const
{
    OptionHelpText_sp oht = findOption(option);
    if (!oht)
        return false;

    oht->write(stream, computeOptionColumns());
    return true;
}

void HelpTextFormatter::writeMessage(std::ostream& stream,
                                     const std::string& msg) const
{
    TextFormatter formatter(&stream, &msg);
    if (!m_ProgramName.empty())
    {
        stream << m_ProgramName << ": ";
        if (m_ProgramName.size() + 2 < m_TextWidth)
            formatter.setTextWidth(m_TextWidth - m_ProgramName.size() - 2);
        formatter.formatLine();
    }
    formatter.setTextWidth(m_TextWidth - m_LeftMargin);
    while (!formatter.endOfText())
    {
        stream << spaces(m_LeftMargin);
        formatter.formatLine();
    }
    stream << "\n";
}

void HelpTextFormatter::getFieldWidths(size_t& shortOpts, size_t& longOpts) const
{
    shortOpts = 0;
    longOpts = 0;
    for (std::vector<OptionHelpText_sp>::const_iterator it = m_Options.begin();
         it != m_Options.end();
         ++it)
    {
        shortOpts = std::max(shortOpts, (*it)->shortOptionWidth());
        longOpts = std::max(longOpts, (*it)->longOptionWidth());
    }
}

void HelpTextFormatter::writeUsage(std::ostream& stream) const
{
    if (m_Usage.empty())
        return;

    stream << "USAGE\n";
    std::string usage;
    if (m_ProgramName.empty())
        usage = m_Usage;
    else
        usage = String::replace(m_Usage, "%prog", m_ProgramName);
    TextFormatter formatter(&stream, &usage);
    formatter.setTextWidth(m_TextWidth - m_LeftMargin);
    do
    {
        stream << spaces(m_LeftMargin);
    } while (formatter.formatLine());
    stream << "\n";
}

void HelpTextFormatter::writeOptions(std::ostream& stream) const
{
    if (m_Options.empty())
        return;
    stream << "OPTIONS\n";
    HelpTextColumns cols = computeOptionColumns();
    for (std::vector<OptionHelpText_sp>::const_iterator it = m_Options.begin();
         it != m_Options.end();
         ++it)
    {
        (*it)->write(stream, cols);
    }
}

HelpTextColumns HelpTextFormatter::computeOptionColumns() const
{
    size_t shortOpts, longOpts;
    getFieldWidths(shortOpts, longOpts);
    HelpTextColumns cols;
    cols.shortOption = m_LeftMargin;
    cols.longOption = shortOpts ? cols.shortOption + shortOpts + 1 :
                                  cols.shortOption;
    size_t helpTextCol = longOpts ? cols.longOption + longOpts + 1 :
                                    cols.longOption;
    cols.helpText = std::min(m_TextWidth - m_MinHelpTextWidth, helpTextCol);
    cols.textWidth = m_TextWidth;
    return cols;
}

OptionHelpText_sp HelpTextFormatter::findOption(const std::string& option) const
{
    for (std::vector<OptionHelpText_sp>::const_iterator it = m_Options.begin();
         it != m_Options.end();
         ++it)
    {
        if ((*it)->hasOption(option))
            return *it;
    }

    return OptionHelpText_sp();
}

}
