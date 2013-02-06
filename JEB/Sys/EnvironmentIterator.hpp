#ifndef JEB_SYS_ENVIRONMENTITERATOR_HPP
#define JEB_SYS_ENVIRONMENTITERATOR_HPP

#include <iterator>
#include <string>
#include <utility>
#include "JEB/JEBDefinitions.hpp"

namespace JEB
{

class EnvironmentIterator
{
public:
    EnvironmentIterator();
    bool hasNext() const;
    std::pair<std::string, std::string> next();
private:
    char** m_Env;
};

}

#endif