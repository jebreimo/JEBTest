Goals for this project:
=======================
- No source code dependencies to any projects except the standard library, not even boost.
- Tests are organized with functions rather than classes.
- Adding new tests should cause as little overhead as possible.
- The error report should make it easy to discover which test, if any, has failed.
- Don't introduce syntax that confuses C++ text editors.

Example
========
    #include <JEBTest/JEBTest.hpp>

    // Define a test function
    void Test_Strings()
    {
		// Verify that the expression on the left hand side matches
		// the one on the right hand side.
        JT_EQUAL(std::string("Hello ") + "world!", "Hello world!");
    }

	// Define a test suite
    JT_TEST(Test_Strings); 

	// Macro that expands to a main function
    JT_CONSOLE_MAIN() 
