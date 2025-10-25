#include "log.hpp"
#include <ctime>
#include <iomanip>

ModernLogger::ModernLogger(const std::string& filename) : logFile(filename) {
    logStream.open(logFile, std::ios::app);  // 追加模式
    if (logStream.is_open()) {
        std::cout << "📝 日志系统启动：" << logFile << std::endl;
    } else {
        std::cerr << "❌ 无法创建日志文件：" << logFile << std::endl;
    }
}

ModernLogger& ModernLogger::getInstance() {
    static ModernLogger instance;  // 线程安全的单例
    return instance;
}

void ModernLogger::info(const std::string& message) {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    
    std::string logMsg = "[INFO] " + message;
    
    // 同时输出到控制台和文件
    std::cout << logMsg << std::endl;
    
    if (logStream.is_open()) {
        logStream << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") 
                  << " " << logMsg << std::endl;
        logStream.flush();  // 确保立即写入
    }
}

void ModernLogger::warning(const std::string& message) {
    std::string logMsg = "[WARNING] " + message;
    std::cout << "⚠️ " << logMsg << std::endl;
    
    if (logStream.is_open()) {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        logStream << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") 
                  << " " << logMsg << std::endl;
        logStream.flush();
    }
}

void ModernLogger::error(const std::string& message) {
    std::string logMsg = "[ERROR] " + message;
    std::cerr << "❌ " << logMsg << std::endl;
    
    if (logStream.is_open()) {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        logStream << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") 
                  << " " << logMsg << std::endl;
        logStream.flush();
    }
}

void ModernLogger::debug(const std::string& message) {
    #ifdef DEBUG
    std::string logMsg = "[DEBUG] " + message;
    std::cout << "🐛 " << logMsg << std::endl;
    
    if (logStream.is_open()) {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        logStream << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") 
                  << " " << logMsg << std::endl;
        logStream.flush();
    }
    #endif
}

ModernLogger::~ModernLogger() {
    if (logStream.is_open()) {
        info("日志系统关闭");
        logStream.close();
    }
    std::cout << "📝 日志系统已关闭" << std::endl;
}
