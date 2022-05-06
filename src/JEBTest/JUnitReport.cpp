//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "JUnitReport.hpp"

#include <iomanip>
#include "JEBTest/Session.hpp"
#include "Test.hpp"
#include "XmlWriter.hpp"

namespace JEBTest
{
    void addTestCases(std::map<std::string, std::vector<TestPtr>>& testCases,
                      std::string path, const TestPtr& test)
    {
        if (test->assertions() > 0)
            testCases[path].push_back(test);
        auto subtests = test->tests();
        if (!subtests.empty())
        {
            if (!path.empty())
                path += "/";
            path += test->name();
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
         writer.attribute("classname", std::string_view());
         if (test.assertions() != 0)
         {
             writer.attribute("assertions", (int64_t)test.assertions());
             writer.attribute("time", test.elapsedTime());
             auto& errors = test.errors();
             for (auto it = begin(errors); it != end(errors); ++it)
                 writeXmlError(writer, *it);
         }
         writer.endElement();
     }

    void writeJUnitReport(std::ostream& os, const Session& session)
    {
         auto suites = getTestCases(session.tests());
         XmlWriter writer(os);
         writer.setFormatting(XmlWriter::IndentElements);
         writer.beginElement("testsuites");
         for (auto& [name, tests] : suites)
         {
             writer.beginElement("testsuite");
             writer.attribute("name", name);
             writer.attribute("tests", int64_t(tests.size()));
             for (const auto& test : tests)
             {
                 writeXmlTestCase(writer, *test);
             }
             writer.endElement();
         }
         writer.endElement();
    }
}
