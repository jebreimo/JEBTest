#ifndef JEB_UTILITIES_HPP
#define JEB_UTILITIES_HPP

#include <utility>
#include "JEB/JEBDefinitions.hpp"

template <typename T, typename U>
const T& first(const std::pair<T, U>& pair)
{
    return pair.first;
}

template <typename T, typename U>
const T& second(const std::pair<T, U>& pair)
{
    return pair.second;
}

#endif
