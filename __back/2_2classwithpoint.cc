#include "cplusplus.hpp"
using namespace std;

class Computer
{
public:
    Computer(const char *brand, double price)
        : _brand(new char[strlen(brand) + 1]), _price(price)
    {
        strcpy(_brand, brand);
    }
    void print()
    {
        fmt::print("品牌: {}, 价格: {}\n", _brand, _price);
    }

    ~Computer()
    {

        if (_brand)
        {
            delete[] _brand;
            _brand = nullptr;
        }
    }

private:
    char *_brand;
    double _price;
};
void test0()
{
    Computer pc("Dell", 2000);
    pc.print();
}

int main(int argc, char *argv[])
{
    test0();
    return 0;
}