#include "cplusplus.hpp" // 里面已 #include <fmt/core.h> 等
using namespace std;

class Point
{
private:
    // 0. 类内成员初值（C++11）
    int _ix = 0; // 如果没有任何构造函数显式处理 _ix，它就是 0
    int _iy = 0;

public:
    // 1.无参构造
    // Point(){
    //     fmt::print("Point()  默认构造函数  ({} , {})\n", _ix, _iy);
    // } // 默认构造函数

    Point() : _ix(30), _iy(10)
    {
        fmt::print("Point()  无参构造  ({} , {})\n", _ix, _iy);
    }

    // 2.有参构造
    Point(int x, int y) : _ix(x), _iy(y)
    {
        fmt::print("Point(int,int)  有参构造  ({} , {})\n", _ix, _iy);
    }

    void print()
    {
        fmt::print("当前坐标: ({}, {})\n", _ix, _iy);
    }
};

void test()
{
    Point p1; // 调用 Point()
    p1.print();

    Point p2(3, 4); // 调用 Point(int,int)
    p2.print();
}

int main()
{
    test();
    return 0;
}