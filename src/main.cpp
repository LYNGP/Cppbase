#include "cplusplus.hpp"

using std::cout;
using std::endl;

void test0() {
    cout << "test0" << endl;
}

int main(int argc, const char* argv[]) {
    test0();
    cout << "Hello, world!" << endl;
    fmt::print("The answer is {}.\n", 42);
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    fmt::print("The current date and time is {}.\n", fmt::localtime(now));
    std::string s = "Hello, world!";
    fmt::print("The length of '{}' is {}.\n", s, s.length());
    return 0;
}