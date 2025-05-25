/**
 * @file Parser.cpp
 * @brief File implemets Parser class
 *
 * The Parser class splits the input line into jobs, where a job is a single command that can be executed,
 * meaning if there are many parallel commands in the line, they will be split into separate jobs. Each job
 * can have arguments and can be redirected to a file. Then each job is parsed into a Command object.
 *
 * @author Sukhanov Ivan
 * @date 25/5/2025
 * @version 1.0
 */

#include "Parser.hpp"

#include "ParseUtils.hpp"
#include "StringUtils.hpp"

/// @brief Default constructor for Parser.
Parser::Parser() = default;

/// @brief Regular expression for detecting parallel execution symbols.
std::regex Parser::parallelSymb{"\\s+&\\s*"};

/// @brief Regular expression for detecting output redirection symbols.
std::regex Parser::redirectSymb{"\\s+>\\s+"};

/// @brief String containing whitespace and space-like symbols for parsing.
std::string Parser::spaceSymbols{" \n\t"};

/**
 * @brief Parses the input command line and returns a vector of Command objects.
 * @param line The input line string to parse.
 * @return std::vector<std::unique_ptr<Command>> Parsed commands.
 * @throws std::invalid_argument if job splitting or redirection parsing fails.
 */
std::vector<std::unique_ptr<Command>> Parser::parse(const std::string& line) {
    using namespace std;

    // split the input line into jobs based on the parallel execution symbol
    vector<string> jobs;
    auto retrieveStringFromIters([](auto it1, auto it2) { return string{it1, it2}; });
    bool isLastParallel = utils::splitByRegex(begin(line), end(line), back_inserter(jobs), parallelSymb,
                                              retrieveStringFromIters);

    // parse each job into a Command object
    vector<unique_ptr<Command>> parsedCommands;
    size_t numberOfJobs = jobs.size();
    for (int i = 0; i < numberOfJobs; i++) {
        const string& job(jobs.at(i));

        bool inParallel = i < numberOfJobs - 1 || isLastParallel;
        bool withRedirection;
        try {
            withRedirection = utils::isPresent(begin(job), end(job), redirectSymb);
        } catch (invalid_argument& e) {
            throw e;
        }

        parsedCommands.push_back(move(composeCommand(job, withRedirection, inParallel)));
    }

    return move(parsedCommands);
}

/**
 * @brief Composes a Command object from the given job string.
 * @param job The job string to parse.
 * @param redirect Indicates if output redirection is present.
 * @param parallel Indicates if the command should be run in parallel.
 * @return std::unique_ptr<Command> The composed Command object.
 * @throws std::invalid_argument if redirection parsing fails.
 * @throws std::runtime_error if redirection is set but command parts are missing.
 */
std::unique_ptr<Command> Parser::composeCommand(const std::string& job, bool redirect, bool parallel) {
    using namespace std;

    // in case of redirection, separate the command and the redirection part
    unique_ptr<pair<string, string>> commandAndRedirection;
    if (redirect) {
        pair<string, string> commandWithRedirection;
        try {
            commandWithRedirection = utils::cleaveByRegex(begin(job), end(job), redirectSymb);
        } catch (invalid_argument& e) {
            throw e;
        }

        commandAndRedirection = make_unique<pair<string, string>>(move(commandWithRedirection));
    }

    if (redirect && !commandAndRedirection) {
        throw runtime_error("parse: nullptr commandParts with set redirection flag");
    }

    // split the job into command pieces (words, arguments, etc.)
    const string& command = redirect ? commandAndRedirection->first : job;
    vector<string> pieces;
    utils::splitRespectingQuotes(command, back_inserter(pieces));

    // combine the command pieces into a Command object
    unique_ptr<Command> currCommand(
        make_unique<Command>(pieces.front(), vector<string>{next(begin(pieces)), end(pieces)}));

    if (redirect) {
        currCommand->setOutputRedirect(utils::trim(commandAndRedirection->second, spaceSymbols));
    }
    currCommand->setParallel(parallel);

    return move(currCommand);
}
