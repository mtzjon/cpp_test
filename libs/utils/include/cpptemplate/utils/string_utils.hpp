#pragma once

#include <string>
#include <string_view>
#include <vector>

// Export macros for dynamic libraries
#ifdef CPPTEMPLATE_UTILS_STATIC
    #define CPPTEMPLATE_UTILS_API
#else
    #ifdef CPPTEMPLATE_UTILS_BUILDING
        #if defined(_WIN32) || defined(_WIN64)
            #define CPPTEMPLATE_UTILS_API __declspec(dllexport)
        #else
            #define CPPTEMPLATE_UTILS_API __attribute__((visibility("default")))
        #endif
    #else
        #if defined(_WIN32) || defined(_WIN64)
            #define CPPTEMPLATE_UTILS_API __declspec(dllimport)
        #else
            #define CPPTEMPLATE_UTILS_API
        #endif
    #endif
#endif

namespace cpptemplate::utils {

/**
 * @brief Trim whitespace from both ends of a string
 * @param str Input string
 * @return Trimmed string
 */
[[nodiscard]] CPPTEMPLATE_UTILS_API std::string trim(std::string_view str);

/**
 * @brief Trim whitespace from the left end of a string
 * @param str Input string
 * @return Left-trimmed string
 */
[[nodiscard]] CPPTEMPLATE_UTILS_API std::string ltrim(std::string_view str);

/**
 * @brief Trim whitespace from the right end of a string
 * @param str Input string
 * @return Right-trimmed string
 */
[[nodiscard]] CPPTEMPLATE_UTILS_API std::string rtrim(std::string_view str);

/**
 * @brief Convert string to uppercase
 * @param str Input string
 * @return Uppercase string
 */
[[nodiscard]] CPPTEMPLATE_UTILS_API std::string to_upper(std::string_view str);

/**
 * @brief Convert string to lowercase
 * @param str Input string
 * @return Lowercase string
 */
[[nodiscard]] CPPTEMPLATE_UTILS_API std::string to_lower(std::string_view str);

/**
 * @brief Split string by delimiter
 * @param str Input string
 * @param delimiter Delimiter character
 * @return Vector of string parts
 */
[[nodiscard]] CPPTEMPLATE_UTILS_API std::vector<std::string> split(std::string_view str, char delimiter);

/**
 * @brief Join strings with delimiter
 * @param strings Vector of strings to join
 * @param delimiter Delimiter string
 * @return Joined string
 */
[[nodiscard]] CPPTEMPLATE_UTILS_API std::string join(const std::vector<std::string>& strings, 
                                                     std::string_view delimiter);

/**
 * @brief Check if string starts with prefix
 * @param str Input string
 * @param prefix Prefix to check
 * @return True if string starts with prefix
 */
[[nodiscard]] CPPTEMPLATE_UTILS_API bool starts_with(std::string_view str, std::string_view prefix);

/**
 * @brief Check if string ends with suffix
 * @param str Input string
 * @param suffix Suffix to check
 * @return True if string ends with suffix
 */
[[nodiscard]] CPPTEMPLATE_UTILS_API bool ends_with(std::string_view str, std::string_view suffix);

/**
 * @brief Replace all occurrences of a substring
 * @param str Input string
 * @param from Substring to replace
 * @param to Replacement string
 * @return String with replacements
 */
[[nodiscard]] CPPTEMPLATE_UTILS_API std::string replace_all(std::string str, 
                                                            std::string_view from, 
                                                            std::string_view to);

} // namespace cpptemplate::utils