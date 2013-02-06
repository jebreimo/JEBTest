#include "../Primes.hpp"
#include <JEB/Unit/JEBUnit.hpp>

using JEB::Math::nextPrime;
using JEB::Math::firstFactor;
using JEB::Math::computePrimes;

void test_NextPrime()
{
    JU_EQUAL(nextPrime(0), 2);
    JU_EQUAL(nextPrime(2), 3);
    JU_EQUAL(nextPrime(3), 5);
    JU_EQUAL(nextPrime(5), 7);
    JU_EQUAL(nextPrime(7), 11);
    JU_EQUAL(nextPrime(11), 13);
    JU_EQUAL(nextPrime(13), 17);
    JU_EQUAL(nextPrime(17), 19);
    JU_EQUAL(nextPrime(19), 23);
    JU_EQUAL(nextPrime(23), 29);
}

void test_NextFactor()
{
    int n = -32340;
    int factor = firstFactor(n);
    JU_EQUAL(factor, -1);
    n /= factor;
    factor = firstFactor(n, factor);
    JU_EQUAL(factor, 2);
    n /= factor;
    factor = firstFactor(n, factor);
    JU_EQUAL(factor, 2);
    n /= factor;
    factor = firstFactor(n, factor);
    JU_EQUAL(factor, 3);
    n /= factor;
    factor = firstFactor(n, factor);
    JU_EQUAL(factor, 5);
    n /= factor;
    factor = firstFactor(n, factor);
    JU_EQUAL(factor, 7);
    n /= factor;
    factor = firstFactor(n, factor);
    JU_EQUAL(factor, 7);
    n /= factor;
    factor = firstFactor(n, factor);
    JU_EQUAL(factor, 11);
    n /= factor;
    factor = firstFactor(n, factor);
    JU_EQUAL(factor, 1);
}

void test_ComputePrimes()
{
    std::vector<int> ps = computePrimes(5, 5);
    JU_EQUAL(ps.size(), 5);
    JU_EQUAL(ps[0], 11);
    JU_EQUAL(ps[1], 13);
    JU_EQUAL(ps[2], 17);
    JU_EQUAL(ps[3], 19);
    JU_EQUAL(ps[4], 23);
}

JU_TESTSUITE(test_NextPrime, test_NextFactor, test_ComputePrimes);
