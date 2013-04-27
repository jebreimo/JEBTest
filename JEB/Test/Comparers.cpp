#include "Comparers.hpp"

#include <cmath>

using namespace std;

namespace JEB { namespace Test {

template <>
bool compare<double, double>(double t, double u)
{
    return compareReals(t, u, DoubleEpsilon);
}

template <>
bool compare<float, float>(float t, float u)
{
    return compareReals(t, u, FloatEpsilon);
}

bool compareReals(double a, double b, double epsilon)
{
    return std::fabs(a - b) <= epsilon;
}

bool compareReals(float a, float b, float epsilon)
{
    return std::fabs(a - b) <= epsilon;
}

}}
