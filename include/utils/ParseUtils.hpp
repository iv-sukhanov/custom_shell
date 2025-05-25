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

/// @brief Utility class for parsing
class ParseUtils {
   public:
    /**
     * @brief Checks if a regex pattern is present in the given input range and does not exceed the maximum
     * allowed occurrences.
     *
     * @tparam InIt Input iterator type.
     * @param beg Iterator to the beginning of the input range.
     * @param end Iterator to the end of the input range.
     * @param regex The regular expression to search for.
     * @param maxOccurance The maximum allowed number of occurrences.
     * @return true if the pattern is present at least once and does not exceed maxOccurance, false otherwise.
     * @throws std::invalid_argument if the number of occurrences exceeds maxOccurance.
     */
    template <typename InIt>
    static bool isPresent(InIt beg, InIt end, const std::regex& regex, size_t maxOccurance = 1);

    /**
     * @brief Splits an input range by a regex pattern, applies a binary function to each split, and writes
     * the results to an output iterator.
     *
     * @tparam InIt Input iterator type.
     * @tparam OutIt Output iterator type.
     * @tparam F Binary function type to apply to each split.
     * @param iterBeg Iterator to the beginning of the input range.
     * @param iterEnd Iterator to the end of the input range.
     * @param outputIter Output iterator to write results.
     * @param regex The regular expression to split by.
     * @param binFunc Binary function to apply to each split segment.
     * @return true if the input ends with the pattern, false otherwise.
     */
    template <typename InIt, typename OutIt, typename F>
    static bool splitByRegex(InIt iterBeg, InIt iterEnd, OutIt outputIter, const std::regex& regex,
                             F binFunc);

    /**
     * @brief Splits a string into tokens, respecting quoted substrings (single or double quotes).
     *
     * @tparam OutIt Output iterator type.
     * @param input The input string to split.
     * @param outputIter Output iterator to write tokens.
     */
    template <typename OutIt>
    static void splitRespectingQuotes(const std::string& input, OutIt outputIter);

    /**
     * @brief Splits an input range into two substrings at the first match of a regex pattern.
     *
     * @tparam InIt Input iterator type.
     * @param iter Iterator to the beginning of the input range.
     * @param iterEnd Iterator to the end of the input range.
     * @param regex The regular expression to split by.
     * @return std::pair<std::string, std::string> Pair of substrings before and after the regex match.
     * @throws std::invalid_argument if the regex does not match exactly once.
     */
    template <typename InIt>
    static std::pair<std::string, std::string> cleaveByRegex(InIt iter, InIt iterEnd,
                                                             const std::regex& regex);
};

/**
 * @brief Checks if a regex pattern is present in the given input range and does not exceed the maximum
 * allowed occurrences.
 *
 * @tparam InIt Input iterator type.
 * @param beg Iterator to the beginning of the input range.
 * @param end Iterator to the end of the input range.
 * @param regex The regular expression to search for.
 * @param maxOccurance The maximum allowed number of occurrences.
 * @return true if the pattern is present at least once and does not exceed maxOccurance, false otherwise.
 * @throws std::invalid_argument if the number of occurrences exceeds maxOccurance.
 */
template <typename InIt>
bool ParseUtils::isPresent(InIt beg, InIt end, const std::regex& regex, size_t maxOccurance) {
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
 * @brief Splits an input range by a regex pattern, applies a binary function to each split, and writes the
 * results to an output iterator.
 *
 * @tparam InIt Input iterator type.
 * @tparam OutIt Output iterator type.
 * @tparam F Binary function type to apply to each split.
 * @param iterBeg Iterator to the beginning of the input range.
 * @param iterEnd Iterator to the end of the input range.
 * @param outputIter Output iterator to write results.
 * @param regex The regular expression to split by.
 * @param binFunc Binary function to apply to each split segment.
 * @return true if the input ends with the pattern, false otherwise.
 */
template <typename InIt, typename OutIt, typename F>
bool ParseUtils::splitByRegex(InIt iterBeg, InIt iterEnd, OutIt outputIter, const std::regex& regex,
                              F binFunc) {
    auto tempIterator = iterBeg;

    std::sregex_iterator regexIterBeg = std::sregex_iterator(iterBeg, iterEnd, regex);
    std::sregex_iterator regexIterEnd = std::sregex_iterator{};

    bool endsWithPattern = true;

    while (regexIterBeg != regexIterEnd) {
        const std::smatch& currMatch = *regexIterBeg;
        auto sliceEnd = std::next(iterBeg, currMatch.position());

        if (std::distance(tempIterator, sliceEnd) > 0) {
            *outputIter++ = binFunc(tempIterator, sliceEnd);
        }

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
 * @brief Splits a string into tokens, respecting quoted substrings (single or double quotes).
 *
 * @tparam OutIt Output iterator type.
 * @param input The input string to split.
 * @param outputIter Output iterator to write tokens.
 */
template <typename OutIt>
void ParseUtils::splitRespectingQuotes(const std::string& input, OutIt outputIter) {
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
 * @brief Splits an input range into two substrings at the first match of a regex pattern.
 *
 * @tparam InIt Input iterator type.
 * @param iter Iterator to the beginning of the input range.
 * @param iterEnd Iterator to the end of the input range.
 * @param regex The regular expression to split by.
 * @return std::pair<std::string, std::string> Pair of substrings before and after the regex match.
 * @throws std::invalid_argument if the regex does not match exactly once.
 */
template <typename InIt>
std::pair<std::string, std::string> ParseUtils::cleaveByRegex(InIt iter, InIt iterEnd,
                                                              const std::regex& regex) {
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
