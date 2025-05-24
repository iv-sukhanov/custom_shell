#include "Parser.hpp"

#include <algorithm>
#include <ios>
#include <iostream>
#include <iterator>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "ParseUtils.hpp"
#include "StringUtils.hpp"

Parser::Parser() = default;

std::regex Parser::parallelSymb{"\\s+&\\s*"};
std::regex Parser::redirectSymb{"\\s+>\\s+"};
std::string Parser::spaceSymbols{" \n\t"};

std::vector<std::unique_ptr<Command>> Parser::parse(const std::string& line) {
    using namespace std;

    auto retrieveStringFromIters([](auto it1, auto it2) { return string{it1, it2}; });

    vector<string> jobs;
    bool isLastParallel =
        utils::splitJobs(begin(line), end(line), back_inserter(jobs), parallelSymb, retrieveStringFromIters);

    // debug
    // cout << "\n#";
    // copy(begin(jobs), end(jobs), ostream_iterator<string>{cout, "# #"});
    // cout << endl;

    vector<unique_ptr<Command>> parsedCommands;
    size_t numberOfJobs = jobs.size();
    for (int i = 0; i < numberOfJobs; i++) {
        const string& job(jobs.at(i));

        bool inParallel = i < numberOfJobs - 1 || isLastParallel;
        bool withRedirection;
        try {
            withRedirection = utils::isRedirected(begin(job), end(job), redirectSymb);
        } catch (invalid_argument& e) {
            throw e;
        }

        unique_ptr<pair<string, string>> commandAndRedirection;
        if (withRedirection) {
            pair<string, string> commandWithRedirection;
            try {
                commandWithRedirection = utils::separateRedirection(begin(job), end(job), redirectSymb);
            } catch (invalid_argument& e) {
                throw e;
            }

            commandAndRedirection = make_unique<pair<string, string>>(move(commandWithRedirection));
        }

        if (withRedirection && !commandAndRedirection) {
            throw runtime_error("parse: nullptr commandParts with set redirection flag");
        }

        const string& command = withRedirection ? commandAndRedirection->first : job;
        vector<string> pieces;
        utils::splitArgs(command, back_inserter(pieces));

        unique_ptr<Command> currCommand(
            make_unique<Command>(pieces.front(), vector<string>{next(begin(pieces)), end(pieces)}));

        if (withRedirection) {
            currCommand->setOutputRedirect(utils::trim(commandAndRedirection->second, spaceSymbols));
        }
        currCommand->setParallel(inParallel);

        parsedCommands.push_back(move(currCommand));
    }

    // debug
    // for (const auto& el : parsedCommands) {
    //     cout << el->getName() << '\n' << "#";
    //     auto args = el->getArgs();
    //     copy(begin(args), end(args), ostream_iterator<string>{cout, "# #"});
    //     cout << "\nRedirected to " << el->getOutputRedirect().value_or("none") << '\n'
    //          << "Run in parallel: " << (el->isParallel() ? "yes" : "no") << endl;
    // }

    return move(parsedCommands);
}
