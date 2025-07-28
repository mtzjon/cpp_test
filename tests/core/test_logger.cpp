#include <gtest/gtest.h>
#include <memory>
#include <filesystem>

#include "cpptemplate/core/logger.hpp"

using namespace cpptemplate::core;

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create logs directory if it doesn't exist
        std::filesystem::create_directories("logs");
        logger = Logger::create("TestLogger");
    }

    void TearDown() override {
        logger.reset();
    }

    std::shared_ptr<Logger> logger;
};

TEST_F(LoggerTest, CreateLogger) {
    ASSERT_NE(logger, nullptr);
    EXPECT_EQ(logger->name(), "TestLogger");
}

TEST_F(LoggerTest, CreateMultipleLoggers) {
    auto logger1 = Logger::create("Logger1");
    auto logger2 = Logger::create("Logger2");
    
    ASSERT_NE(logger1, nullptr);
    ASSERT_NE(logger2, nullptr);
    EXPECT_EQ(logger1->name(), "Logger1");
    EXPECT_EQ(logger2->name(), "Logger2");
}

TEST_F(LoggerTest, SetLogLevel) {
    // This test mainly ensures the method doesn't crash
    logger->set_level(spdlog::level::debug);
    logger->set_level(spdlog::level::info);
    logger->set_level(spdlog::level::warn);
    logger->set_level(spdlog::level::err);
    logger->set_level(spdlog::level::critical);
}

TEST_F(LoggerTest, LogMethods) {
    // These tests mainly ensure the logging methods don't crash
    logger->trace("Trace message: {}", 42);
    logger->debug("Debug message: {}", 3.14);
    logger->info("Info message: {}", "hello");
    logger->warn("Warning message: {}", true);
    logger->error("Error message: {}", 'x');
    logger->critical("Critical message: {}", std::string("test"));
}

TEST_F(LoggerTest, LogWithMultipleArguments) {
    logger->info("Multiple args: {} {} {} {}", 1, 2.5, "three", true);
    logger->warn("Format string with {} and {}", "string", 123);
}

TEST_F(LoggerTest, LogEmptyMessage) {
    logger->info("");
    logger->debug("");
    logger->error("");
}

TEST_F(LoggerTest, MoveSemantics) {
    auto original_name = logger->name();
    auto moved_logger = std::move(logger);
    
    ASSERT_NE(moved_logger, nullptr);
    EXPECT_EQ(moved_logger->name(), original_name);
    
    // Original logger should be in a valid but unspecified state
    // We don't test its state as it's moved-from
}