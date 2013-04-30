#include "OptionHelpText.hpp"

#include "JEB/Algorithms/Algorithms.hpp"
#include "JEB/IO/IOManipulators.hpp"
#include "JEB/Collections/VectorUtilities.hpp"
#include "JEB/Text/TextFormatter.hpp"

namespace JEB
{

namespace internal
{
    class OptionWriter
    {
    public:
        OptionWriter(std::ostream* stream, const std::string* helpText, const HelpTextColumns& columns);
        void writeShortOption(const std::string& option, const std::string& valueName);
        void writeLongOption(const std::string& option, const std::string& valueName);
        bool writeHelpText();
    private:
        void fill(size_t column);

        TextFormatter m_Formatter;
        size_t m_Column;
        std::ostream* m_Stream;
        HelpTextColumns m_Columns;
    };

    OptionWriter::OptionWriter(std::ostream* stream, const std::string* helpText, const HelpTextColumns& columns)
        : m_Formatter(stream, helpText),
          m_Column(0),
          m_Stream(stream),
          m_Columns(columns)
    {
    }

    void OptionWriter::writeShortOption(const std::string& option, const std::string& valueName)
    {
        fill(m_Columns.shortOption);

        *m_Stream << option;
        m_Column += option.size();

        if (!valueName.empty())
        {
            *m_Stream << ' ' << valueName;
            m_Column += 1 + valueName.size();
        }
    }

    void OptionWriter::writeLongOption(const std::string& option, const std::string& valueName)
    {
        fill(m_Columns.longOption);

        *m_Stream << option;
        m_Column += option.size();

        if (!valueName.empty())
        {
            *m_Stream << '=' << valueName;
            m_Column += 1 + valueName.size();
        }
    }

    bool OptionWriter::writeHelpText()
    {
        if (m_Column > m_Columns.textWidth)
        {
            m_Column %= (m_Columns.textWidth + 1);
            if (m_Column == 0)
                return m_Formatter.endOfText();
        }

        if (m_Column + 2 >= m_Columns.textWidth)
        {
            *m_Stream << '\n';
            m_Column = 0;
            return m_Formatter.endOfText();
        }

        fill(m_Columns.helpText);

        if (m_Column > m_Columns.helpText)
            m_Formatter.setTextWidth(m_Columns.textWidth - m_Column);
        else
            m_Formatter.setTextWidth(m_Columns.textWidth - m_Columns.helpText);

        if (!m_Formatter.formatLine())
            *m_Stream << '\n';

        m_Column = 0;
        return m_Formatter.endOfText();
    }

    void OptionWriter::fill(size_t column)
    {
        if (column > m_Column)
        {
            *m_Stream << spaces(column - m_Column);
            m_Column = column;
        }
    }
}

void OptionHelpText::addLongOption(const std::string& option)
{
    m_LongOptions.push_back(option);
}

void OptionHelpText::addShortOption(const std::string& option)
{
    m_ShortOptions.push_back(option);
}

bool OptionHelpText::hasOption(const std::string& option) const
{
    return has(m_ShortOptions, option) || has(m_LongOptions, option);
}

const std::string& OptionHelpText::helptext() const
{
    return m_HelpText;
}

void OptionHelpText::setHelpText(const std::string& helpText)
{
    m_HelpText = helpText;
}

const std::string& OptionHelpText::valueName() const
{
    return m_ValueName;
}

void OptionHelpText::setValueName(const std::string& valueName)
{
    m_ValueName = valueName;
}

size_t OptionHelpText::shortOptionWidth() const
{
    if (m_ShortOptions.empty())
        return 0;
    else if (m_ValueName.empty())
        return 2;
    else
        return 3 + m_ValueName.size();
}

size_t OptionHelpText::longOptionWidth() const
{
    if (m_LongOptions.empty())
        return 0;
    else if (m_ValueName.empty())
        return Algorithms::maxSize(m_LongOptions.begin(), m_LongOptions.end());
    else
        return Algorithms::maxSize(m_LongOptions.begin(), m_LongOptions.end()) + 1 + m_ValueName.size();
}

void OptionHelpText::write(std::ostream& stream, const HelpTextColumns& columns) const
{
    std::vector<std::string>::const_iterator sit = m_ShortOptions.begin();
    std::vector<std::string>::const_iterator lit = m_LongOptions.begin();
    internal::OptionWriter writer(&stream, &m_HelpText, columns);
    bool moreHelpText = true;
    while (sit != m_ShortOptions.end() || lit != m_LongOptions.end())
    {
        if (sit != m_ShortOptions.end())
            writer.writeShortOption(*sit++, m_ValueName);
        if (lit != m_LongOptions.end())
            writer.writeLongOption(*lit++, m_ValueName);
        moreHelpText = !writer.writeHelpText();
    }
    while (moreHelpText)
        moreHelpText = !writer.writeHelpText();
}

}
