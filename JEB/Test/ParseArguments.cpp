#include "ParseArguments.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <sstream>

namespace JEB { namespace Test {

namespace
{
    std::string programName;
    std::string helpText =
        "USAGE\n"
        "$prog$ [options] [test-name] ...\n"
        "\n"
        "Executes the unit tests in $prog$.\n"
        "\n"
        "ARGUMENTS\n"
        "  test-name\n"
        "    The name of the test or tests that will be run. All tests are run if no\n"
        "    test names are given. If the --exclude option is used, all tests except the\n"
        "    given ones are run.\n"
        "\n"
        "    Tests are typically arranged in a two-level hierarchy with a parent and\n"
        "    several child-tests. To disable a parent test and all its children, just\n"
        "    enter the name of the parent. To disable a specific child, enter the names\n"
        "    of both the parent and the child separated by a single \"/\".\n"
        "\n"
        "    Example:\n"
        "        If the tests are arranged like this:\n"
        "\n"
        "            test_Sys:\n"
        "                test_Path:\n"
        "                    test_splitExtension\n"
        "                    test_join\n"
        "                    test_normalize\n"
        "                test_Environment:\n"
        "                    test_read\n"
        "                    test_setValue\n"
        "            test_String:\n"
        "                test_join\n"
        "                test_split\n"
        "\n"
        "        To only run tests in test_Sys, use\n"
        "\n"
        "            $prog$ test_Sys\n"
        "\n"
        "        To run all tests in test_Path, use\n"
        "\n"
        "            $prog$ test_Sys/test_Path\n"
        "\n"
        "        To only run test_Join under test_Path, use\n"
        "\n"
        "            $prog$ test_Sys/test_Path/test_join\n"
        "\n"
        "GENERAL OPTIONS\n"
        "-h, --help\n"
        "    Show program help.\n"
        "-e, --exclude\n"
        "    Exclude the named tests and run everything else. This is the opposite of\n"
        "    the default behavior.\n"
        "-l FILE, --log-file=FILE\n"
        "    Redirect all the output the tests normally write to stdout or stderr to a\n"
        "    file named FILE instead. (This does not affect the test reports).\n"
        "-q, --quiet\n"
        "    Don't display extra information while running tests. (Opposite of -v.)\n"
        "-v, --verbose\n"
        "    Display extra information while running tests.\n"
        "\n"
        "REPORT OPTIONS\n"
        "--junit\n"
        "    Produce a test report in the JUnit XML format.\n"
        "--text\n"
        "    Produce a plain text test report that only list failed tests. This is the\n"
        "    default.\n"
        "--fulltext\n"
        "    Produce a plain text test report that lists all tests.\n"
        "-f FILE, --file=FILE\n"
        "    The name of the report file. If multiple report files are produced, FILE\n"
        "    will have the suitable file type extension appended to it (txt, xml etc.).\n"
        "    Test reports are written to stdout if this option isn't used.\n"
        "--host=HOST\n"
        "    Set the host name. This option has no effect on tests; it's only included\n"
        "    in the test report.\n"
        "\n";

    void writeHelp()
    {
        std::string s = "$prog$";
        auto first = begin(helpText);
        while (first != end(helpText))
        {
            auto last = std::search(first, end(helpText), begin(s), end(s));
            if (last == end(helpText))
                break;
            std::cout.write(&*first, distance(first, last));
            std::cout << programName;
            first = last + 6;
        }
        std::cout.write(&*first, distance(first, end(helpText)));
        std::cout.flush();
    }

    bool resemblesShortOption(const char* s)
    {
        if ((s[0] == '-') && (s[1] != '\0') &&
            (s[1] != '-' || s[2] == '\0' || s[2] == '='))
            return true;
        else
            return false;
    }

    bool resemblesOption(const char* s)
    {
        return s[0] == '-' && s[1] != '\0';
    }

    class ArgumentIterator
    {
    public:
        ArgumentIterator(int argc, char* argv[])
            : m_ArgIt(*argv),
              m_ArgsIt(&argv[0]),
              m_ArgsEnd(&argv[argc])
        {}

