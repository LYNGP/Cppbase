#include <iostream>
#include <fstream>
#include <fmt/format.h>
using std::cout;
using std::endl;
using std::ifstream;
using fmt::print;

void test0() {
    cout << "test0" << endl;
    ifstream ifs;
    ifs.open("test.txt");
}

int main() {
    test0();
    return 0;
}