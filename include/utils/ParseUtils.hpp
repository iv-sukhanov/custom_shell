#pragma once

#include <iostream>
#include <iterator>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

#include "StringUtils.hpp"

namespace utils {

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
        std::cout << "temp " << std::distance(iterBeg, tempIterator);
    }

    if (tempIterator != iterEnd) {
        *outputIter = binFunc(tempIterator, iterEnd);
        isLastParallel = false;
    }

    return isLastParallel;
}

template <typename InIt, typename F>
std::pair<std::string, std::string> separateRedirection(InIt iter, InIt iterEnd, F binFunc) {
    std::regex redirectionSymbol("\\s+(>)\\s+");  // mb add an append option
    std::sregex_iterator regexIterBeg = std::sregex_iterator(iter, iterEnd, redirectionSymbol);
    std::sregex_iterator regexIterEnd{};

    if (std::distance(regexIterBeg, regexIterEnd) != 1) {
        throw std::runtime_error("invalid number of result tockens in redirecion splited line");
    }

    std::cout << (*regexIterBeg)[1] << std::endl;  // debug

    std::string first{iter, next(iter, regexIterBeg->position())};
    std::string second{next(iter, regexIterBeg->position() + regexIterBeg->length()), iterEnd};

    return {move(first), move(second)};
}

}  // namespace utils
