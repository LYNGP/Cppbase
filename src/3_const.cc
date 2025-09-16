#include "cplusplus.hpp"
using namespace std;

void test0()
{
    const int a = 100;
    // a = 20; // error: assignment of read-only variable 'a'
    fmt::print("a - 10 = {}\n", a - 10);
}

void test1()
{
    int a = 10;
    int b = 20;

    /* 1. 普通整数变量 */
    int value = a; // plain int
    value = 99;    // OK, 数据可改
    cout << "value = " << value << '\n';

    /* 2. 普通指针：pointer to int */
    int *p1 = &a;
    *p1 = 11; // OK, 数据可改
    p1 = &b;  // OK, 指针可改
    cout << "*p1 = " << *p1 << '\n';

    /* 3. 指针常量：const pointer to int */
    int *const p2 = &a; // const appears after *
    // p2 = &b;             // ERROR! 指针本身不可改
    *p2 = 12; // OK, 指向的数据可改
    cout << "*p2 = " << *p2 << '\n';

    /* 4. 常量指针：pointer to const int */
    const int *p3 = &a; // const appears before *
    // *p3 = 13;            // ERROR! 数据不可改
    p3 = &b; // OK, 指针可改
    cout << "*p3 = " << *p3 << '\n';

    /* 5. 双 const：const pointer to const int */
    const int *const p4 = &a;
    // *p4 = 14;            // ERROR! 数据不可改
    // p4 = &b;             // ERROR! 指针不可改
    cout << "*p4 = " << *p4 << '\n';
}
int main(int argc, char *argv[])
{
    test1();
    return 0;
}