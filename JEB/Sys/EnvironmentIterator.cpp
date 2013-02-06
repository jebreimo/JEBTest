#include "EnvironmentIterator.hpp"

#include "JEB/String/String.hpp"

extern char** environ;

namespace JEB
{

EnvironmentIterator::EnvironmentIterator()
    : m_Env(environ)
{
}

bool EnvironmentIterator::hasNext() const
{
    return *m_Env != NULL;
}

std::pair<std::string, std::string> EnvironmentIterator::next()
{
    if (!*m_Env)
        return std::pair<std::string, std::string>();

    const std::string value = *m_Env++;
    return String::splitFirst(value, "=");
}

}
