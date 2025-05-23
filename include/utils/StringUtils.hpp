#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <regex>

namespace utils {

template <typename InIt1, typename InIt2, typename OutIt, typename F>
InIt1 split(InIt1 iter, InIt1 iterEnd, InIt2 splitValBeg, InIt2 splitValEnd, OutIt outputIter, F binFunc) {
    while (iter != iterEnd) {
        auto sliceEnd(std::find_first_of(iter, iterEnd, splitValBeg, splitValEnd));

        if (std::distance(iter, sliceEnd) > 0) {
            *outputIter++ = binFunc(iter, sliceEnd);
        }

        if (sliceEnd == iterEnd) {
            return iterEnd;
        }

        iter = next(sliceEnd);
    }

    return iterEnd;
}

template <typename InIt, typename SplitSymb, typename OutIt, typename F>
InIt split(InIt iter, InIt iterEnd, SplitSymb splitSymb, OutIt outputIter, F binFunc) {
    while (iter != iterEnd) {
        auto sliceEnd(std::find(iter, iterEnd, splitSymb));

        if (std::distance(iter, sliceEnd) > 0) {
            *outputIter++ = binFunc(iter, sliceEnd);
        }

        if (sliceEnd == iterEnd) {
            return iterEnd;
        }

        iter = next(sliceEnd);
    }

    return iterEnd;
}

std::string trim(const std::string& str, std::string_view unwantedSynbols);

}  // namespace utils
