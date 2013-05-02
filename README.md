Goals for this project:
=======================
- No source code dependencies to any projects except the standard library, not even boost
- Tests are organized with functions rather than classes
- Adding new tests should cause as little overhead as possible
- The error report should make it easy to discover which test, if any, has failed 
- Don't introduce any syntax that confuses C++ text editors

There are a couple of reasons for prefering test and as functions rather than classes:

- Less overhead for the programmer (less typing)
- When tests share a common data set, classes tend to force the use of setup and tear-down steps that make RAII less elegant than it should be.

TODO
====
- Proper console report


Examples
========

First the equivalent of a "hello world":

    #include <JEB/JEBTest.hpp>

    // Define a test function
    void TEST_Integers()
    {
		// Verify that the expression on the left hand side matches
		// the one on the right hand side.
        JT_EQUAL(std::string("Hello ") + "world!", "Hello world!");
    }

	// Define a test suite
    JT_TESTSUITE(TEST_Integers); 

	// Macro that expands to a main function
    JT_CONSOLE_MAIN() 
