#include "cplusplus.hpp"
#include "computer.hpp"

using std::cout;
using std::endl;

void test0()
{
    Computer pc("xioami", 10000);
    pc.print();
    Computer pc2(pc);
    pc2.print();
    Computer pc3 = pc;
    pc3.print();
}

class E
{
    double _e;
    char _eArr[20];
    int _e2;
    double _e1;
};

int main()
{
    test0();
    // cout << sizeof(E) << endl;
    return 0;
}
