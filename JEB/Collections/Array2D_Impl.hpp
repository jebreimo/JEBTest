#include <algorithm>
#include <cassert>
#include "Algorithms.hpp"

namespace JEB {

template <typename T>
Array2D<T>::Array2D()
    : m_Pointers(NULL),
      m_Buffer(NULL)
{
    m_Size[0] = m_Size[1] = 0;
}

template <typename T>
Array2D<T>::Array2D(size_t dim0, size_t dim1)
    : m_Pointers(NULL),
      m_Buffer(NULL)
{
    init(dim0, dim1);
}

template <typename T>
Array2D<T>::Array2D(const Array2D<T>& other)
    : m_Pointers(NULL),
      m_Buffer(NULL)
{
    init(other.size(0), other.size(1));
    T* dst = begin();
    for (const T* src = other.begin(); src != other.end(); src++)
        *dst++ = *src;
}

template <typename T>
Array2D<T>::~Array2D()
{
    delete[] m_Pointers;
    delete[] m_Buffer;
}

template <typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D& rhs)
{
    Array2D<T> other(rhs);
    other.swap(*this);
    return *this;
}

template <typename T>
T* Array2D<T>::operator[](size_t dim0)
{
    assert(dim0 < m_Size[0]);
    return m_Pointers[dim0];
}

template <typename T>
const T* Array2D<T>::operator[](size_t dim0) const
{
    assert(dim0 < m_Size[0]);
    return m_Pointers[dim0];
}

template <typename T>
size_t Array2D<T>::size(size_t dim) const
{
    assert(dim < sizeof(m_Size) / sizeof(*m_Size));
    return m_Size[dim];
}

template <typename T>
void Array2D<T>::setSize(size_t dim0, size_t dim1)
{
    if (dim0 * dim1 == m_Size[0] * m_Size[1])
    {
        delete m_Pointers;
        initPointers(dim0, dim1);
    }
    else
    {
        Array2D<T> other(dim0, dim1);
        other.swap(*this);
    }
}

template <typename T>
T* Array2D<T>::begin()
{
    return &m_Buffer[0];
}

template <typename T>
const T* Array2D<T>::begin() const
{
    return &m_Buffer[0];
}

template <typename T>
const T* Array2D<T>::cbegin() const
{
    return &m_Buffer[0];
}

template <typename T>
T* Array2D<T>::end()
{
    return &m_Buffer[m_Size[0] * m_Size[1]];
}

template <typename T>
const T* Array2D<T>::end() const
{
    return &m_Buffer[m_Size[0] * m_Size[1]];
}

template <typename T>
const T* Array2D<T>::cend() const
{
    return &m_Buffer[m_Size[0] * m_Size[1]];
}

template <typename T>
void Array2D<T>::swap(Array2D<T>& other)
{
    Algorithms::swapArrays(m_Size, other.m_Size);
    std::swap(m_Pointers, other.m_Pointers);
    std::swap(m_Buffer, other.m_Buffer);
}

template <typename T>
void Array2D<T>::init(size_t dim0, size_t dim1)
{
    m_Buffer = new T[dim0 * dim1];
    initPointers(dim0, dim1);
    std::fill(begin(), end(), T());
}

template <typename T>
void Array2D<T>::initPointers(size_t dim0, size_t dim1)
{
    m_Pointers = new T*[dim0];
    for (size_t i = 0; i < dim0; ++i)
        m_Pointers[i] = &m_Buffer[i * dim1];
    m_Size[0] = dim0;
    m_Size[1] = dim1;
}

template <typename T>
bool operator==(const Array2D<T>& a, const Array2D<T>& b)
{
    return a.size(0) == b.size(0) && a.size(1) == b.size(1) &&
           std::equal(a.begin(), a.end(), b.begin());
}

template <typename T>
bool operator!=(const Array2D<T>& a, const Array2D<T>& b)
{
    return !(a == b);
}

template <typename T>
void print(std::ostream& os, const Array2D<T>& a)
{
    assert(a.size(0) != 0 || a.size(1) != 0);

    for (size_t i = 0; i < a.size(0); ++i)
    {
        os << a[i][0];
        for (size_t j = 1; j < a.size(1); ++j)
            os << " " << a[i][j];
        os << "\n";
    }
}

template <typename T>
void minMax(const Array2D<T>& a, T& min, T& max)
{
    Algorithms::minMax(a.begin(), a.end(), min, max);
}

}
