#include <iostream>
#include <memory>

#include "cpptemplate/core/logger.hpp"
#include "cpptemplate/math/calculator.hpp"
#include "cpptemplate/utils/string_utils.hpp"

#ifndef APP_VERSION
#define APP_VERSION "unknown"
#endif

#ifndef APP_NAME
#define APP_NAME "CppTemplate Main"
#endif

int main() {
    try {
        // Initialize logger
        auto logger = cpptemplate::core::Logger::create("MainApp");
        logger->info("{} v{} starting...", APP_NAME, APP_VERSION);

        // Demonstrate calculator functionality
        cpptemplate::math::Calculator calc;
        
        const double a = 10.5;
        const double b = 3.2;
        
        logger->info("Performing calculations with a={}, b={}", a, b);
        
        logger->info("Addition: {} + {} = {}", a, b, calc.add(a, b));
        logger->info("Subtraction: {} - {} = {}", a, b, calc.subtract(a, b));
        logger->info("Multiplication: {} * {} = {}", a, b, calc.multiply(a, b));
        
        if (b != 0.0) {
            logger->info("Division: {} / {} = {}", a, b, calc.divide(a, b));
        }

        logger->info("Power: {}^{} = {}", a, 2.0, calc.power(a, 2.0));
        logger->info("Square root of {} = {}", a, calc.sqrt(a));

        // Demonstrate string utilities
        const std::string test_string = "  Hello, World!  ";
        logger->info("Original string: '{}'", test_string);
        logger->info("Trimmed string: '{}'", cpptemplate::utils::trim(test_string));
        logger->info("Uppercase string: '{}'", cpptemplate::utils::to_upper(test_string));
        logger->info("Lowercase string: '{}'", cpptemplate::utils::to_lower(test_string));

        // Test string splitting
        const std::string csv = "apple,banana,cherry,date";
        auto fruits = cpptemplate::utils::split(csv, ',');
        logger->info("Split '{}' into {} parts:", csv, fruits.size());
        for (size_t i = 0; i < fruits.size(); ++i) {
            logger->info("  [{}]: '{}'", i, fruits[i]);
        }

        // Test string joining
        std::vector<std::string> words = {"Hello", "beautiful", "world"};
        auto joined = cpptemplate::utils::join(words, " ");
        logger->info("Joined words: '{}'", joined);

        logger->info("Application completed successfully");
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}