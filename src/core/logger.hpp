#pragma once

#include <memory>
#include <string>
#include <string_view>

#include <spdlog/spdlog.h>

namespace cpp_template::core {

/**
 * @brief A logger wrapper around spdlog providing a clean interface
 * 
 * This class wraps spdlog functionality and provides a factory method
 * for creating loggers with consistent configuration.
 */
class Logger {
public:
    /**
     * @brief Create a logger instance
     * @param name Logger name
     * @return Shared pointer to logger instance
     */
    [[nodiscard]] static std::shared_ptr<Logger> create(std::string_view name);

    /**
     * @brief Destructor
     */
    ~Logger() = default;

    // Make the class non-copyable but movable
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = default;
    Logger& operator=(Logger&&) = default;

    /**
     * @brief Log trace message
     * @tparam Args Argument types
     * @param fmt Format string
     * @param args Arguments
     */
    template<typename... Args>
    void trace(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        logger_->trace(fmt, std::forward<Args>(args)...);
    }

    /**
     * @brief Log debug message
     * @tparam Args Argument types
     * @param fmt Format string
     * @param args Arguments
     */
    template<typename... Args>
    void debug(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        logger_->debug(fmt, std::forward<Args>(args)...);
    }

    /**
     * @brief Log info message
     * @tparam Args Argument types
     * @param fmt Format string
     * @param args Arguments
     */
    template<typename... Args>
    void info(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        logger_->info(fmt, std::forward<Args>(args)...);
    }

    /**
     * @brief Log warning message
     * @tparam Args Argument types
     * @param fmt Format string
     * @param args Arguments
     */
    template<typename... Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        logger_->warn(fmt, std::forward<Args>(args)...);
    }

    /**
     * @brief Log error message
     * @tparam Args Argument types
     * @param fmt Format string
     * @param args Arguments
     */
    template<typename... Args>
    void error(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        logger_->error(fmt, std::forward<Args>(args)...);
    }

    /**
     * @brief Log critical message
     * @tparam Args Argument types
     * @param fmt Format string
     * @param args Arguments
     */
    template<typename... Args>
    void critical(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        logger_->critical(fmt, std::forward<Args>(args)...);
    }

    /**
     * @brief Set log level
     * @param level Log level
     */
    void set_level(spdlog::level::level_enum level);

    /**
     * @brief Get logger name
     * @return Logger name
     */
    [[nodiscard]] std::string name() const;

private:
    /**
     * @brief Private constructor - use factory method
     * @param logger spdlog logger instance
     */
    explicit Logger(std::shared_ptr<spdlog::logger> logger);

    std::shared_ptr<spdlog::logger> logger_;
};

} // namespace cpp_template::core