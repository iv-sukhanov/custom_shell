#include "Parser.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

Parser::Parser() = default;

template <typename InIt_1, typename InIt_2, typename OutIt, typename F>
InIt_1 split(InIt_1 it, InIt_1 it_end, InIt_2 interval_beg, InIt_2 interval_end,
             OutIt out_it, F binfunc) {
  while (it != it_end) {
    auto slice_end(std::find_first_of(it, it_end, interval_beg, interval_end));
    if (std::distance(it, slice_end) > 1) {
      *out_it++ = binfunc(it, slice_end);
    }

    if (slice_end == it_end) {
      return slice_end;
    }

    it = next(slice_end);
  }

  return it_end;
}

std::vector<std::unique_ptr<Command>> Parser::parse(const std::string &line) {
  using namespace std;

  string spaceSymbols = " 	\n\r";
  // auto res = find_first_of(begin(line), end(line), begin(spaceSymbols),
  //                          end(spaceSymbols));
  // int pos = 0;
  vector<string> pieces;  // consinder using llist
  // while (res != end(line)) {
  //   // cout << "matched: #" << *res << "#\n";
  //   int resDistance = distance(begin(line), res);
  //
  //   string piece = line.substr(pos, resDistance - pos);
  //   if (!piece.empty()) {
  //     pieces.push_back(piece);
  //   }
  //
  //   pos = resDistance + 1;
  //   res = find_first_of(next(res), end(line), begin(spaceSymbols),
  //                       end(spaceSymbols));
  //
  //   // debug
  //   if (piece.empty()) continue;
  //   cout << "piece: #" << piece << "#\npos " << pos << "\nres "
  //        << res - begin(line) << '\n';
  // }
  //
  // if (string lastPiece = line.substr(pos, line.size() - pos);
  //     !lastPiece.empty()) {
  //   pieces.push_back(lastPiece);
  // }

  // TODO aslo add the last piece
  split(begin(line), end(line), begin(spaceSymbols), end(spaceSymbols),
        back_inserter(pieces), [](auto it_b, auto it_e) {
          return string{it_b, it_e};
        });
  copy(begin(pieces), end(pieces),
       ostream_iterator<string>{cout, ", "});  // debug
  unique_ptr<Command> parsedCommand = make_unique<Command>(
      pieces.front(), vector<string>{begin(pieces) + 1, end(pieces)});
  // vector<unique_ptr<Command>> output{move(parsedCommand)};
  vector<unique_ptr<Command>> output{};
  output.push_back(move(parsedCommand));
  return output;
}
