#include "cplusplus.hpp"
using namespace std;

/* ---------- 浅拷贝 ---------- */
class Shallow
{
public:
    char *name; // 只保存指针
    Shallow(const char *s)
    {
        name = new char[strlen(s) + 1];
        strcpy(name, s);
    }
    /* 默认拷贝构造：完全不管新内存，直接拷贝指针值 */
    Shallow(const Shallow &other) : name(other.name) {}

    ~Shallow()
    {
        delete[] name; // 释放同一块内存
    }
};

/* ---------- 深拷贝 ---------- */
class Deep
{
public:
    char *name; // 同样保存指针
    Deep(const char *s)
    {
        name = new char[strlen(s) + 1];
        strcpy(name, s);
    }
    /* 自己写拷贝构造：重新申请内存，真正复制内容 */
    Deep(const Deep &other) : name(new char[strlen(other.name) + 1])
    {
        strcpy(name, other.name);
    }

    ~Deep()
    {
        delete[] name; // 释放各自独立的内存
    }
};

/* ---------- 测试 ---------- */
int main()
{
    std::cout << "----- 浅拷贝 -----\n";
    {
        // Shallow s1("Alice");
        // Shallow s2 = s1; // 没写深拷贝，只是指针复制
        // fmt::print("s1.name = {}, address = {}\n", s1.name, (void *)s1.name);
        // fmt::print("s2.name = {}, address = {}\n", s2.name, (void *)s2.name);
        // /* 两个地址一模一样，指向同一块内存！ */
        // strcpy(s2.name, "Bob"); // 改一个，另一个跟着变
        // fmt::print("把 s2 改成 Bob 后：\n");
        // fmt::print("s1.name = {}\n", s1.name);
        // fmt::print("s2.name = {}\n", s2.name);
        // /* 析构时同一块内存会被 delete 两次 → 未定义行为（可能崩溃） */
    }

    std::cout << "\n----- 深拷贝 -----\n";
    {
        Deep d1("Carol");
        Deep d2 = d1; // 真正复制内容
        fmt::print("d1.name = {}, address = {}\n", d1.name, (void *)d1.name);
        fmt::print("d2.name = {}, address = {}\n", d2.name, (void *)d2.name);
        /* 地址不同，各自独立 */
        strcpy(d2.name, "Dave");
        std::cout << "把 d2 改成 Dave 后：\n";
        fmt::print("d1.name = {}\n", d1.name);
        fmt::print("d2.name = {}\n", d2.name);
        /* 析构时各自释放自己的内存，安全 */
    }
    return 0;
}
