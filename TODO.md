TODO
====
- Add some test examples that also serves as "tests" of the test library
    - Add a project with macros expanded
- Implement text report
- Reduce number of public include files
- Make name clashes less likely by changing certain names used in macros (add a JT prefix to for instance TestFailure, CriticalFailure and FatalFailure)
- Handle the host option

DONE
====
- Add a way to specify execution order of "test suites"
- Implement JUnit (xml) report
- Record execution time for all tests
- Add redirection of cout, cerr and clog.

Ideas I've considered, but don't intend to implement
====================================================
- Add a way to list the names of all tests without executing them

This is possible for auto-registered tests, but will be too much of a hassle for other tests. It's not a particularly useful feature, just "neat".
