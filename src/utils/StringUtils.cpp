#include "StringUtils.hpp"

#include <string>
namespace utils {

std::string trim(const std::string& str, std::string_view unwantedSynbols) {
    size_t first = str.find_first_not_of(unwantedSynbols);
    if (first == std::string::npos) {
        return "";
    }

    size_t last = str.find_last_not_of(unwantedSynbols);
    return str.substr(first, last - first + 1);
}

}  // namespace utils
