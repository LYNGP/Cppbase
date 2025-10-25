#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>
#include <fstream>

class ModernLogger {
private:
    std::string logFile;
    std::ofstream logStream;
    
    // 私有构造函数
    ModernLogger(const std::string& filename = "app.log");

public:
    // 获取单例实例
    static ModernLogger& getInstance();
    
    // 禁止拷贝和赋值
    ModernLogger(const ModernLogger&) = delete;
    ModernLogger& operator=(const ModernLogger&) = delete;
    
    // 日志方法
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void debug(const std::string& message);
    
    // 析构函数
    ~ModernLogger();
};

#endif
