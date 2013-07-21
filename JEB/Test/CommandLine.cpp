#include "CommandLine.hpp"

#include <JEB/String/FromString.hpp>

Options::Options()
    : exclude(false),
      fulltext(false),
      help(false),
      junit(false),
      text(false),
      verbose(false)
{}

CommandLine::CommandLine()
    : result(Error)
{}

static void initialize(JEB::ArgParser::ArgParser& ap)
{
    ap.addHelpText("USAGE\n"
                   "%prog%& [options]& [test& name& ...]& <out-file>\n" "\n"
                   "Executes unit tests.\n" "\n" "ARGUMENTS\n");
    ap.addHelpText("[testName& ...]\n"
                   "The name of the test or tests that will be run. All tests are run if no "
                   "test names are given. If the --exclude option is used, all tests except "
                   "the given ones are run.\n" "\n"
                   "Tests are typically arranged in a two-level hierarchy with a parent and "
                   "several child-tests. To disable a parent test and all its children, just "
                   "enter the name of the parent. To disable a spesific child enter the names "
                   "of both the parent and the child, separated with a single \"/\".\n");
    ap.addHelpText("<outFile>\n"
                   "The name of the file that some kind of output will be written to. This is a "
                   "text file.\n");
    ap.addHelpText("\n" "GENERAL OPTIONS\n");
    ap.addFlag("exclude", "-e --exclude", true,
               "Exclude the tests whose names appear after the options and run everything "
               "else. This is the opposite of the default behavior.\n");
    ap.addFlag("help", "-h --help", true,
               "Show program help.\n");
    ap.addOption("logFile", "-l --log-file", "VALUE",
                 "Redirect all the output the tests normally write to stdout or stderr to "
                 "a file named FILE instead. (This does not affect the test reports).\n");
    ap.addFlag("verbose", "-q --quiet", false,
               "Don't display extra information while running tests. (Opposite of -v.)\n");
    ap.addFlag("verbose", "-v --verbose", true,
               "Display extra information while running tests.\n");
    ap.addHelpText("\n" "REPORT OPTIONS\n");
    ap.addFlag("junit", "--junit", true,
               "Produce a test report in the JUnit XML format.\n");
    ap.addFlag("text", "--text", true,
               "Produce a plain text test report that only list failed tests. This is the "
               "default.\n");
    ap.addFlag("fulltext", "--fulltext", true,
               "Produce a plain text test report that lists all tests.\n");
    ap.addOption("file", "-f --file", "VALUE",
                 "The name of the report file. If multiple report files are produced, FILE "
                 "will have the suitable file type extension appended to it (txt, xml etc.). "
                 "Test reports are written to stdout if this option isn't used.\n");
    ap.addOption("host", "--host", "HOST",
                 "Set the host name. This option has no effect on tests, it is only used in the report.\n");
    ap.addHelpText("\n");
}

template <typename T>
T fromString(const std::string& s, const std::string& name)
{
    T value;
    if (!JEB::String::fromString(s, value))
        throw std::runtime_error(name + ": unable to assign value \"" + s + "\"");
    return value;
}

static void readRegularOptions(Options& opts, const JEB::ArgParser::ParsedArgs& pa)
{
    if (pa.hasOption("exclude"))
        opts.exclude = fromString<bool>(pa.option("exclude"), "exclude");
    if (pa.hasOption("file"))
        opts.file = fromString<std::string>(pa.option("file"), "file");
    if (pa.hasOption("fulltext"))
        opts.fulltext = fromString<bool>(pa.option("fulltext"), "fulltext");
    if (pa.hasOption("host"))
        opts.host = fromString<std::string>(pa.option("host"), "host");
    if (pa.hasOption("junit"))
        opts.junit = fromString<bool>(pa.option("junit"), "junit");
    if (pa.hasOption("logFile"))
        opts.logFile = fromString<std::string>(pa.option("logFile"), "logFile");
    if (pa.hasOption("text"))
        opts.text = fromString<bool>(pa.option("text"), "text");
    if (pa.hasOption("verbose"))
        opts.verbose = fromString<bool>(pa.option("verbose"), "verbose");
}

static void readArgs(Args& args, const JEB::ArgParser::ParsedArgs& pa)
{
    size_t excess = pa.argumentCount() - 1;
    std::vector<std::string>::const_iterator it = pa.arguments().begin();
    
    for (size_t i = 0; i < excess; ++i)
    {
        args.testName.push_back(fromString<std::string>(*it, "testName"));
        ++it;
    }
    excess = 0;
    
    args.outFile = fromString<std::string>(*it, "outFile");
    ++it;
}

std::unique_ptr<CommandLine> parseArgs(int argc, char* argv[])
{
    std::unique_ptr<CommandLine> cl(new CommandLine);
    initialize(cl->argParser);
    cl->argParser.parse(argc, argv, cl->parsedArgs);

    if (!cl->parsedArgs)
    {
        cl->argParser.writeErrors(cl->parsedArgs);
        return cl;
    }
    if (cl->parsedArgs.tryGetOption("help", cl->options.help))
    {
        cl->argParser.writeHelp();
        cl->result = CommandLine::Help;
        return cl;
    }
    if (cl->parsedArgs.argumentCount() < 1)
    {
        cl->argParser.writeMessage("Too few arguments.");
        return cl;
    }

    try
    {
        readRegularOptions(cl->options, cl->parsedArgs);
        readArgs(cl->args, cl->parsedArgs);
    }
    catch (std::runtime_error& ex)
    {
        cl->argParser.writeMessage(ex.what());
        cl->result = CommandLine::Error;
        return cl;
    }

    cl->result = CommandLine::Ok;

    return cl;
}
