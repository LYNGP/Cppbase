#include <iostream>
#include <fstream>
#include <fmt/format.h>
#include <filesystem>
#include <string>
using fmt::print;
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
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
}

void test1(){
    string filename = "test2.cc";
    ifstream ifs(filename); 

    if(!ifs){
        cerr << "ifs open file fail!";
        return;
    }
    
    //读取一个文件的所有内容先要获取文件的大小
    //将游标放到了文件的最后（尾后）
    ifs.seekg(0,std::ios::end);
    long length = ifs.tellg();//获取尾后下标，实际就是总的字符数
    // cout << length << endl;
    print("文件大小为：{}\n", length);

    char * pdata = new char[length + 1]();
    //需要将游标再放置到文件开头
    ifs.seekg(0,std::ios::beg);
    ifs.read(pdata,length);

    //content包含了文件的所有内容，包括空格、换行
    string content(pdata);
    cout << "content:" << content << endl;
    /* cout << pdata << endl; */
    ifs.close();
}

int main()
{
    test1();
    return 0;
}