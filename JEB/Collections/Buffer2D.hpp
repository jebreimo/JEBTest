#ifndef JEB_BUFFER2D_HPP
#define JEB_BUFFER2D_HPP

#include <cstddef>
#include "JEB/JEBDefinitions.hpp"

namespace JEB
{

template <typename T>
class Buffer2D
{
public:
    Buffer2D(T* buffer,
             size_t dim0,
             size_t dim1,
             size_t trailingDataSize = 0);
    Buffer2D(const Buffer<T>& other);
    ~Buffer2D();

    Buffer2D& operator=(const Buffer2D& rhs);

    size_t size(size_t dim) const;

    size_t trailingDataSize() const;

    T* operator[](size_t dim0);
    const T* operator[](size_t dim0) const;

    T* begin();
    const T* begin() const;

    T* end();
    const T* end() const;
private:
    void  init(size_t dim0, size_t dim1);

    size_t m_Size[2];
    size_t m_TrailingDataSize;
    T** m_Pointers;
    T* m_Buffer;
};

}

#include "Buffer2D_Impl.hpp"

#endif
