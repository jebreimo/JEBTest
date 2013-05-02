#ifndef JEB_SESSION_HPP
#define JEB_SESSION_HPP

#include <iosfwd>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace JEB { namespace Test {

class Error;
typedef std::shared_ptr<class Test> TestPtr;

class Session
{
public:
    static Session& instance();

    void beginTest(const std::string& name = "<unnamed>");
    void endTest();
    void testFailed(const Error& error);
    void assertPassed();
    void unhandledException(const Error& error);

    size_t numberOfFailedTests() const;

    bool areAllTestsEnabled() const;
    void setAllTestsEnabled(bool enable);
    bool isTestEnabled(const std::string& name) const;
    void setTestEnabled(const std::string& name, bool enable);

    const std::vector<TestPtr>& tests() const;

    void print(const std::string& text);

    std::ostream* log();
    void setLog(std::ostream* log);
private:
    Session();
    ~Session();
    std::string getTestName(const std::string& name) const;

    bool m_AllTestsEnabled;
    std::map<std::string, bool> m_EnabledTests;
    std::ostream* m_Log;
    std::vector<TestPtr> m_Tests;
    std::vector<TestPtr> m_ActiveTest;
};

}}

#endif
