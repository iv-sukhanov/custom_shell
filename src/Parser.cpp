#include "Parser.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

Parser::Parser() = default;

std::vector<std::unique_ptr<Command>> Parser::parse(const std::string &line) {
  using namespace std;

  string spaceSymbols = " 	\n\r";
  auto res = find_first_of(begin(line), end(line), begin(spaceSymbols),
                           end(spaceSymbols));
  int pos = 0;
  while (res != end(line)) {
    // cout << "matched: #" << *res << "#\n";
    int pieceLength = distance(begin(line) + pos, res);
    string piece = line.substr(pos, pieceLength);
    pos = distance(begin(line), res) + 1;
    res = find_first_of(next(res), end(line), begin(spaceSymbols),
                        end(spaceSymbols));
    if (piece.empty()) continue;
    cout << "pl: " << pieceLength << "\npiece: #" << piece << "#\npos " << pos
         << "\nres " << res - begin(line) << '\n';
  }
  // TODO aslo add the last piece
}
