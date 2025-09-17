#include "cplusplus.hpp"
using namespace std;

// class Computer // 类名大驼峰命名法
// {
// public:                              // 类提供给外界访问的接口
//     void setBrand(const char *brand) // 成员函数小驼峰命名法
//     {
//         strcpy(_brand, brand);
//     }

//     void setPrice(float price)
//     {
//         _price = price;
//     }

//     void print()
//     {
//         fmt::print("Brand: {}, Price: {}\n", _brand, _price);
//     }

// private:
//     char _brand[20]; // 数据成员前加下划线
//     float _price;
// };
class Computer
{
public:
    // 成员函数
    void setBrand(const char *brand); // 设置品牌

    void setPrice(float price); // 设置价格

    void print(); // 打印信息
private:
    // 数据成员
    char _brand[20];
    float _price;
};

void Computer::setBrand(const char *brand)
{
    strcpy(_brand, brand);
}
void Computer::setPrice(float price)
{
    _price = price;
}
void Computer::print()
{
    fmt::print("Brand: {}, Price: {}\n", _brand, _price);
}
void test0()
{
    Computer phone;
    phone.setBrand("Xiaomi");
    phone.setPrice(1999);
    phone.print();
}

int main(int argc, char *argv[])
{
    test0();
    return 0;
}
