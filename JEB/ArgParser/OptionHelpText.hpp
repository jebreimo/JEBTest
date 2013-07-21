#ifndef OPTIONHELPTEXT_HPP
#define OPTIONHELPTEXT_HPP

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace ArgParser {

struct HelpTextColumns
{
    size_t shortOption;
    size_t longOption;
    size_t helpText;
    size_t textWidth;
};

class OptionHelpText
{
public:
    void addLongOption(const std::string& option);
    void addShortOption(const std::string& option);
    bool hasOption(const std::string& option) const;

    const std::string& helptext() const;
    void setHelpText(const std::string& helpText);

    const std::string& valueName() const;
    void setValueName(const std::string& valueName);

    size_t shortOptionWidth() const;
    size_t longOptionWidth() const;

    void write(std::ostream& stream, const HelpTextColumns& columns) const;
private:
    std::string m_HelpText;
    std::vector<std::string> m_LongOptions;
    std::vector<std::string> m_ShortOptions;
    std::string m_ValueName;
};

typedef std::shared_ptr<OptionHelpText> OptionHelpText_sp;

}}

#endif // OPTIONHELPTEXT_HPP
