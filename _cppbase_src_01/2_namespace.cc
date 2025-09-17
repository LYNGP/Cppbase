#include "cplusplus.hpp"
using namespace std;

namespace wd
{
    int num = 999;
    void func()
    {
        fmt::print("func\n");
    }
    namespace guopeng
    {
        int num = 888;
    }
}
namespace huawei
{
    int num = 1999;
    void func()
    {
        fmt::print("func2\n");
    }
}

void test0()
{
    fmt::print("test0\n");
    fmt::print("wd::num = {}\n", wd::num);
    fmt::print("huawei::num = {}\n", huawei::num);
    wd::func();
    huawei::func();
}

void test1()
{
    fmt::print("test1\n");
    using namespace wd;
    fmt::print("wd::num = {}\n", num);
    fmt::print("wd::guopeng::num = {}\n", guopeng::num);
}

int main(int argc, char *argv[])
{
    // test0();
    test1();
    return 0;
}