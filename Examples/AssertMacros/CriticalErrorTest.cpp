#include "JEB/JEBTest.hpp"

static void testFatalError()
{
    char* foo = nullptr;
    JT_NOT_EQUAL_FATAL(foo, (char*)nullptr);
}

JT_TEST(testFatalError);
