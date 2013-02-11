#ifndef JEB_TEST_COMPARERS_HPP
#define JEB_TEST_COMPARERS_HPP

#include <cstring>

namespace JEB { namespace Test {

static double DoubleEpsilon = 0;
static float FloatEpsilon = 0;

template <typename T, typename U>
bool compare(T t, U u)
{
    return t == u;
}

template <>
bool compare<double, double>(double t, double u);

template <>
bool compare<float, float>(float t, float u);

template <>
inline bool compare<char*, char*>(char* t, char* u)
{
    return std::strcmp(t, u) == 0;
}

template <>
inline bool compare<const char*, const char*>(const char* t, const char* u)
{
    return std::strcmp(t, u) == 0;
}

bool compareReals(double a, double b, double epsilon);
bool compareReals(float a, float b, float epsilon);

}}

#endif
