#include <iostream>

#include "cpptemplate/core/logger.hpp"
#include "cpptemplate/math/calculator.hpp"

int main() {
    // Create logger
    auto logger = cpptemplate::core::Logger::create("BasicExample");
    logger->info("Starting basic calculator example");

    // Create calculator
    cpptemplate::math::Calculator calc;

    // Perform some calculations
    double a = 10.0;
    double b = 3.0;

    logger->info("Computing {} + {} = {}", a, b, calc.add(a, b));
    logger->info("Computing {} - {} = {}", a, b, calc.subtract(a, b));
    logger->info("Computing {} * {} = {}", a, b, calc.multiply(a, b));
    logger->info("Computing {} / {} = {}", a, b, calc.divide(a, b));

    logger->info("Example completed successfully!");
    return 0;
}