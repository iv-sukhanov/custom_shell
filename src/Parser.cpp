#include "Parser.hpp"

#include <algorithm>
#include <ios>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "StringUtils.hpp"

Parser::Parser() = default;

std::vector<std::unique_ptr<Command>> Parser::parse(const std::string& line) {
    using namespace std;

    auto retrieveStringFromIters([](auto it1, auto it2) { return string{it1, it2}; });

    auto redirectSymb = find(begin(line), end(line), '>');
    bool withRedirection = redirectSymb != end(line);
    unique_ptr<vector<string>> commandParts;

    if (withRedirection) {
        commandParts = make_unique<vector<string>>();
        utils::split(begin(line), end(line), '>', back_inserter(*commandParts), retrieveStringFromIters);
    }

    // debug
    // if (withRedirection && commandParts) {
    //     copy(begin(*commandParts), end(*commandParts), ostream_iterator<string>(cout, "\n"));
    // }

    if (withRedirection && !commandParts) {
        throw runtime_error("parse: nullptr commandParts with set redirection flag");
    }

    const string& command = withRedirection ? commandParts->front() : line;
    vector<string> pieces;
    const string spaceSymbols = " \n\t";
    utils::split(begin(command), end(command), begin(spaceSymbols), end(spaceSymbols), back_inserter(pieces),
                 retrieveStringFromIters);

    vector<unique_ptr<Command>> output;
    output.push_back(make_unique<Command>(pieces.front(), vector<string>{begin(pieces) + 1, end(pieces)}));
    if (withRedirection) {
        output.front()->setOutputRedirect(utils::trim(commandParts->back(), spaceSymbols));
    }

    return move(output);
}