        bool nextArgument(std::string& arg)
        {
            arg.clear();
            if (m_ArgsIt == m_ArgsEnd)
            {
                return false;
            }
            else if (m_ArgIt != *m_ArgsIt)
            {
                arg = "-";
                arg.push_back(*m_ArgIt);
                if (!*++m_ArgIt)
                    m_ArgIt = *++m_ArgsIt;
                return true;
            }

            if (resemblesShortOption(m_ArgIt))
            {
                arg.assign(m_ArgIt, m_ArgIt + 2);
                if (*(m_ArgIt + 2))
                    m_ArgIt += 2;
                else
                    m_ArgIt = *++m_ArgsIt;
                return true;
            }

            char* end = m_ArgIt;
            if (resemblesOption(m_ArgIt))
            {
                end += 3;
                while (*end && *end != '=')
                    ++end;
            }
            else
            {
                while (*end)
                    ++end;
            }

            arg.assign(m_ArgIt, end);
            if (*end)
                m_ArgIt = end + 1;
            else
                m_ArgIt = *++m_ArgsIt;
            return true;
        }

        bool nextValue(std::string& value)
        {
            if (m_ArgsIt == m_ArgsEnd)
                return false;
            value = m_ArgIt;
            m_ArgIt = *++m_ArgsIt;
            return true;
        }

        bool hasValue() const
        {
            return m_ArgIt != *m_ArgsIt;
        }
    private:
        char* m_ArgIt;
        char** m_ArgsIt;
        char** m_ArgsEnd;
    };

    template <typename T>
    bool fromString(const std::string& s, T& value)
    {
        std::istringstream stream(s);
        stream >> std::boolalpha >> value;
        return !stream.fail();
    }

    bool fromString(const std::string& s, std::string& value)
    {
        value = s;
        return true;
    }

    template <typename T>
    std::string toString(const T& value)
    {
        std::ostringstream stream;
        stream << value;
        return stream.str();
    }

    std::string toString(const std::string& value)
    {
        return value;
    }

    bool error(const std::string& flag,
               Arguments& result,
               const std::string& errorMsg)
    {
        std::cerr << "Error: " << flag << ": " << errorMsg << "\n"
                  << "Run \"" << programName
                  << " -h\" for help.\n";
        result.parse_arguments_result = Arguments::RESULT_ERROR;
        return false;
    }

    template <typename T>
    bool getValue(T& value,
                  const std::string& flag,
                  ArgumentIterator& argIt,
                  Arguments& result)
    {
        std::string strValue;
        if (!argIt.nextValue(strValue))
            return error(flag, result, "no value provided");
        if (!fromString(strValue, value))
            return error(flag, result, "invalid option value \"" + strValue + "\".");
        return true;
    }

    bool process_exclude_option(const std::string& flag,
                                ArgumentIterator& argIt,
                                Arguments& result)
    {
        result.exclude = true;
        if (!resemblesShortOption(flag.c_str()) && argIt.hasValue())
            return error(flag, result, "option does not take a value.");
        return true;
    }
    
    bool process_file_option(const std::string& flag,
                             ArgumentIterator& argIt,
                             Arguments& result)
    {
        if (!getValue(result.file, flag, argIt, result))
            return false;
        return true;
    }
    
    bool process_fulltext_option(const std::string& flag,
                                 ArgumentIterator& argIt,
                                 Arguments& result)
    {
        result.fulltext = true;
        if (argIt.hasValue())
            return error(flag, result, "option does not take a value.");
        return true;
    }
    
    bool process_help_option(const std::string& flag,
                             ArgumentIterator& argIt,
                             Arguments& result)
    {
        writeHelp();
        result.help = true;
        result.parse_arguments_result = Arguments::RESULT_HELP;
        return false;
    }
    
    bool process_host_option(const std::string& flag,
                             ArgumentIterator& argIt,
                             Arguments& result)
    {
        if (!getValue(result.host, flag, argIt, result))
            return false;
        return true;
    }
    
