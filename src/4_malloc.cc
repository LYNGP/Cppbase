#include "cplusplus.hpp"
using namespace std;

//c申请、释放堆空间
void test0()
{
    int *p1 = (int*)malloc(sizeof(int));
    *p1 = 10;
    cout << *p1 << endl;
    free(p1);
}
//c++申请、释放堆空间
void test1()
{
    int *p2 = new int(20);
    cout << *p2 << endl;
    delete p2;
}
//new 为数组申请空间
void test2()
{
    int *p3 = new int[3]();
    for (int i = 0; i < 3; i++)
    {
        fmt::print("p3[{}] = {}\n", i, p3[i]);
    }
    delete[] p3;
}
int main(int argc, char *argv[])
{
    test0();
    test1();
    test2();
    return 0;
}