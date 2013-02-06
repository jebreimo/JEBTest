#include "../Matrix.hpp"
#include <JEB/Unit/JEBUnit.hpp>

using namespace JEB::Math;

template <typename T>
static void assertValue(const Matrix<T>& m,
                        size_t i,
                        size_t j,
                        T value)
{
    JU_ASSERT_MSG(m[i][j] == value,
                  "unexpected value at " << i << ", " << j << ": "
                  << m[i][j] << " (expected " << value << ")");
}

template <typename T>
static void assertValues(const Matrix<T>& m,
                         T firstValue,
                         T increment)
{
    T value = firstValue;
    for (size_t i = 0; i < m.rows(); i++)
    {
        for (size_t j = 0; j < m.columns(); j++)
        {
            assertValue<T>(m, i, j, value);
            value += increment;
        }
    }
}

template <typename T>
static void init(Matrix<T>& m, T firstValue = 0, T increment = 1)
{
    for (T* it = m.begin(); it != m.end(); it++)
    {
        *it = firstValue;
        firstValue += increment;
    }
}

static void test_Initialization()
{
    Matrix<double> matrix(4, 6);
    JU_EQUAL(matrix.rows(), 4);
    JU_EQUAL(matrix.columns(), 6);
    JU_EQUAL(matrix.size().first, matrix.rows());
    JU_EQUAL(matrix.size().second, matrix.columns());
    for (size_t i = 0; i < matrix.rows(); i++)
        for (size_t j = 0; j < matrix.columns(); j++)
            assertValue<double>(matrix, i, j, 0);
    double value = 0;
    for (Matrix<double>::iterator it = matrix.begin(); it != matrix.end(); it++)
    {
        *it = value;
        value += 1;
    }
    assertValues(matrix, 0.0, 1.0);
    matrix[2][4] = 5;
    assertValue<double>(matrix, 2, 4, 5);
}

static void test_Add()
{
    Matrix<int> m(3, 5);
    int n = 0;
    for (Matrix<int>::iterator it = m.begin(); it != m.end(); it++)
        *it = n++;
    Matrix<int> m2(4, 5);
    JU_THROWS(m += m2, std::invalid_argument);
    Matrix<int> m3(3, 5);
    std::fill(m3.begin(), m3.end(), 1);
    m += m3;
    assertValues(m, 1, 1);
}

static void test_Sub()
{
    Matrix<int> m(3, 5);
    int n = 0;
    for (Matrix<int>::iterator it = m.begin(); it != m.end(); it++)
        *it = n++;
    Matrix<int> m2(4, 5);
    JU_THROWS(m -= m2, std::invalid_argument);
    Matrix<int> m3(3, 5);
    std::fill(m3.begin(), m3.end(), 1);
    JU_EQUAL(m[0][0], 0);
    JU_EQUAL(m3[0][0], 1);
    m3 -= m;
    assertValues(m3, 1, -1);
}

static void test_Mul()
{
    Matrix<int> m(3, 5);
    int n = 0;
    for (Matrix<int>::iterator it = m.begin(); it != m.end(); it++)
        *it = n++;
    m *= 7;
    assertValues(m, 0, 7);
}

static void test_Transpose()
{
    Matrix<int> m(3, 5);
    int n = 0;
    for (Matrix<int>::iterator it = m.begin(); it != m.end(); it++)
        *it = n++;
    m.transpose();
    JU_EQUAL(m.rows(), 5);
    JU_EQUAL(m.columns(), 3);
    for (size_t i = 0; i < m.rows(); i++)
        for (size_t j = 0; j < m.columns(); j++)
            assertValue<int>(m, i, j, j * m.rows() + i);
}

static void test_Negation()
{
    Matrix<int> m(2, 2);
    init(m);
    assertValues(-m, 0, -1);
}

static void test_Multiplication()
{
}

JU_TESTSUITE(test_Initialization,
             test_Add,
             test_Sub,
             test_Mul,
             test_Transpose,
             test_Negation);