    bool process_junit_option(const std::string& flag,
                              ArgumentIterator& argIt,
                              Arguments& result)
    {
        result.junit = true;
        if (argIt.hasValue())
            return error(flag, result, "option does not take a value.");
        return true;
    }
    
    bool process_log_file_option(const std::string& flag,
                                 ArgumentIterator& argIt,
                                 Arguments& result)
    {
        if (!getValue(result.log_file, flag, argIt, result))
            return false;
        return true;
    }
    
    bool process_quiet_option(const std::string& flag,
                              ArgumentIterator& argIt,
                              Arguments& result)
    {
        result.verbose = false;
        if (!resemblesShortOption(flag.c_str()) && argIt.hasValue())
            return error(flag, result, "option does not take a value.");
        return true;
    }
    
    bool process_text_option(const std::string& flag,
                             ArgumentIterator& argIt,
                             Arguments& result)
    {
        result.text = true;
        if (argIt.hasValue())
            return error(flag, result, "option does not take a value.");
        return true;
    }
    
    bool process_verbose_option(const std::string& flag,
                                ArgumentIterator& argIt,
                                Arguments& result)
    {
        result.verbose = true;
        if (!resemblesShortOption(flag.c_str()) && argIt.hasValue())
            return error(flag, result, "option does not take a value.");
        return true;
    }

    typedef bool (*ProcessOptionFunc)(const std::string&,
                                      ArgumentIterator&,
                                      Arguments&);
    typedef std::pair<std::string, ProcessOptionFunc> OptionProcessor;

    OptionProcessor optionProcessors[] = {
        OptionProcessor("-e", process_exclude_option),
        OptionProcessor("--exclude", process_exclude_option),
        OptionProcessor("-f", process_file_option),
        OptionProcessor("--file", process_file_option),
        OptionProcessor("--fulltext", process_fulltext_option),
        OptionProcessor("-h", process_help_option),
        OptionProcessor("--help", process_help_option),
        OptionProcessor("--host", process_host_option),
        OptionProcessor("--junit", process_junit_option),
        OptionProcessor("-l", process_log_file_option),
        OptionProcessor("--log-file", process_log_file_option),
        OptionProcessor("-q", process_quiet_option),
        OptionProcessor("--quiet", process_quiet_option),
        OptionProcessor("--text", process_text_option),
        OptionProcessor("-v", process_verbose_option),
        OptionProcessor("--verbose", process_verbose_option)
    };

    ProcessOptionFunc findOptionProcessor(const std::string& flag)
    {
        const OptionProcessor* op = std::find_if(
                std::begin(optionProcessors),
                std::end(optionProcessors),
                [&](const OptionProcessor& op) {return op.first == flag;});
        if (op == std::end(optionProcessors))
            return NULL;
        return op->second;
    }

}

Arguments::Arguments()
    : exclude(false),
      fulltext(false),
      help(false),
      junit(false),
      text(false),
      verbose(true),
      parse_arguments_result(RESULT_OK)
{}

Arguments::~Arguments()
{}

std::unique_ptr<Arguments> parse_arguments(int argc, char* argv[])
{
    if (argc == 0)
        return std::unique_ptr<Arguments>();

    size_t pos = std::string(argv[0]).find_last_of("/\\");
    if (pos == std::string::npos)
        programName = argv[0];
    else
        programName = &argv[0][pos + 1];

    std::unique_ptr<Arguments> result(new Arguments);
    std::vector<std::string> args;

    ArgumentIterator argIt(argc - 1, argv + 1);
    std::string arg;
    while (argIt.nextArgument(arg))
    {
        ProcessOptionFunc func = findOptionProcessor(arg);
        if (func)
        {
            if (!func(arg, argIt, *result))
                return result;
        }
        else if (resemblesOption(arg.c_str()))
        {
            error(arg, *result, "unknown option.");
            return result;
        }
        else
        {
            args.push_back(arg);
        }
    }


    size_t excess = args.size() - 0;
    std::vector<std::string>::const_iterator it = args.begin();

    for (size_t i = 0; excess && i < -1; ++i)
    {
        result->test_name.push_back(*it++);
        --excess;
    }
    return result;
}

}}
