#include "cplusplus.hpp"
using namespace std;


void test0()
{
    const int a = 100;
    // a = 20; // error: assignment of read-only variable 'a'
    fmt::print("a - 10 = {}\n", a-10);
}   

void test1(){
    int num1 = 100,num2 = 200;
    int *p1 = &num1;
    *p1 = 20;  //*p 是num的别名
    // fmt::print("num = {}, p1 = {}\n", num1, num2, static_cast<void*>(p1));
    fmt::print("num = {}, p1 = {}\n", num1, static_cast<void*>(p1));
    const int *p2 = &num2;
    // *p2 = 30; // error: assignment of read-only variable 'p2'
}
int main(int argc, char *argv[])
{
    test1();
    return 0;
}