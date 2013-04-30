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

    const std::string& usage() const;
    void setUsage(const std::string& usage);

    void addOption(OptionHelpText_sp option);

    void useConsoleTextWidth();

    void write(std::ostream& stream) const;
    bool writeOption(const std::string& option, std::ostream& stream) const;
    void writeMessage(std::ostream& stream, const std::string& msg) const;
private:
    void getFieldWidths(size_t& shortOpts, size_t& longOpts) const;
    void writeUsage(std::ostream& stream) const;
    void writeOptions(std::ostream& stream) const;
    HelpTextColumns computeOptionColumns() const;
    OptionHelpText_sp findOption(const std::string& option) const;

    size_t m_LeftMargin;
    size_t m_MinHelpTextWidth;
    std::vector<OptionHelpText_sp> m_Options;
    std::string m_ProgramName;
    size_t m_TextWidth;
    std::string m_Usage;
};

}

#endif
