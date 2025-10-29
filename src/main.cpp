#include <iostream>
#include <string>
#include <vector>
#include <fmt/format.h>

using std::cout;
using std::endl;
using std::vector;

void test0()
{
    // vector常用的几种构造形式
    vector<int> v1;
    vector<int> v2(10);
    vector<int> v3(10, 20);
    vector<int> v4{1, 2, 3, 4, 5};
    vector<int> v5(v4.begin(), v4.end() - 2); //[0,3)

    v2.push_back(30);
    v2.push_back(40);
    v2.pop_back();
    fmt::print("v2 size: {}\n", v2.size());
    fmt::print("v2 capacity: {}\n", v2.capacity()); // 扩容到原来的 1.5倍 或 2倍

    // v2.shrink_to_fit();  //释放多余空间
    // v2.clear();          //清空元素但不释放空间

    for (auto &ele : v2)
    {
        cout << ele << " ";
    }
    cout << endl;

    fmt::print("vector对象的大小: {}\n", sizeof(v3));
    /*
    #-------------------------#
    v2 size: 11
    v2 capacity: 20
    0 0 0 0 0 0 0 0 0 0 30 
    vector对象的大小: 24
    #-------------------------#
    */
}

int main()
{
    cout << "#-------------------------#" << endl;
    test0();
    cout << "#-------------------------#" << endl;

    return 0;
}