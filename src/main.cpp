#include <iostream>
#include <memory>

#include "core/calculator.hpp"
#include "core/logger.hpp"
#include "utils/string_utils.hpp"

int main() {
    try {
        // Initialize logger
        auto logger = cpp_template::core::Logger::create("CppTemplate");
        logger->info("Application started");

        // Demonstrate calculator functionality
        cpp_template::core::Calculator calc;
        
        const double a = 10.5;
        const double b = 3.2;
        
        logger->info("Performing calculations with a={}, b={}", a, b);
        
        logger->info("Addition: {} + {} = {}", a, b, calc.add(a, b));
        logger->info("Subtraction: {} - {} = {}", a, b, calc.subtract(a, b));
        logger->info("Multiplication: {} * {} = {}", a, b, calc.multiply(a, b));
        
        if (b != 0.0) {
            logger->info("Division: {} / {} = {}", a, b, calc.divide(a, b));
        }

        // Demonstrate string utilities
        const std::string test_string = "  Hello, World!  ";
        logger->info("Original string: '{}'", test_string);
        logger->info("Trimmed string: '{}'", cpp_template::utils::trim(test_string));
        logger->info("Uppercase string: '{}'", cpp_template::utils::to_upper(test_string));
        logger->info("Lowercase string: '{}'", cpp_template::utils::to_lower(test_string));

        // Test string splitting
        const std::string csv = "apple,banana,cherry,date";
        auto fruits = cpp_template::utils::split(csv, ',');
        logger->info("Split '{}' into {} parts:", csv, fruits.size());
        for (size_t i = 0; i < fruits.size(); ++i) {
            logger->info("  [{}]: '{}'", i, fruits[i]);
        }

        logger->info("Application completed successfully");
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}