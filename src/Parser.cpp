#include "Parser.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

Parser::Parser() = default;

std::vector<std::unique_ptr<Command>> Parser::parse(const std::string &line) {
  using namespace std;

  string spaceSymbols = " 	\n\r";
  auto res = find_first_of(begin(line), end(line), begin(spaceSymbols),
                           end(spaceSymbols));
  int pos = 0;
  vector<string> pieces;  // consinder using llist
  while (res != end(line)) {
    // cout << "matched: #" << *res << "#\n";
    int resDistance = distance(begin(line), res);

    string piece = line.substr(pos, resDistance - pos);
    if (!piece.empty()) {
      pieces.push_back(piece);
    }

    pos = resDistance + 1;
    res = find_first_of(next(res), end(line), begin(spaceSymbols),
                        end(spaceSymbols));

    // debug
    if (piece.empty()) continue;
    cout << "piece: #" << piece << "#\npos " << pos << "\nres "
         << res - begin(line) << '\n';
  }

  if (string lastPiece = line.substr(pos, line.size() - pos);
      !lastPiece.empty()) {
    pieces.push_back(lastPiece);
  }

  copy(begin(pieces), end(pieces),
       ostream_iterator<string>{cout, ", "});  // debug
  // TODO aslo add the last piece
  unique_ptr<Command> parsedCommand = make_unique<Command>(
      pieces.front(), vector<string>{begin(pieces) + 1, end(pieces)});
  // vector<unique_ptr<Command>> output{move(parsedCommand)};
  vector<unique_ptr<Command>> output{};
  output.push_back(move(parsedCommand));
  return output;
}
