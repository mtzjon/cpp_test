#include "cpptemplate/utils/string_utils.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace cpptemplate::utils {

std::string trim(std::string_view str) {
    return ltrim(rtrim(str));
}

std::string ltrim(std::string_view str) {
    auto start = std::find_if_not(str.begin(), str.end(), 
                                  [](unsigned char ch) { return std::isspace(ch); });
    return std::string(start, str.end());
}

std::string rtrim(std::string_view str) {
    auto end = std::find_if_not(str.rbegin(), str.rend(),
                                [](unsigned char ch) { return std::isspace(ch); }).base();
    return std::string(str.begin(), end);
}

std::string to_upper(std::string_view str) {
    std::string result;
    result.reserve(str.size());
    std::transform(str.begin(), str.end(), std::back_inserter(result),
                   [](unsigned char ch) { return std::toupper(ch); });
    return result;
}

std::string to_lower(std::string_view str) {
    std::string result;
    result.reserve(str.size());
    std::transform(str.begin(), str.end(), std::back_inserter(result),
                   [](unsigned char ch) { return std::tolower(ch); });
    return result;
}

std::vector<std::string> split(std::string_view str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    
    for (char ch : str) {
        if (ch == delimiter) {
            if (!token.empty()) {
                tokens.push_back(std::move(token));
                token.clear();
            }
        } else {
            token += ch;
        }
    }
    
    if (!token.empty()) {
        tokens.push_back(std::move(token));
    }
    
    return tokens;
}

std::string join(const std::vector<std::string>& strings, std::string_view delimiter) {
    if (strings.empty()) {
        return {};
    }
    
    std::ostringstream oss;
    auto it = strings.begin();
    oss << *it;
    ++it;
    
    for (; it != strings.end(); ++it) {
        oss << delimiter << *it;
    }
    
    return oss.str();
}

bool starts_with(std::string_view str, std::string_view prefix) {
    return str.size() >= prefix.size() && 
           str.substr(0, prefix.size()) == prefix;
}

bool ends_with(std::string_view str, std::string_view suffix) {
    return str.size() >= suffix.size() && 
           str.substr(str.size() - suffix.size()) == suffix;
}

std::string replace_all(std::string str, std::string_view from, std::string_view to) {
    if (from.empty()) {
        return str;
    }
    
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
    
    return str;
}

} // namespace cpptemplate::utils