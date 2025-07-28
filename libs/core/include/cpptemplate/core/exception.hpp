#pragma once

#include <stdexcept>
#include "cpptemplate/core/logger.hpp" // For export macros

namespace cpptemplate::core {

/**
 * @brief Base exception class for the library
 * 
 * This class provides a base for all library-specific exceptions.
 */
class CPPTEMPLATE_CORE_API Exception : public std::runtime_error {
public:
    explicit Exception(const std::string& message) : std::runtime_error(message) {}
};

} // namespace cpptemplate::core