// SimpleLogger.hpp
#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace SimpleLogger {
    inline void Init() {
        static bool initialized = false;
        if (initialized) return;
        
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("demo.log", true);
        
        spdlog::sinks_init_list sink_list = {console_sink, file_sink};
        auto logger = std::make_shared<spdlog::logger>("guopeng", sink_list);
        
        spdlog::set_default_logger(logger);
        spdlog::set_level(spdlog::level::debug);
        
        initialized = true;
    }
}

// 使用宏简化调用
#define INIT_LOGGER() SimpleLogger::Init()
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
