#include <iostream>
#include <fstream>
#include <fmt/format.h>
#include <filesystem>
#include <string>
#include "logger.hpp"

using fmt::print;
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

void test0()
{
    auto currentPath = std::filesystem::current_path();
    print("📍 当前工作目录: {}\n", currentPath.string());
    print("#--------------------------------------------------#\n");

    string filename = "test.txt";
    ifstream ifs(filename);

    if (!ifs)
    {
        cerr << "ifs open file fail!";
        return;
    }

    string line;
    while (getline(ifs, line))
    {
        cout << line << endl;
    }
    ifs.close();
}

void test1()
{
    ifstream ifs("test2.cc");

    if (!ifs)
    {
        cerr << "ifs open file fail!";
        return;
    }

    // 读取一个文件的所有内容先要获取文件的大小
    // 将游标放到了文件的最后（尾后）
    ifs.seekg(0, std::ios::end); // std::ios::end 表示文件尾后
    long length = ifs.tellg();   // 获取尾后下标，实际就是总的字符数
    // cout << length << endl;
    LOG_INFO("文件大小为：{}", length);

    char *pdata = new char[length + 1]();
    // 需要将游标再放置到文件开头
    ifs.seekg(0, std::ios::beg); // std::ios::beg 表示文件开头
    ifs.read(pdata, length);

    // content包含了文件的所有内容，包括空格、换行
    string content(pdata);
    LOG_INFO("\n{}", content);
    /* cout << pdata << endl; */
    ifs.close();
}

void test2()
{
    ifstream ifs("文件io.txt", std::ios::ate); // ate表示打开文件后将游标放在文件尾后

    if (!ifs)
    {
        LOG_ERROR("ifs open file fail!");
        return;
    }

    long length = ifs.tellg(); // 获取尾后下标，实际就是总的字符数
    LOG_INFO("文件大小为：{}", length);

    char *pdata = new char[length + 1]();
    ifs.seekg(0, std::ios::beg); // std::ios::beg 表示文件开头
    ifs.read(pdata, length);

    // content包含了文件的所有内容，包括空格、换行
    string content(pdata);
    LOG_INFO("\n{}", content);

    ifs.close();
}
void test3()
{
    // 文件输出流绑定的文件对象如果不存在就创建
    ofstream ofs("output.txt", std::ios::app); // 使用默认std::ios::out模式会清空原有内容，指定std::ios::app可在文件末尾追加内容

    if (!ofs)
    {
        LOG_ERROR("ofs open file fail!");
        return;
    }

    string line("guopeng\n");
    ofs << line;
    ofs.close();
}

int main()
{
    INIT_LOGGER();
    test2();
    return 0;
}