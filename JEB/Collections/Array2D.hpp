#ifndef JEB_ARRAY2D_HPP
#define JEB_ARRAY2D_HPP

#include <ostream>
#include "JEB/JEBDefinitions.hpp"

namespace JEB
{

template <typename T>
class Array2D
{
public:
    Array2D();
    Array2D(size_t dim0, size_t dim1);
    Array2D(const Array2D<T>& other);
    ~Array2D();

    Array2D& operator=(const Array2D& rhs);

    T* operator[](size_t dim0);
    const T* operator[](size_t dim0) const;

    size_t size(size_t dim) const;
    void setSize(size_t dim0, size_t dim1);

    T* begin();
    const T* begin() const;
    const T* cbegin() const;

    T* end();
    const T* end() const;
    const T* cend() const;

    void swap(Array2D& other);
private:
    void init(size_t dim0, size_t dim1);
    void initPointers(size_t dim0, size_t dim1);

    size_t m_Size[2];
    T** m_Pointers;
    T* m_Buffer;
};

template <typename T>
bool operator==(const Array2D<T>& a, const Array2D<T>& b);
template <typename T>
bool operator!=(const Array2D<T>& a, const Array2D<T>& b);

template <typename T>
void print(std::ostream& os, const Array2D<T>& a);

template <typename T>
void minMax(const Array2D<T>& a, T& min, T& max);

}

#include "Array2D_Impl.hpp"

#endif // JEB_ARRAY2D_HPP
