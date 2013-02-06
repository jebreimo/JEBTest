#include "JEB/BitSet.hpp"
#include "JEB/Debug.hpp"

namespace JEB { namespace Math {

namespace MatrixAlgorithms
{

template <typename T>
void transposeInPlace(T* values, size_t rows, size_t cols)
{
    BitSet visited(rows * cols);
    size_t unvisited = 0;
    while (unvisited != BitSet::NotFound)
    {
        size_t index = unvisited;
        T value = values[index];
        while (!visited.bit(index))
        {
            visited.setBit(index, true);
            index = (index / cols) + (index % cols) * rows;
            std::swap(value, values[index]);
        }
        unvisited = visited.findFirst(false, unvisited + 1);
    }
}

}

}}
