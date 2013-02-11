#ifndef JEB_TEST_TEST_HPP
#define JEB_TEST_TEST_HPP

#include <memory>
#include <string>
#include <vector>
#include "Error.hpp"

namespace JEB { namespace Test {

class Test
{
public:
    Test(const std::string& name);

    size_t assertions() const;
    void incrementAssertions();

    const Error& error() const;
    void setError(const Error& error);

    bool failed() const;
    void setFailed(bool failed);

    const std::string& name() const;
private:
    size_t m_Assertions;
    Error m_Error;
    bool m_Failed;
    std::string m_Name;
};

}}

#endif
