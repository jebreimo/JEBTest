#include <iosfwd>

namespace JEB { namespace Test {

class Session;

void writeReport(std::ostream& os, const Session& session);
void writeXmlReport(std::ostream& os, const Session& session);

}}
