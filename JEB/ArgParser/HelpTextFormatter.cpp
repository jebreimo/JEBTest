#include "HelpTextFormatter.hpp"

#include <ostream>
#include "JEB/IO/IOManipulators.hpp"
#include "JEB/String/String.hpp"
#include "JEB/Sys/Console.hpp"
#include "JEB/Text/TextFormatter.hpp"

namespace JEB { namespace ArgParser {

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

void HelpTextFormatter::addText(const std::string& text)
{
    m_Text.push_back(TextElement(text));
}

void HelpTextFormatter::addOption(OptionHelpText_sp option)
{
    m_Text.push_back(TextElement(option));
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
    HelpTextColumns cols = computeOptionColumns();
    for (auto it = m_Text.begin(); it != m_Text.end(); ++it)
    {
        if (it->option())
            it->option()->write(stream, cols);
        else if (m_ProgramName.empty())
            writeText(stream, it->text());
        else
            writeText(stream,
                      String::replace(it->text(), "%prog", m_ProgramName));
    }
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
    for (auto it = m_Text.begin(); it != m_Text.end(); ++it)
    {
        if (it->option())
        {
            shortOpts = std::max(shortOpts, it->option()->shortOptionWidth());
            longOpts = std::max(longOpts, it->option()->longOptionWidth());
        }
    }
}

void HelpTextFormatter::writeText(std::ostream& stream, const std::string& text) const
{
    std::string usage;
    TextFormatter formatter(&stream, &text);
    formatter.setTextWidth(m_TextWidth - m_LeftMargin);
    do
    {
        stream << spaces(m_LeftMargin);
    } while (formatter.formatLine());
    stream << "\n";
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
    for (auto it = m_Text.begin(); it != m_Text.end(); ++it)
    {
        if (it->option() && it->option()->hasOption(option))
            return it->option();
    }

    return OptionHelpText_sp();
}

HelpTextFormatter::TextElement::TextElement()
{}

HelpTextFormatter::TextElement::TextElement(const std::string& text)
    : m_Text(text)
{}

HelpTextFormatter::TextElement::TextElement(OptionHelpText_sp& option)
    : m_Option(option)
{}

const std::string& HelpTextFormatter::TextElement::text() const
{
    return m_Text;
}

const OptionHelpText_sp& HelpTextFormatter::TextElement::option() const
{
    return m_Option;
}

}}
