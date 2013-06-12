#ifndef JEB_HELPTEXTFORMATTER_HPP
#define JEB_HELPTEXTFORMATTER_HPP

#include <iosfwd>
#include <vector>
#include <string>
#include "OptionHelpText.hpp"

/** @file
  * @brief Defines the class HelpTextFormatter.
  */

namespace JEB
{

/** @brief Writes nicely formatted help texts.
  */
class HelpTextFormatter
{
public:
    HelpTextFormatter();
    ~HelpTextFormatter();

    size_t minHelpTextWidth() const;
    void setMinHelpTextWidth(size_t minHelpTextWidth);

    const std::string& programName() const;
    void setProgramName(const std::string& programName);

    size_t textWidth() const;
    void setTextWidth(size_t textWidth);

    void addText(const std::string& text);
    void addOption(OptionHelpText_sp option);

    void useConsoleTextWidth();

    void write(std::ostream& stream) const;
    void writeMessage(std::ostream& stream, const std::string& msg) const;
private:
    void getFieldWidths(size_t& shortOpts, size_t& longOpts) const;
    void writeText(std::ostream& stream, const std::string& text) const;
    HelpTextColumns computeOptionColumns() const;
    OptionHelpText_sp findOption(const std::string& option) const;

    class TextElement
    {
    public:
        TextElement();
        TextElement(const std::string& text);
        TextElement(OptionHelpText_sp& option);

        const std::string& text() const;
        const OptionHelpText_sp& option() const;
    private:
        std::string m_Text;
        OptionHelpText_sp m_Option;
    };

    size_t m_LeftMargin;
    size_t m_MinHelpTextWidth;
    std::vector<TextElement> m_Text;
    std::string m_ProgramName;
    size_t m_TextWidth;
};

}

#endif
