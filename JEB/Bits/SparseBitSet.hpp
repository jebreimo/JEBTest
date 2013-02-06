#ifndef JEB_SPARSEBITSET_HPP
#define JEB_SPARSEBITSET_HPP

#include <vector>
#include "JEB/JEBDefinitions.hpp"

namespace JEB {

class SparseBitSet
{
public:
    SparseBitSet(size_t size, size_t bucketSize = 32768);
    ~SparseBitSet();

    size_t size() const;
    void setSize(size_t size);

    size_t bucketSize() const;
    void setBucketSize(size_t bucketSize);

    bool bit(size_t index) const;
    void setBit(size_t index, bool value);

    size_t bucketCount() const;
    size_t usedBucketCount() const;
private:
    void clear();
    unsigned* createBucket(size_t index);

    size_t m_Size;
    size_t m_BucketSize;
    std::vector<unsigned*> m_Buckets;
};

}

#endif
