TBD

Examples
========

First the equivalent of a "hello world":

    #include <JEB/JEBTest.hpp>

    // Define a test function
    void TEST_Integers()
    {
        JT_EQUAL(4 * 7, 28); // Ver
        JT_EQUAL(std::string("Hello ") + "world!", "Hello world!");
    }

    JT_TESTSUITE(TEST_Integers); // Creates a test suite

    JT_CONSOLE_MAIN() // Macro that expands to a main function

