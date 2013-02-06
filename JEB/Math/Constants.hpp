#ifndef JEB_MATH_CONSTANTS_HPP
#define JEB_MATH_CONSTANTS_HPP

#include <limits>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Math {

static const size_t InvalidIndex = std::numeric_limits<size_t>::max();
static const double InvalidDouble = -std::numeric_limits<double>::max();
static const double DoubleTolerance = 1e-9;

static const double Pi = 3.1415926535897932384626433832795;

static inline bool isValid(double v) {return v != InvalidDouble;}
static inline bool isValid(size_t v) {return v != InvalidIndex;}

}}

#endif
