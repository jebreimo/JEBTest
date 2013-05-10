#include "JEB/JEBTest.hpp"

void testCriticalError()
{
    char* foo = nullptr;
    JT_NOT_EQUAL_CRITICAL(foo, nullptr);
}

JT_TESTSUITE(testCriticalError);
