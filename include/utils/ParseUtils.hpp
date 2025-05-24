#pragma once

#include <cctype>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "StringUtils.hpp"

namespace utils {

template <typename InIt>
bool isRedirected(InIt beg, InIt end, const std::regex& regex) {
    auto redirectIter = std::sregex_iterator(beg, end, regex);
    switch (size_t occuranceNumb = std::distance(redirectIter, {}); occuranceNumb) {
        case 0:
            return false;
            break;
        case 1:
            return true;
            break;
        default:
            throw std::invalid_argument("invalid number of redirections");
            break;
    }
}

template <typename InIt, typename OutIt, typename F>
bool splitJobs(InIt iterBeg, InIt iterEnd, OutIt outputIter, const std::regex& regex, F binFunc) {  // rename
    auto tempIterator = iterBeg;
    std::sregex_iterator regexIterBeg = std::sregex_iterator(iterBeg, iterEnd, regex);
    std::sregex_iterator regexIterEnd = std::sregex_iterator{};

    bool isLastParallel = true;

    while (regexIterBeg != regexIterEnd) {
        const std::smatch& currMatch = *regexIterBeg;
        auto sliceEnd = std::next(iterBeg, currMatch.position());

        *outputIter++ = binFunc(tempIterator, sliceEnd);

        tempIterator = std::next(sliceEnd, currMatch.length());
        regexIterBeg = std::next(regexIterBeg);
    }

    if (tempIterator != iterEnd) {
        *outputIter = binFunc(tempIterator, iterEnd);
        isLastParallel = false;
    }

    return isLastParallel;
}

template <typename OutIt>
void splitArgs(const std::string& input, OutIt outputIter) {
    std::istringstream iss{input};
    std::string tocken;

    char quote;
    char currChar;
    bool quoted;

    while (iss >> std::ws) {
        if (iss.peek() == EOF) {
            break;
        }

        if ((quoted = iss.peek() == '"' || iss.peek() == '\'')) {
            iss.get(quote);
        }

        while (iss.get(currChar)) {
            if (currChar == '\\' && iss.get(currChar)) {
                tocken += currChar;
            } else if (quoted && currChar == quote || !quoted && std::isspace(currChar)) {
                break;
            } else {
                tocken += currChar;
            }
        }

        // std::cout << "adding this tocken: !" << tocken << "!\n";
        *outputIter++ = move(tocken);
        tocken.clear();
    }
}

template <typename InIt>
std::pair<std::string, std::string> separateRedirection(InIt iter, InIt iterEnd, const std::regex& regex) {
    std::sregex_iterator regexIterBeg = std::sregex_iterator(iter, iterEnd, regex);
    std::sregex_iterator regexIterEnd{};

    if (std::distance(regexIterBeg, regexIterEnd) != 1) {
        throw std::invalid_argument("invalid number of result tockens in redirecion splited line");
    }

    // std::cout << (*regexIterBeg)[1] << std::endl;  // debug

    std::string first{iter, next(iter, regexIterBeg->position())};
    std::string second{next(iter, regexIterBeg->position() + regexIterBeg->length()), iterEnd};

    return {move(first), move(second)};
}

}  // namespace utils
