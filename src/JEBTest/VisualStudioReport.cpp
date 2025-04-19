//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "VisualStudioReport.hpp"

#if (_MSC_VER > 1200)

#include <sstream>
#include <windows.h>

namespace JEBTest
{
    bool isRunningInVisualStudio()
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

namespace JEBTest
{
    bool isRunningInVisualStudio()
    {
        return false;
    }

    void writeVisualStudioReport(
            void (*)(std::ostream&, const Session&),
            const Session&)
    {}
}

#endif
