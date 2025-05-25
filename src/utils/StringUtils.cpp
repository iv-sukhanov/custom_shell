/**
 * @file StringUtils.cpp
 * @brief Implements utility functions related to strings
 *
 * Contains generic utility functions related to strings.
 *
 * @author Sukhanov Ivan
 * @date 25/5/2025
 * @version 1.0
 */
#include "StringUtils.hpp"

#include <string>

/// @brief Namespace for utility functions.
namespace utils {

/**
 * @brief Trims unwanted symbols from both ends of the input string.
 *
 * @param str The input string to trim.
 * @param unwantedSynbols A string_view containing characters to be removed from both ends.
 * @return std::string The trimmed string.
 */
std::string trim(const std::string& str, std::string_view unwantedSynbols) {
    size_t first = str.find_first_not_of(unwantedSynbols);
    if (first == std::string::npos) {
        return "";
    }

    size_t last = str.find_last_not_of(unwantedSynbols);
    return str.substr(first, last - first + 1);
}

}  // namespace utils
