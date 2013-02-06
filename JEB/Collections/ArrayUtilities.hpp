#ifndef JEB_ARRAYUTILITIES_HPP
#define JEB_ARRAYUTILITIES_HPP

#include <iterator>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace ArrayUtilities {

template <typename T>
class ReverseIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
    ReverseIterator();
    explicit ReverseIterator(T* ptr);

    ReverseIterator& operator++();
    ReverseIterator operator++(int);

    ReverseIterator& operator--();
    ReverseIterator operator--(int);

    T& operator*() const;
    T* operator->() const;

    bool operator==(const ReverseIterator& rhs) const;
    bool operator!=(const ReverseIterator& rhs) const;
private:
    T* m_Ptr;
};

template <typename T>
class ConstReverseIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
    ConstReverseIterator();
    explicit ConstReverseIterator(const T* ptr);

    ConstReverseIterator& operator++();
    ConstReverseIterator operator++(int);

    ConstReverseIterator& operator--();
    ConstReverseIterator operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator==(const ConstReverseIterator& rhs) const;
    bool operator!=(const ConstReverseIterator& rhs) const;
private:
    const T* m_Ptr;
};

template <typename T, size_t N>
ReverseIterator<T> rbegin(T (&array)[N])
{
    return ReverseIterator<T>(&array[N]);
}

template <typename T, size_t N>
ReverseIterator<T> rend(T (&array)[N])
{
    return ReverseIterator<T>(&array[0]);
}

template <typename T, size_t N>
ConstReverseIterator<T> crbegin(T (&array)[N])
{
    return ConstReverseIterator<T>(&array[N]);
}

template <typename T, size_t N>
ConstReverseIterator<T> crend(T (&array)[N])
{
    return ConstReverseIterator<T>(&array[0]);
}

template <typename T>
ReverseIterator<T> riterator(T* ptr)
{
    return ReverseIterator<T>(ptr);
}

template <typename T>
ConstReverseIterator<T> criterator(T* ptr)
{
    return ConstReverseIterator<T>(ptr);
}

}}

#endif
