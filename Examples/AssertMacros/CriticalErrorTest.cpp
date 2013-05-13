#include "JEB/JEBTest.hpp"

static void testCriticalError()
{
    char* foo = nullptr;
    JT_NOT_EQUAL_CRITICAL(foo, (char*)nullptr);
}

JT_TEST(testCriticalError);
