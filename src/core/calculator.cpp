#include "calculator.hpp"

#include <cmath>
#include <limits>

namespace cpp_template::core {

double Calculator::add(double a, double b) const noexcept {
    return a + b;
}

double Calculator::subtract(double a, double b) const noexcept {
    return a - b;
}

double Calculator::multiply(double a, double b) const noexcept {
    return a * b;
}

double Calculator::divide(double a, double b) const {
    if (std::abs(b) < std::numeric_limits<double>::epsilon()) {
        throw std::invalid_argument("Division by zero is not allowed");
    }
    return a / b;
}

double Calculator::power(double base, double exponent) const noexcept {
    return std::pow(base, exponent);
}

double Calculator::sqrt(double value) const {
    if (value < 0.0) {
        throw std::invalid_argument("Square root of negative number is not allowed");
    }
    return std::sqrt(value);
}

} // namespace cpp_template::core