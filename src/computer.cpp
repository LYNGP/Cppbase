#include "computer.hpp"

using std::cout;
using std::endl;

// void Computer::setBrand(const char * brand)
// { 
//     strcpy(_brand, brand); 
// }
// void Computer::setPrice(float price)
// { 
//     _price = price;
// }
void Computer::print(){
    cout << "品牌: " << _brand << " 价格: " << _price << endl;
}