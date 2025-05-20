#include "Parser.hpp"

#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "StringUtils.hpp"

Parser::Parser() = default;

std::vector<std::unique_ptr<Command>> Parser::parse(const std::string &line) {
    using namespace std;

    vector<string> pieces;
    const string spaceSymbols = " \n\t";
    auto retrieveStringFromIters([](auto it1, auto it2) { return string{it1, it2}; });
    utils::split(begin(line), end(line), begin(spaceSymbols), end(spaceSymbols), back_inserter(pieces),
                 retrieveStringFromIters);

    vector<unique_ptr<Command>> output;
    output.push_back(make_unique<Command>(pieces.front(), vector<string>{begin(pieces) + 1, end(pieces)}));

    return move(output);
}
