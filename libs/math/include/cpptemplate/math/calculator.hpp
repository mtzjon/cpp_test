#pragma once

#include <stdexcept>

// Export macros for dynamic libraries
#ifdef CPPTEMPLATE_MATH_STATIC
    #define CPPTEMPLATE_MATH_API
#else
    #ifdef CPPTEMPLATE_MATH_BUILDING
        #if defined(_WIN32) || defined(_WIN64)
            #define CPPTEMPLATE_MATH_API __declspec(dllexport)
        #else
            #define CPPTEMPLATE_MATH_API __attribute__((visibility("default")))
        #endif
    #else
        #if defined(_WIN32) || defined(_WIN64)
            #define CPPTEMPLATE_MATH_API __declspec(dllimport)
        #else
            #define CPPTEMPLATE_MATH_API
        #endif
    #endif
#endif

namespace cpptemplate::math {

/**
 * @brief A calculator class demonstrating basic arithmetic operations
 * 
 * This class provides basic mathematical operations with proper error handling
 * and follows modern C++ best practices.
 */
class CPPTEMPLATE_MATH_API Calculator {
public:
    /**
     * @brief Default constructor
     */
    Calculator() = default;

    /**
     * @brief Default destructor
     */
    ~Calculator() = default;

    // Make the class non-copyable and non-movable for this example
    Calculator(const Calculator&) = delete;
    Calculator& operator=(const Calculator&) = delete;
    Calculator(Calculator&&) = delete;
    Calculator& operator=(Calculator&&) = delete;

    /**
     * @brief Add two numbers
     * @param a First operand
     * @param b Second operand
     * @return Sum of a and b
     */
    [[nodiscard]] double add(double a, double b) const noexcept;

    /**
     * @brief Subtract two numbers
     * @param a First operand
     * @param b Second operand
     * @return Difference of a and b (a - b)
     */
    [[nodiscard]] double subtract(double a, double b) const noexcept;

    /**
     * @brief Multiply two numbers
     * @param a First operand
     * @param b Second operand
     * @return Product of a and b
     */
    [[nodiscard]] double multiply(double a, double b) const noexcept;

    /**
     * @brief Divide two numbers
     * @param a Dividend
     * @param b Divisor
     * @return Quotient of a and b (a / b)
     * @throws std::invalid_argument if b is zero
     */
    [[nodiscard]] double divide(double a, double b) const;

    /**
     * @brief Calculate power of a number
     * @param base Base number
     * @param exponent Exponent
     * @return base raised to the power of exponent
     */
    [[nodiscard]] double power(double base, double exponent) const noexcept;

    /**
     * @brief Calculate square root of a number
     * @param value Input value
     * @return Square root of the input value
     * @throws std::invalid_argument if value is negative
     */
    [[nodiscard]] double sqrt(double value) const;
};

} // namespace cpptemplate::math