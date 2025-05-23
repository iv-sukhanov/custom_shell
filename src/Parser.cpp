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
#include <vector>

#include "ParseUtils.hpp"
#include "StringUtils.hpp"

Parser::Parser() = default;

std::vector<std::unique_ptr<Command>> Parser::parse(const std::string& line) {
    using namespace std;

    auto retrieveStringFromIters([](auto it1, auto it2) { return string{it1, it2}; });

    vector<string> jobs;
    regex parallelSymb{"\\s+&\\s*"};
    bool isLastParallel =
        utils::splitJobs(begin(line), end(line), back_inserter(jobs), parallelSymb, retrieveStringFromIters);

    // debug
    cout << "\n#";
    copy(begin(jobs), end(jobs), ostream_iterator<string>{cout, "# #"});
    cout << endl;

    vector<unique_ptr<Command>> parsedCommands;
    size_t numberOfJobs = jobs.size();
    for (int i = 0; i < numberOfJobs; i++) {
        const string& job(jobs.at(i));
        auto redirectSymb = find(begin(job), end(job), '>');
        bool withRedirection = redirectSymb != end(job);
        bool inParallel = i < numberOfJobs - 1 || isLastParallel;
        unique_ptr<vector<string>> commandParts;

        if (withRedirection) {
            commandParts = make_unique<vector<string>>();
            utils::split(begin(job), end(job), '>', back_inserter(*commandParts), retrieveStringFromIters);
        }

        if (withRedirection && !commandParts) {
            throw runtime_error("parse: nullptr commandParts with set redirection flag");
        }

        const string& command =
            withRedirection ? commandParts->front() : job;  // TODO consider using std::pair
        vector<string> pieces;
        const string spaceSymbols = " \n\t";
        utils::split(begin(command), end(command), begin(spaceSymbols), end(spaceSymbols),
                     back_inserter(pieces), retrieveStringFromIters);

        unique_ptr<Command> currCommand(
            make_unique<Command>(pieces.front(), vector<string>{next(begin(pieces)), end(pieces)}));

        if (withRedirection) {
            currCommand->setOutputRedirect(utils::trim(commandParts->back(), spaceSymbols));
        }
        currCommand->setParallel(inParallel);

        parsedCommands.push_back(move(currCommand));
    }

    // debug
    for (const auto& el : parsedCommands) {
        cout << el->getName() << '\n' << "#";
        auto args = el->getArgs();
        copy(begin(args), end(args), ostream_iterator<string>{cout, "# #"});
        cout << "\nRedirected to " << el->getOutputRedirect().value_or("none") << endl;
    }

    return move(parsedCommands);
}
