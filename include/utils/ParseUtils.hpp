/**
 * @file ParseUtils.hpp
 * @brief Contains utility functions for parsing
 *
 * This file contains generic utility functions for parsing.
 *
 * @author Sukhanov Ivan
 * @date 25/5/2025
 * @version 1.0
 */
#pragma once

#include <regex>
#include <sstream>

/// @brief Namespace for utility functions.
namespace utils {

/**
 * @brief Checks if the input contains a number of matches for the given regex up to a maximum occurrence.
 *
 * @tparam InIt Input iterator type.
 * @param beg Iterator to the beginning of the input.
 * @param end Iterator to the end of the input.
 * @param regex Regular expression to search for.
 * @param maxOccurance Maximum allowed number of matches (default is 1).
 * @return true if at least one match is found and does not exceed maxOccurance, false otherwise.
 * @throws std::invalid_argument if the number of matches exceeds maxOccurance.
 */
template <typename InIt>
bool isPresent(InIt beg, InIt end, const std::regex& regex, size_t maxOccurance = 1) {
    std::sregex_iterator regexIterBeg = std::sregex_iterator(beg, end, regex);
    size_t occuranceNumb = std::distance(regexIterBeg, {});

    if (occuranceNumb > maxOccurance) {
        throw std::invalid_argument(
            "invalid number of occurances " +
            (regexIterBeg != std::sregex_iterator{} ? '"' + regexIterBeg->str() + "\"\n" : ""));
    }

    return occuranceNumb != 0;
}

/**
 * @brief Splits a range using a regex delimiter and applies a binary function to each segment.
 *
 * Iterates over the input range, splitting it at each match of the given regex. For each segment,
 * the provided binary function is called with iterators to the segment's start and end, and the result
 * is written to the output iterator. Returns true if the input ends with a delimiter match, false otherwise.
 *
 * @tparam InIt Input iterator type (must be compatible with std::sregex_iterator).
 * @tparam OutIt Output iterator type.
 * @tparam F Callable type accepting (InIt, InIt) and returning a value to be stored in the output.
 * @param iterBeg Iterator to the beginning of the input range.
 * @param iterEnd Iterator to the end of the input range.
 * @param outputIter Output iterator to store results.
 * @param regex Regular expression used as the delimiter.
 * @param binFunc Binary function applied to each segment.
 * @return true if the input ends with a delimiter match (no trailing segment), false otherwise.
 */
template <typename InIt, typename OutIt, typename F>
bool splitByRegex(InIt iterBeg, InIt iterEnd, OutIt outputIter, const std::regex& regex,
                  F binFunc) {  // rename
    auto tempIterator = iterBeg;
    std::sregex_iterator regexIterBeg = std::sregex_iterator(iterBeg, iterEnd, regex);
    std::sregex_iterator regexIterEnd = std::sregex_iterator{};

    bool endsWithPattern = true;

    while (regexIterBeg != regexIterEnd) {
        const std::smatch& currMatch = *regexIterBeg;
        auto sliceEnd = std::next(iterBeg, currMatch.position());

        *outputIter++ = binFunc(tempIterator, sliceEnd);

        tempIterator = std::next(sliceEnd, currMatch.length());
        regexIterBeg = std::next(regexIterBeg);
    }

    if (tempIterator != iterEnd) {
        *outputIter = binFunc(tempIterator, iterEnd);
        endsWithPattern = false;
    }

    return endsWithPattern;
}

/**
 * @brief Splits a string into arguments, handling quoted substrings and escaped characters.
 *
 * @tparam OutIt Output iterator type.
 * @param input Input string to split.
 * @param outputIter Output iterator to store arguments.
 */
template <typename OutIt>
void splitRespectingQuotes(const std::string& input, OutIt outputIter) {
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

        *outputIter++ = move(tocken);
        tocken.clear();
    }
}

/**
 * @brief Separates a string into two parts based on a single regex match (typically for redirection).
 *
 * @tparam InIt Input iterator type.
 * @param iter Iterator to the beginning of the input.
 * @param iterEnd Iterator to the end of the input.
 * @param regex Regular expression to match the separator.
 * @return std::pair<std::string, std::string> Pair of strings split at the regex match.
 * @throws std::invalid_argument if the regex does not match exactly once.
 */
template <typename InIt>
std::pair<std::string, std::string> cleaveByRegex(InIt iter, InIt iterEnd, const std::regex& regex) {
    std::sregex_iterator regexIterBeg = std::sregex_iterator(iter, iterEnd, regex);
    std::sregex_iterator regexIterEnd{};

    if (std::distance(regexIterBeg, regexIterEnd) != 1) {
        throw std::invalid_argument("invalid number of result tockens in redirecion splited line");
    }

    std::string first{iter, next(iter, regexIterBeg->position())};
    std::string second{next(iter, regexIterBeg->position() + regexIterBeg->length()), iterEnd};

    return {move(first), move(second)};
}

}  // namespace utils
