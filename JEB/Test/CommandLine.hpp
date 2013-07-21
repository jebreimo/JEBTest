#ifndef COMMANDLINE_HPP
#define COMMANDLINE_HPP

#include <memory>
#include <JEB/ArgParser/ArgParser.hpp>

struct Options
{
    Options();

    bool exclude;
    std::string file;
    bool fulltext;
    bool help;
    std::string host;
    bool junit;
    std::string logFile;
    bool text;
    bool verbose;
};

struct Args
{
    std::vector<std::string> testName;
    std::string outFile;
};

struct CommandLine
{
    CommandLine();

    enum Result {Error, Ok, Help, Info};
    Result result;

    JEB::ArgParser::ArgParser argParser;
    JEB::ArgParser::ParsedArgs parsedArgs;
    Options options;
    Args args;
};

std::unique_ptr<CommandLine> parseArgs(int argc, char* argv[]);

#endif
