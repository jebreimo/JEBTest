#ifndef JEB_PODARRAY2D_HPP
#define JEB_PODARRAY2D_HPP

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include "JEB/JEBDefinitions.hpp"

namespace JEB
{

template <typename T>
class PodArray2D
{
public:
    PodArray2D(size_t dim0, size_t dim1, size_t alignment = 1);
    ~PodArray2D();
    size_t size(size_t dim) const;
    size_t alignment() const;
    T** buffer();

    T* operator[](size_t dim0);
    const T* operator[](size_t dim0) const;

    void setAllValues(const T& value);
private:
    PodArray2D(const PodArray2D&);
    PodArray2D& operator=(const PodArray2D&);

    template <typename T>
    T** newArray(size_t dim0, size_t dim1, size_t alignment = 1);

    size_t m_Size[2];
    size_t m_Alignment;
    T** m_Buffer;
};

template <typename T>
PodArray2D<T>::PodArray2D(size_t dim0, size_t dim1, size_t alignment)
    : m_Buffer(newArray(dim0, dim1, alignment)),
      m_Alignment(alignment)
{
    m_Size[0] = dim0;
    m_Size[1] = dim1;
}

template <typename T>
PodArray2D<T>::~PodArray2D()
{
    std::free(m_Buffer);
}

template <typename T>
size_t PodArray2D<T>::size(size_t dim) const
{
    return m_Size[dim];
}

template <typename T>
size_t PodArray2D<T>::alignment() const
{
    return m_Alignment;
}

template <typename T>
T** PodArray2D<T>::buffer()
{
    return m_Buffer;
}

template <typename T>
void PodArray2D<T>::setAllValues(const T& value)
{
    if (m_Alignment == 1)
    {
        std::fill(m_Buffer[0], m_Buffer[m_Size[0]], value);
    }
    else
    {
        for (size_t i = 0; i != m_Size[0]; ++i)
            std::fill_n(m_Buffer[i], m_Size[1], value);
    }
}

template <typename T>
T* PodArray2D<T>::operator[](size_t dim0)
{
    return m_Buffer[dim0];
}

template <typename T>
const T* PodArray2D<T>::operator[](size_t dim0) const
{
    return m_Buffer[dim0];
}

namespace
{
    inline size_t alignValue(size_t value, size_t alignment)
    {
        size_t mod = value % alignment;
        if (mod != 0)
            value += alignment - mod;
        return value;
    }
}

template <typename T>
T** PodArray2D<T>::newArray(size_t dim0, size_t dim1, size_t alignment)
{
    assert(m != 0 && n != 0 && valueSize != 0);
    assert(alignment != 0 && (alignment & (alignment - 1)) == 0);
    const size_t DefaultAlignment = 16;
    size_t dim0Size = (m + 1) * sizeof(T*);
    size_t dim1Size = alignValue(n * sizeof(T), alignment);
    size_t padding = alignment > sizeof(T*) ? alignment - sizeof(T*) : 0;
    size_t size = dim0Size + dim1 * dim1Size + padding;

    char* buffer = static_cast<char*>(std::calloc(size));

    T** arr = reinterpret_cast<T**>(buffer);
    buffer = reinterpret_cast<char*>(alignValue((size_t)buffer + dim0Size,
                                                alignment));

    for (size_t i = 0; i <= dim1; ++i, buffer += dim2Size)
        arr[i] = reinterpret_cast<T*>(buffer);

    return arr;
}

}

#endif
