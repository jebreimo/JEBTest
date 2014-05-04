/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_TEST_JUNITREPORT_HPP
#define JEB_TEST_JUNITREPORT_HPP

#include <iosfwd>

namespace JEB { namespace Test {

class Session;

void writeJUnitReport(std::ostream& os, const Session& session);

}}

#endif
