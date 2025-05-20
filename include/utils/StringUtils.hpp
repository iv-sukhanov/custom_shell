#pragma once

#include <algorithm>

namespace utils {

template <typename InIt1, typename InIt2, typename OutIt, typename F>
InIt1 split(InIt1 iter, InIt1 iterEnd, InIt2 splitValBeg, InIt2 splitValEnd, OutIt outputIter, F binFunc) {
    while (iter != iterEnd) {
        auto sliceEnd(std::find_first_of(iter, iterEnd, splitValBeg, splitValEnd));

        if (std::distance(iter, sliceEnd) > 1) {
            *outputIter++ = binFunc(iter, sliceEnd);
        }

        if (sliceEnd == iterEnd) {
            return iterEnd;
        }

        iter = next(sliceEnd);
    }

    return iterEnd;
}

}  // namespace utils
