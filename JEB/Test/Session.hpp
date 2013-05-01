#ifndef JEB_SESSION_HPP
#define JEB_SESSION_HPP

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

namespace JEB { namespace Test {

class Error;
class TestSuite;
typedef std::shared_ptr<TestSuite> TestSuitePtr;

class Session
{
public:
    static Session& instance();

    void beginSuite(const std::string& name = "<unnamed>");
    void endSuite();
    void suiteFailed(const Error& error);

    void beginTest(const std::string& name = "<unnamed>");
    void endTest();
    void testFailed(const Error& error);

    void unhandledException(const Error& error);

    size_t numberOfFailedSuites() const;

    const std::vector<TestSuitePtr>& suites() const;

    void print(const std::string& text);

    void assertPassed();

    std::ostream* log();
    void setLog(std::ostream* log);
private:
    Session();
    ~Session();

    std::ostream* m_Log;
    std::vector<TestSuitePtr> m_TestSuites;
};

}}

#endif
