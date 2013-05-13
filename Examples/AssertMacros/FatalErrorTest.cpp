#include "JEB/JEBTest.hpp"

static void testFatalError()
{
    char* foo = nullptr;
    JT_NOT_EQUAL_FATAL(foo, (char*)nullptr);
}

JT_PRIORITIZED_TEST(-1, testFatalError);
