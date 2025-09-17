#include "cplusplus.hpp"
using namespace std;

void test0()
{
    int iNumber = 100;
    float fNumber = 0;
    // fNumber = (float)iNumber; // C风格
    fNumber = static_cast<float>(iNumber);// C++风格
    fmt::print("iNumber = {}, fNumber = {:.2f}\n", iNumber, fNumber);
}

int main(int argc, char *argv[])
{
    test0();
    return 0;
}