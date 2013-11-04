#ifndef PARSEARGUMENTS_HPP
#define PARSEARGUMENTS_HPP

#include <memory>
#include <string>
#include <vector>

/** @file
  * Defines the function parse_arguments and its result Arguments.
  */

/** @brief The result of parse_arguments
  */
struct Arguments
{
    /** @brief Assigns the default values to all members.
      */
    Arguments();
    /** @brief Assigns the default values to all members.
      */
    ~Arguments();

    /** @brief Member for options: -e, --exclude
      */
    bool exclude;
    /** @brief Member for options: --fulltext
      */
    bool fulltext;
    /** @brief Member for options: -h, --help
      */
    bool help;
    /** @brief Member for options: --host
      */
    std::string host;
    /** @brief Member for options: --junit
      */
    bool junit;
    /** @brief Member for options: -l, --logfile
      */
    std::string logfile;
    /** @brief Member for options: -f, --report
      */
    std::string report;
    /** @brief Member for arguments: test_name
      */
    std::vector<std::string> test_name;
    /** @brief Member for options: --text
      */
    bool text;
    /** @brief Member for options: -q, --quiet, -v, --verbose
      */
    bool verbose;

    enum Result {
        /** @brief parse_arguments parsed the arguments successfully.
          */
        RESULT_OK,
        /** @brief parse_arguments encountered a help option.
          *
          * The help message has been displayed. The option and argument
          * members of this struct can not be relied upon.
          */
        RESULT_HELP,
        /** @brief There are invalid or missing options or arguments.
          *
          * An error message has been displayed. The option and argument
          * members of this struct can not be relied upon.
          */
        RESULT_ERROR
    };

    /** @brief The exit status of parse_arguments.
      *
      * This member should always be checked before any of the other members
      * are read.
      */
    Result parse_arguments_result;
};

/** @brief Parses the arguments in @a argv.
  *
  * @param argc the number of values in argv.
  * @param argv the arguments (an array of char-strings).
  * @returns an instance of Arguments with values in
  *     accordance with the parsed arguments. If @a argc is 0 the
  *     returned value is a nullptr.
  */
std::unique_ptr<Arguments> parse_arguments(int argc, char* argv[]);

#endif
