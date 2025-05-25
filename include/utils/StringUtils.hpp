/**
 * @file StringUtils.hpp
 * @brief Contains utility functions related to strings
 *
 * This file contains generic utility functions related to strings.
 *
 * @author Sukhanov Ivan
 * @date 25/5/2025
 * @version 1.0
 */
#pragma once

#include <algorithm>
#include <string>

/// @brief Namespace for utility functions.
namespace utils {

/// @brief Utility class for string operations.
class StringUtils {
   public:
    /**
     * @brief Splits a range into segments using a set of delimiter values and applies a binary function to
     * each segment.
     *
     * @tparam InIt1 Input iterator type for the main range.
     * @tparam InIt2 Input iterator type for the delimiter values.
     * @tparam OutIt Output iterator type.
     * @tparam F Callable type accepting (InIt1, InIt1) and returning a value to be stored in the output.
     * @param iter Iterator to the beginning of the input range.
     * @param iterEnd Iterator to the end of the input range.
     * @param splitValBeg Iterator to the beginning of the delimiter values.
     * @param splitValEnd Iterator to the end of the delimiter values.
     * @param outputIter Output iterator to store results.
     * @param binFunc Binary function applied to each segment.
     * @return InIt1 Iterator to the end of the processed range.
     */
    template <typename InIt1, typename InIt2, typename OutIt, typename F>
    static InIt1 split(InIt1 iter, InIt1 iterEnd, InIt2 splitValBeg, InIt2 splitValEnd, OutIt outputIter,
                       F binFunc);
    /**
     * @brief Trims unwanted symbols from both ends of the input string.
     *
     * @param str The input string to trim.
     * @param unwantedSynbols A string_view containing characters to be removed from both ends.
     * @return std::string The trimmed string.
     */
    static std::string trim(const std::string& str, std::string_view unwantedSynbols);
};

/**
 * @brief Splits a range into segments using a set of delimiter values and applies a binary function to
 * each segment.
 *
 * @tparam InIt1 Input iterator type for the main range.
 * @tparam InIt2 Input iterator type for the delimiter values.
 * @tparam OutIt Output iterator type.
 * @tparam F Callable type accepting (InIt1, InIt1) and returning a value to be stored in the output.
 * @param iter Iterator to the beginning of the input range.
 * @param iterEnd Iterator to the end of the input range.
 * @param splitValBeg Iterator to the beginning of the delimiter values.
 * @param splitValEnd Iterator to the end of the delimiter values.
 * @param outputIter Output iterator to store results.
 * @param binFunc Binary function applied to each segment.
 * @return InIt1 Iterator to the end of the processed range.
 */
template <typename InIt1, typename InIt2, typename OutIt, typename F>
InIt1 StringUtils::split(InIt1 iter, InIt1 iterEnd, InIt2 splitValBeg, InIt2 splitValEnd, OutIt outputIter,
                         F binFunc) {
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

}  // namespace utils
