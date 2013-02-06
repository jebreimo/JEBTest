#ifndef JEB_PAIR_INSERTER_HPP
#define JEB_PAIR_INSERTER_HPP

#include <iterator>
#include <stdexcept>
#include <utility>
#include "JEB/JEBDefinitions.hpp"

namespace JEB {

template <typename T>
class PairBackInsertIterator : std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    PairBackInsertIterator(std::pair<T, T>& pair)
        : m_It(&pair.first),
          m_End(m_It + 2)
    {
    }

    PairBackInsertIterator& operator*() {return *this;}
    PairBackInsertIterator& operator++() {return *this;}
    PairBackInsertIterator& operator++(int) {return *this;}

    const T& operator=(const T& value)
    {
        if (m_It != m_End)
            *m_It++ = value;
        return value;
    }

private:
    T* m_It;
    T* m_End;
};

template <typename T>
PairBackInsertIterator<T> backInserter(std::pair<T, T>& pair)
{
    return PairBackInsertIterator<T>(pair);
}

template <typename T>
class PairFrontInsertIterator : std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    PairFrontInsertIterator(std::pair<T, T>& pair)
        : m_It(&pair.second + 1),
          m_Begin(&pair.first)
    {
    }

    PairFrontInsertIterator& operator*() {return *this;}
    PairFrontInsertIterator& operator++() {return *this;}
    PairFrontInsertIterator& operator++(int) {return *this;}

    const T& operator=(const T& value)
    {
        if (m_It != m_Begin)
            *--m_It = value;
        return value;
    }

private:
    T* m_It;
    T* m_Begin;
};

template <typename T>
PairFrontInsertIterator<T> frontInserter(std::pair<T, T>& pair)
{
    return PairFrontInsertIterator<T>(pair);
}

}

#endif
