#ifndef JEB_VECTORUTILITIES_HPP
#define JEB_VECTORUTILITIES_HPP

#include <algorithm>
#include <vector>
#include "JEB/JEBDefinitions.hpp"

namespace JEB
{

template <typename T>
bool has(const std::vector<T>& vec, const T& value)
{
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

}

#endif
