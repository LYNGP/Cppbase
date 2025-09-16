#include "cplusplus.hpp"
using namespace std;
void test0()
{
    int num = 10;
    int &ref = num;
    cout << "num = " << num << endl;
    cout << "ref = " << ref << endl;
    ref = 20;
    cout << "num = " << num << endl;
    cout << "ref = " << ref << endl;

    // fmt::ptr(p) 把任意裸指针 p 包装成 const void*
    // 引用是被限制的指针，在汇编里，引用的本质就是“间接寻址”。
    fmt::print("&num = {}\n", fmt::ptr(&num));
    fmt::print("&ref = {}\n", fmt::ptr(&ref));
}
int main(int argc, char *argv[])
{
    test0();
    return 0;
}