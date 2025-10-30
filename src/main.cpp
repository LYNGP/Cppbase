#include <iostream>
#include "logger.hpp"

using std::cout;
using std::endl;

class Point
{
public:
    Point(int x, int y)
        : _ix(x), _iy(y)
    {
    }
    // 声明友元关系，这个函数可访问类的私有成员
    friend float distance(const Point &lhs, const Point &rhs);

private:
    int _ix;
    int _iy;
};

// 参数设计：
// 引用传递：避免对象拷贝带来的性能开销
// const修饰：防止函数内部意外修改对象状态
// 右值绑定：const引用可以绑定右值对象
float distance(const Point &lhs, const Point &rhs)
{
    return sqrt((lhs._ix - rhs._ix) * (lhs._ix - rhs._ix) +
                (lhs._iy - rhs._iy) * (lhs._iy - rhs._iy));
}

void test0()
{
    Point p1(0, 0);
    Point p2(3, 4);
    LOG_INFO("distance {}", distance(p1, p2));
}

int main()
{
    INIT_LOGGER();
    test0();
    return 0;
}
