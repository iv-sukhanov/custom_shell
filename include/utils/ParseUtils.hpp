#pragma once

#include <iostream>
#include <iterator>
#include <regex>

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

}  // namespace utils
