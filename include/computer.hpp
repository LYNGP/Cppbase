#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

/*
class Computer
{
public:
	// 成员函数
	//  Computer(){};//默认构造函数（无参）

	Computer()
	: _brand("HP")
	, _price(10000.0) // 初始化列表
	{
		cout << "初始化列表" << endl;
	}

	Computer(const char *brand, float price)
	{
		cout << "有参构造函数 --> 初始化" << endl;
		strcpy(_brand, brand);
		_price = price;
	} // 有参构造函数 --> 初始化

	void setBrand(const char *brand); // 设置品牌

	void setPrice(float price); // 设置价格

	void print(); // 打印信息
private:
	// 数据成员
	char _brand[20];
	float _price;
};
*/

/*
class Computer {
public:
	Computer(const char * brand, double price)
	: _brand(new char[strlen(brand) + 1]())
	, _price(price)
	{
		cout << "有参构造函数 --> 初始化" << endl;
		strcpy(_brand, brand);
	}
	~Computer()
	{
		if(_brand){
			delete [] _brand;
			_brand = nullptr;//设为空指针，安全回收
		};
		cout << "~Computer()" << endl;
	}
	void print(); // 打印信息
private:
	char * _brand;
	double _price;
};
*/

#include <string>

class Computer
{
public:
	Computer(const string &brand, double price)
		: _brand(brand), _price(price) // string 自动处理内存
	{
		cout << "有参构造函数 --> 初始化" << endl;
	}
	Computer(const Computer &other) // 拷贝构造函数
		: _brand(other._brand), _price(other._price)
	{
		cout << "拷贝构造函数 --> 初始化" << endl;
	}
	// 不需要手动管理内存了！
	void print(); // 打印信息

private:
	string _brand; // 自动内存管理
	double _price;
};