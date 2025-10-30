#include <iostream>
#include <fstream>
#include <fmt/format.h>
#include <filesystem>
#include <string>

// 添加 spdlog 相关头文件
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

using fmt::print;
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

/**
 * 🔧 初始化日志系统
 * 设置同时输出到控制台和文件
 */
void setupLogger()
{
    try
    {
        // 创建日志目录（如果不存在）
        std::filesystem::create_directories("/home/HwHiAiUser/gp/Cppbase/logs");
        
        // 创建控制台 sink（带颜色）
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_level(spdlog::level::info);  // 控制台显示 info 及以上级别
        
        // 创建文件 sink
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
            "/home/HwHiAiUser/gp/Cppbase/logs/fileio.log", true);  // true 表示截断模式
        fileSink->set_level(spdlog::level::debug);  // 文件记录 debug 及以上级别
        
        // 创建多 sink logger
        spdlog::sinks_init_list sinkList = {consoleSink, fileSink};
        auto logger = std::make_shared<spdlog::logger>("file_logger", sinkList.begin(), sinkList.end());
        
        // 设置为默认 logger
        spdlog::set_default_logger(logger);
        spdlog::set_level(spdlog::level::debug);
        
        // 设置日志格式：[时间] [级别] [函数名] 消息
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%!] %v");
        
        spdlog::info("🚀 日志系统初始化成功！");
        spdlog::info("📁 日志文件位置: /home/HwHiAiUser/gp/Cppbase/logs/fileio.log");
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cerr << "❌ 日志初始化失败: " << ex.what() << std::endl;
    }
}

/**
 * 📖 测试函数0：逐行读取文件
 * 演示基本的文件读取和错误处理
 */
void test0()
{
    spdlog::info("🔍 开始执行 test0() - 逐行读取文件");
    
    auto currentPath = std::filesystem::current_path();
    print("📍 当前工作目录: {}\n", currentPath.string());
    spdlog::debug("当前工作目录: {}", currentPath.string());
    print("#--------------------------------------------------#\n");

    string filename = "test.txt";
    spdlog::info("📂 尝试打开文件: {}", filename);
    
    ifstream ifs(filename);

    if (!ifs)
    {
        spdlog::error("❌ 无法打开文件: {} - 请检查文件是否存在", filename);
        cerr << "ifs open file fail!";
        return;
    }
    
    spdlog::info("✅ 文件打开成功: {}", filename);

    string line;
    int lineCount = 0;
    spdlog::debug("开始逐行读取文件内容...");
    
    while (getline(ifs, line))
    {
        lineCount++;
        cout << line << endl;
        spdlog::debug("读取第 {} 行: {}", lineCount, line);
    }
    
    ifs.close();
    spdlog::info("📚 文件读取完成，共读取 {} 行", lineCount);
    spdlog::info("🔒 文件已关闭: {}", filename);
}

/**
 * 📁 测试函数1：读取整个文件内容
 * 演示获取文件大小和一次性读取
 */
void test1()
{
    spdlog::info("🔍 开始执行 test1() - 读取整个文件内容");
    
    string filename = "test2.cc";
    spdlog::info("📂 尝试打开文件: {}", filename);
    
    ifstream ifs(filename);

    if (!ifs)
    {
        spdlog::error("❌ 无法打开文件: {} - 请检查文件是否存在", filename);
        cerr << "ifs open file fail!";
        return;
    }
    
    spdlog::info("✅ 文件打开成功: {}", filename);

    // 获取文件大小
    spdlog::debug("🔍 开始获取文件大小...");
    ifs.seekg(0, std::ios::end); // 移动到文件末尾
    long length = ifs.tellg();   // 获取当前位置（即文件大小）
    
    print("文件大小为：{}\n", length);
    spdlog::info("📏 文件大小: {} 字节", length);

    // 分配内存
    spdlog::debug("💾 分配内存: {} 字节", length + 1);
    char *pdata = new char[length + 1]();
    
    // 移动到文件开头并读取
    spdlog::debug("📖 移动文件指针到开头并开始读取...");
    ifs.seekg(0, std::ios::beg);
    ifs.read(pdata, length);

    // 转换为字符串并输出
    string content(pdata);
    cout << "content:" << endl;
    cout << content << endl;
    
    spdlog::info("✅ 文件内容读取完成，内容长度: {} 字符", content.length());
    
    // 清理资源
    delete[] pdata;
    ifs.close();
    spdlog::debug("🧹 内存已释放，文件已关闭");
    spdlog::info("🔒 文件已关闭: {}", filename);
}

