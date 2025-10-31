// SimpleLogger.hpp - 追加模式版本
#pragma once
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace SimpleLogger {
    // 🎯 新增：支持追加模式的初始化函数
    inline void Init(spdlog::level::level_enum log_level = spdlog::level::info, 
                     bool append_mode = true) {  // 默认追加模式
        static bool initialized = false;
        if (initialized) return;
        
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        
        // 🔑 关键：第三个参数控制是否追加
        // false = 追加模式，true = 覆盖模式（注意：参数含义是"截断"）
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
            "logs/demo.log", !append_mode);  // 注意取反！
        
        console_sink->set_level(log_level);
        file_sink->set_level(spdlog::level::trace);
        
        spdlog::sinks_init_list sink_list = {console_sink, file_sink};
        auto logger = std::make_shared<spdlog::logger>("guopeng", sink_list);
        
        logger->set_level(spdlog::level::trace);
        spdlog::set_default_logger(logger);
        
        initialized = true;
    }
    
    inline void SetLevel(spdlog::level::level_enum level) {
        spdlog::set_level(level);
    }
    
    inline void Cleanup() {
        spdlog::drop_all();
    }
}

// 使用宏简化调用
#define LOG_INIT_APPEND() SimpleLogger::Init(spdlog::level::info, true)   // 追加模式
#define LOG_INIT() SimpleLogger::Init(spdlog::level::info, false)  // 覆盖模式
// #define LOG_INIT(...) SimpleLogger::Init(__VA_ARGS__)// 覆盖模式
// #define LOG_SET_LEVEL(level) SimpleLogger::SetLevel(level)
#define LOG_CLEANUP() SimpleLogger::Cleanup()

#define LOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOG_WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define LOG_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)


// 从低到高的优先级顺序：
enum level_enum : int
{
    trace = 0,    // 最详细，优先级最低
    debug = 1,    // 调试信息
    info = 2,     // 一般信息
    warn = 3,     // 警告信息
    err = 4,      // 错误信息
    critical = 5, // 致命错误，优先级最高
    off = 6       // 关闭所有日志
};
