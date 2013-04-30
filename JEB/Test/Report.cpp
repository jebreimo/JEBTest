#include "Report.hpp"

#include <iomanip>
#include <iostream>
#include "JEB/Xml/XmlWriter.hpp"
#include "Session.hpp"
#include "TestSuite.hpp"

namespace JEB { namespace Test {

void writeReport(std::ostream& os, const Session& session)
{
    if (session.suites().empty())
    {
        os << "No tests were executed.\n";
        return;
    }
    os << "*** Test Report ***\n";
    size_t testSuiteFailures = 0;
    for (size_t i = 0; i < session.suites().size(); i++)
    {
        const TestSuite& ts = *session.suites()[i];
        os << ts.name() << ":\n";
        size_t failures = 0;
        for (size_t j = 0; j < ts.tests().size(); j++)
        {
            const Test& t = *ts.tests()[j];
            if (t.failed())
            {
                os << "  " << std::left << std::setw(20) << t.name();
                os << " FAILED (" << t.assertions()
                   << " assertions passed)\n"
                   << "    " << t.error() << "\n";
                const std::vector<Error>& context = t.error().context();
                if (!context.empty())
                {
                    for (auto c = context.begin(); c != context.end(); ++c)
                    {
                        os << "      " << c->text() << "\n";
                    }
                }
                failures++;
            }
            else
            {
                os << "  " << std::left << std::setw(20) << t.name();
                os << " PASSED (" << t.assertions() << " assertions passed)\n";
            }
        }
        if (failures != 0)
        {
            os << "  FAILED (" << ts.tests().size() - failures << " of "
               << ts.tests().size() << " tests passed)\n";
            testSuiteFailures++;
        }
        else if (ts.failed())
        {
            os << "  INTERRUPTED\n" << "    " << ts.error() << "\n";
            testSuiteFailures++;
        }
        else
        {
            os << "  SUCCESS (" << ts.tests().size() << " tests passed)\n";
        }
    }
    if (testSuiteFailures != 0)
    {
        os << "*** Result: FAILED ("
           << session.suites().size() - testSuiteFailures << " of "
           << session.suites().size() << " test suites passed) ***\n";
    }
    else
    {
        os << "*** Result: SUCCESS ("
           << session.suites().size() << " test suites passed) ***\n";
    }
    os.flush();
}

void writeXmlReport(std::ostream& os, const Session& session);

}}
