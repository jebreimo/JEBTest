#ifndef JEB_OPTIONDATA_HPP
#define JEB_OPTIONDATA_HPP

#include <string>
#include "ParsedArgs.hpp"

namespace JEB
{

struct OptionData
{
    OptionData(ParsedArgs* parsedArgs,
               const std::string& option,
               const std::string& value,
               void* context)
        : parsedArgs(parsedArgs),
          option(option),
          value(value),
          context(context)
    {
    }

    ParsedArgs* parsedArgs;
    const std::string& option;
    const std::string& value;
    void* context;
};

}

#endif
