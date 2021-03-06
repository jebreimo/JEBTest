/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "VisualStudioReport.hpp"

#if (_MSC_VER > 1200)

#include <sstream>
#include <windows.h>

namespace JEBTest {

bool isRunnningInVisualStudio()
{
    return IsDebuggerPresent() != 0;
}

void writeVisualStudioReport(
        void (*reportFunc)(std::ostream&, const Session&),
        const Session& session)
{
    std::ostringstream ss;
    reportFunc(ss, session);
    OutputDebugStringA(ss.str().c_str());
}

}

#else

namespace JEBTest {

bool isRunnningInVisualStudio()
{
    return false;
}

void writeVisualStudioReport(
        void (*reportFunc)(std::ostream&, const Session&),
        const Session& session)
{}

}

#endif
