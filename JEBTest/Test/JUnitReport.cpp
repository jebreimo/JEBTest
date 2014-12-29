/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JUnitReport.hpp"

#include <iomanip>
#include <iostream>
#include "JEBIO/Xml/XmlWriter.hpp"

#include "Session.hpp"
#include "Test.hpp"

namespace JEBTest {

using namespace JEBTest_JEBIO::Xml;

void addTestCases(std::map<std::string, std::vector<TestPtr>>& testCases,
                  std::string path, TestPtr test)
{
    if (test->assertions() > 0)
        testCases[path].push_back(test);
    auto subtests = test->tests();
    if (!subtests.empty())
    {
        path += "/";
        path += test->name();
        auto subtests = test->tests();
        for (auto it = begin(subtests); it != end(subtests); ++it)
            addTestCases(testCases, path, *it);
    }
}

std::map<std::string, std::vector<TestPtr>> getTestCases(
        const std::vector<TestPtr>& tests)
{
    std::map<std::string, std::vector<TestPtr>> testCases;
    for (auto it = begin(tests); it != end(tests); ++it)
        addTestCases(testCases, std::string(), *it);
    return testCases;
}

void writeXmlError(XmlWriter& writer, const Error& error)
{
    if (error.type() == Error::UnhandledException)
        writer.beginElement("error");
    else
        writer.beginElement("failure");
    writer.attribute("message", error.message());
    writer.attribute("type", Error::levelName(error.type()));
    writer.characterData(error.file());
    writer.characterData("[");
    writer.characterData((int)error.lineNo());
    writer.characterData("]");
    auto& context = error.context();
    for (auto c = begin(context); c != end(context); ++c)
    {
        writer.characterData("\n");
        writer.characterData(c->text());
    }
    writer.endElement();
}

void writeXmlTestCase(XmlWriter& writer, const Test& test)
{
    writer.beginElement("testcase");
    writer.attribute("name", test.name());
    if (test.assertions() != 0)
    {
        writer.attribute("assertions", (int64_t)test.assertions());
        writer.attribute("name", "NONE");
        writer.attribute("time", test.elapsedTime());
        auto& errors = test.errors();
        for (auto it = begin(errors); it != end(errors); ++it)
            writeXmlError(writer, *it);
    }
    writer.endElement();
}

void writeJUnitReport(std::ostream& os, const Session& session)
{
    auto testCases = getTestCases(session.tests());
    XmlWriter writer(os);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("testsuites");
    for (auto it = begin(testCases); it != end(testCases); ++it)
    {
        writer.beginElement("testsuite");
        writer.attribute("name", it->first);
        for (auto t = begin(it->second); t != end(it->second); ++t)
        {
            writeXmlTestCase(writer, **t);
        }
        writer.endElement();
    }
    writer.endElement();
}

}
