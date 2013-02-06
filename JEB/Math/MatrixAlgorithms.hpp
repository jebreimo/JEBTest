#ifndef JEB_MATH_MATRIXALGORITHM_HPP
#define JEB_MATH_MATRIXALGORITHM_HPP

#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace Math {

namespace MatrixAlgorithms
{

template <typename T>
void transposeInPlace(T* values, size_t rows, size_t cols);

}

}}

#include "MatrixAlgorithms_impl.hpp"

#endif
