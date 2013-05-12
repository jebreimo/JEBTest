Test
====
- Add some test examples that also serves as "tests" of the test library
- Implement text report
- Implement JUnit (xml) report
- Add command line interface
- Add redirection of cout, cerr and clog.
- Record execution time for all tests
- Add a way to specify execution order of "test suites"
- Reduce number of public include files
- Make name clashes less likely by changing certain names used in macros (add a JT prefix to for instance TestFailure, CriticalFailure and FatalFailure)

Command line interface
======================
    %prog [options] [TEST ...]

If any test names are given, only thos tests are preformed, otherwise all tests are performed. If tests are arranged in a hierarchy, use "/" to separate "path" elements.

If you have tests arranged like this:

    test_Sys:
        test_Path:
            test_splitExtension
            test_join
            test_normalize
        test_Environment:
            test_read
            test_setValue
    test_String:
        test_join
        test_split

To only run tests in test_Sys, use

    %prog test_Sys

To run all tests in test_Path, use

    %prog test_Sys/test_Path

To only run test_Join under test_Path, use

    %prog test_Sys/test_Path/test_join

Options:
--------
- "--junit" for JUnit xml report
- "--txt" for text report
- "-o:FILE" or "--output=FILE" for report file
- "-l:FILE" or "--logfile=FILE" for redirecting cout, cerr and clog to a file.
- "-e" or "--exclude" to exclude the tests listed after the options rather than include those tests.

Ideas I've considered, but don't intend to implement
====================================================
- Add a way to list the names of all tests without executing them

This is possible for auto-registered tests, but will be too much of a hassle for other tests. It's not a particularly useful feature, just "neat".