/**
 * 📁 测试函数2：使用 ate 模式打开文件
 * 演示不同的文件打开模式
 */
void test2()
{
    spdlog::info("🔍 开始执行 test2() - 使用 ate 模式读取文件");
    
    string filename = "test2.cc";
    spdlog::info("📂 使用 ios::ate 模式打开文件: {}", filename);
    
    ifstream ifs(filename, std::ios::ate); // ate表示打开后游标在文件末尾

    if (!ifs)
    {
        spdlog::error("❌ 无法打开文件: {} - 请检查文件是否存在", filename);
        cerr << "ifs open file fail!";
        return;
    }
    
    spdlog::info("✅ 文件打开成功 (ate模式): {}", filename);

    // 由于使用了 ate 模式，游标已经在文件末尾
    long length = ifs.tellg();
    print("文件大小为：{}\n", length);
    spdlog::info("📏 文件大小 (ate模式): {} 字节", length);

    spdlog::debug("💾 分配内存: {} 字节", length + 1);
    char *pdata = new char[length + 1]();
    
    spdlog::debug("📖 移动文件指针到开头并开始读取...");
    ifs.seekg(0, std::ios::beg);
    ifs.read(pdata, length);

    string content(pdata);
    cout << "content:" << endl;
    cout << content << endl;
    
    spdlog::info("✅ 文件内容读取完成 (ate模式)，内容长度: {} 字符", content.length());
    
    // 清理资源
    delete[] pdata;
    ifs.close();
    spdlog::debug("🧹 内存已释放，文件已关闭");
    spdlog::info("🔒 文件已关闭: {}", filename);
}

/**
 * ✍️ 测试函数3：写入文件
 * 演示文件写入和追加模式
 */
void test3()
{
    spdlog::info("🔍 开始执行 test3() - 写入文件");
    
    string filename = "output.txt";
    spdlog::info("📝 使用 ios::app 模式打开文件进行写入: {}", filename);
    
    // 使用追加模式，不会清空原有内容
    ofstream ofs(filename, std::ios::app);

    if (!ofs)
    {
        spdlog::error("❌ 无法打开文件进行写入: {}", filename);
        cerr << "ofs open file fail!";
        return;
    }
    
    spdlog::info("✅ 文件打开成功 (写入模式): {}", filename);

    string line("guopeng\n");
    spdlog::debug("✏️ 准备写入内容: {}", line.substr(0, line.length()-1)); // 去掉换行符显示
    
    ofs << line;
    spdlog::info("✅ 内容写入成功: {} 字符", line.length());
    
    ofs.close();
    spdlog::info("🔒 文件已关闭: {}", filename);
    
    // 验证文件是否存在
    if (std::filesystem::exists(filename))
    {
        auto fileSize = std::filesystem::file_size(filename);
        spdlog::info("📊 写入后文件大小: {} 字节", fileSize);
    }
}

int main()
{
    // 🔧 首先初始化日志系统
    setupLogger();
    
    spdlog::info("🎯 程序开始执行 - 文件操作示例");
    // spdlog::info("=" * 50);
    
    try
    {
        // 可以选择运行不同的测试函数
        // test0();  // 逐行读取
        // test1();  // 读取整个文件
        // test2();  // ate 模式读取
        test3();     // 写入文件
        
        // spdlog::info("=" * 50);
        spdlog::info("🎉 程序执行完成！");
    }
    catch (const std::exception& e)
    {
        spdlog::error("💥 程序执行过程中发生异常: {}", e.what());
    }
    
    // 清理日志系统
    spdlog::drop_all();
    
    return 0;
}
