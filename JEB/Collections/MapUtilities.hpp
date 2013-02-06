#ifndef JEB_MAPUTILITIES_HPP
#define JEB_MAPUTILITIES_HPP

#include <map>
#include "FromString.hpp"
#include "ToString.hpp"

namespace JEB
{
namespace AnyMap
{

template <typename T, typename U, typename Cmp>
bool tryGet(const std::map<T, U, Cmp>& map, const T& key, U& value)
{
    typename std::map<T, U, Cmp>::const_iterator it = map.find(key);
    if (it == map.end())
        return false;

    value = it->second;
    return true;
}

template <typename T, typename U, typename Cmp>
U get(const std::map<T, U, Cmp>& map, const T& key, const U& defaultValue)
{
    U value;
    if (tryGet(map, key, value))
        return value;
    else
        return defaultValue;
}

template <typename It, typename T>
It findSecond(It begin, It end, const T& value)
{
    while (begin != end && (*begin).second != value)
        begin++;
    return begin;
}

template <typename T, typename U, typename Cmp>
T keyForValue(const std::map<T, U, Cmp>& map, const U& value, const T& defaultKey)
{
    typename std::map<T, U, Cmp>::const_iterator it =
            findSecond(map.begin(), map.end(), value);
    if (it != map.end())
        return it->first;
    else
        return defaultKey;
}

}

namespace StringMap
{

typedef std::map<std::string, std::string> Map_t;

template <typename T>
bool tryGet(const Map_t& map, const std::string& key, T& value)
{
    Map_t::const_iterator it = map.find(key);
    if (it == map.end())
        return false;

    return ::JEB::fromString(it->second, value);
}

template <>
inline bool tryGet<>(const Map_t& map, const std::string& key, std::string& value)
{
    Map_t::const_iterator it = map.find(key);
    if (it == map.end())
        return false;

    value = it->second;
    return true;
}

template <typename T>
T get(const Map_t& map, const std::string& key, const T& defaultValue)
{
    T value;
    if (tryGet(map, key, value))
        return value;
    else
        return defaultValue;
}

template <typename T>
void set(Map_t& map, const std::string& key, const T& value)
{
    map[key] = ::JEB::toString(value);
}

}
}

#endif
