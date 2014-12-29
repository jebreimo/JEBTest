/* JEBTest: A C++ unit testing framework
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBTEST_TEST_VISUALSTUDIOREPORT_HPP
#define JEBTEST_TEST_VISUALSTUDIOREPORT_HPP

#include <iosfwd>

namespace JEBTest {

class Session;

bool isRunnningInVisualStudio();

void writeVisualStudioReport(
        void (*reportFunc)(std::ostream&, const Session&),
        const Session& session);

}

#endif
