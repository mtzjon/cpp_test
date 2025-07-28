#include "logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace cpp_template::core {

std::shared_ptr<Logger> Logger::create(std::string_view name) {
    // Create console sink with colors
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");

    // Create rotating file sink
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/app.log", 1024 * 1024 * 5, 3); // 5MB files, keep 3 files
    file_sink->set_level(spdlog::level::trace);
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [%s:%#] %v");

    // Create logger with both sinks
    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
    auto spdlog_logger = std::make_shared<spdlog::logger>(
        std::string{name}, sinks.begin(), sinks.end());
    
    spdlog_logger->set_level(spdlog::level::trace);
    spdlog_logger->flush_on(spdlog::level::error);

    // Register the logger
    spdlog::register_logger(spdlog_logger);

    return std::shared_ptr<Logger>(new Logger(spdlog_logger));
}

Logger::Logger(std::shared_ptr<spdlog::logger> logger) 
    : logger_(std::move(logger)) {
}

void Logger::set_level(spdlog::level::level_enum level) {
    logger_->set_level(level);
}

std::string Logger::name() const {
    return logger_->name();
}

} // namespace cpp_template::core