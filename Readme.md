### cppbase day01：

[const关键字]
1. const常量和宏定义常量的区别：
    1.1 宏定义发生时机在预处理时，做字符串的替换，const常量是在编译时，本质还是一个变量，只是用const关键字限定之后，赋予只读属性。
    1.2 宏定义没有类型，不做任何类型检查；const常量有具体的类型，在编译期会执行类型检查。

2.  指针常量 --> 指针是常量 --> int * const pa = &a; // 指向不可变，所指数据可变。const pa  常量指针（const pointer）
    常量指针 --> 常量的指针 --> const int * pb = &b; // 指向可变，所指数据不可变。const int 指向常量的指针（pointer to const）
    const int * const pc = &c;//指向和指向的值皆不能进行修改

[new/delete表达式] --> C语言中使用malloc/free函数，C++使用new/delete表达式;
1. new表达式的返回值是相应类型的指针，malloc返回值是void*；
2. new表达式申请空间时可以直接初始化, malloc申请的空间不会进行初始化；
3. new会根据相应类型自动获取空间大小;
4. delete只是回收了指针指向的空间，但这个指针变量依然还在，需要手动将指针置空；
5. delete[]可以释放数组空间，释放时会自动调用析构函数，对应new int[5]() 。

[引用] --> 引用是一个已定义（即先初始化）变量的别名 <引用一经绑定，无法更改绑定> --> int &ref = a; // ref是a的别名，可以直接用ref来访问a的值，也可以修改a的值。
1. 引用必须初始化，指针可以不初始化；
2. 引用不能修改绑定，但是指针可以修改指向；
3. 在代码层面对引用本身取址取到的是变量的地址，但是对指针取址取到的是指针变量本身的地址；
```cpp
void func(const int & x){//保证了引用传递的安全性
    x = 100; //error
}
```
4. 不要返回局部变量的引用，另外，如果返回的是一个堆空间变量的引用，那么这个函数调用一次就会new一次，非常容易造成内存泄露。

[默认参数与函数重载] --> 同一作用域内，可以有一组具有相同函数名，不同参数列表的函数，这组函数被称为重载函数。
1. 函数参数的数量、类型、顺序任一不同则可以构成重载, 只有返回类型不同，参数完全相同，是不能构成重载的;
2. 通常是将默认值的设置放在声明中而不是定义 ，函数参数赋默认值从右向左（严格）

### cppbase day02：

[类与对象] --> 由对象抽象出类，对象是类的实例，类可以包含数据成员、成员函数、构造函数、析构函数等。
1. 函数声明放在头文件，函数定义放在实现文件中
2. 构造函数 --> 完成对象成员变量的初始化及其他操作（如为指针成员动态申请内存）--> 数据成员的初始化与声明顺序一致
3. 内存对齐 --> 除数组外，其他类型的数据成员以较大数据成员所占空间的倍数进行对齐。内存对齐还与数据成员的声明顺序有关。
4. 析构函数 --> 释放对象申请的内存 --> 一般不定义，由编译器自动生成，但如果类中含有指针成员，需要手动释放内存。
5. 拷贝构造函数 --> 复制对象时调用，默认情况下，编译器会自动生成，但如果类中含有指针成员，需要手动实现。
    5.1 默认的拷贝构造函数，是浅拷贝，指向同一片内存；
    5.2 拷贝构造函数需要显式写出时（该类有指针成员申请堆空间），在自定义的拷贝构造函数中要换成深拷贝的方式，先申请空间，再复制内容；
    5.3 拷贝构造函数的调用时机：
        5.3.1 当使用一个已经存在的对象初始化另一个同类型的新对象时；
        5.3.2 对象作为函数参数（值传递时）--> 参数传递使用引用避免不必要拷贝;
        5.3.3 当函数的返回值是对象，执行return语句时（编译器有优化）。
6. 三合成原则：拷贝构造函数、赋值运算符函数、析构函数，如果需要手动定义其中的一个，那么另外两个也需要手动定义。
    赋值运算符函数 --> 实现对象之间的赋值操作，一般不定义，由编译器自动生成，但如果类中含有指针成员，需要手动实现。
        返回类型不可以是void，无法处理连续赋值
        返回与参数一定要是引用，避免多余的拷贝，增加不必要的开销
```cpp
Computer & operator=(const Computer & rhs){
    this->_brand = rhs._brand;
    this->_price = rhs._price;
    return *this;
}

Computer & operator=(const Computer & rhs){
    if(this != &rhs){
        delete [] _brand;
        _brand = new char[strlen(rhs._brand)]();
        strcpy(_brand,rhs._brand);
        _price = rhs._price;
    }
    return *this;
}
```
7. this指针：<常量指针>
    生成：当对象调用非静态成员函数时，编译器自动将对象地址作为this指针传入
    销毁：成员函数执行结束时this指针生命周期结束
    作用：使成员函数能准确访问本对象的成员变量和成员函数


[特殊的数据成员]
常量成员、引用成员、对象成员和静态成员
1. 常量成员、引用成员、对象成员必须在初始化列表中进行初始化，或者在声明时初始化，另外引用成员需要绑定一个已经存在的、且在这个引用成员的生命周期内始终有效的变量（对象）。
2. C++ 允许使用 static （静态存储）修饰数据成员，这样的成员在编译时就被创建并初始化的（与之相比，对象是在运行时被创建的），且其实例只有一个，被所有该类的对象共享，就像住在同一宿舍里的同学共享一个房间号一样。静态数据成员和之前介绍的静态变量一样，当程序执行时，该成员已经存在，一直到程序结束，任何该类对象都可对其进行访问，静态数据成员存储在全局/静态区，并不占据对象的存储空间。
3. 静态数据成员被整个类的所有对象共享。
4. 对于静态数据成员的初始化，必须放在类外！
```cpp
声明（.h）：告诉编译器"这个变量存在"
定义（.cpp）：告诉链接器"变量的具体位置和初值"
```
5. 能对表达式取地址的称为左值，不能取地址的称为右值。

[单例模式] 
0. 想象一个国家🏛️，只能有一位总统。不管从哪个部门访问"总统"这个职位，得到的都是同一个人。单例模式就是这样——确保一个类只有一个实例，并提供全局访问点。
1. 应用场景：
    1、有频繁实例化然后销毁的情况，也就是频繁的 new 对象，可以考虑单例模式；
    2、创建对象时耗时过多或者耗资源过多，但又经常用到的对象；
    3、当某个资源需要在整个程序中只有一个实例时，可以使用单例模式进行管理（全局资源管理）。例如数据库连接池、日志记录器等；
    4、当需要读取和管理程序配置文件时，可以使用单例模式确保只有一个实例来管理配置文件的读取和写入操作（配置文件管理）；
    5、在多线程编程中，线程池是一种常见的设计模式。使用单例模式可以确保只有一个线程池实例，方便管理和控制线程的创建和销毁；
    6、GUI应用程序中的全局状态管理：在GUI应用程序中，可能需要管理一些全局状态，例如用户信息、应用程序配置等。使用单例模式可以确保全局状态的唯一性和一致性。
2. 
```cpp
    // 防止拷贝和赋值
    Point(const Point&) = delete;
    Point& operator=(const Point&) = delete;
    核心实现：
        使用静态成员变量_pInstance保存单例对象指针
        通过静态成员函数getInstance()获取单例对象
        使用destroy()函数手动回收单例对象//智能指针
    关键细节：
        构造函数私有化：防止外部直接创建对象
        析构函数私有化：防止外部直接delete对象
        拷贝控制：使用=delete删除拷贝构造和赋值运算符，严格禁止复制
        指针判空：建议将nullptr写在判等左边，避免误写为赋值操作
```
3. 
什么是线程安全？
    在拥有共享数据的多条线程并行执行的程序中，线程安全的代码会通过同步机制保证各个线程都可以正常且正确的执行，不会出现数据污染等意外情况。

如何保证线程安全？
    给共享的资源加把锁，保证每个资源变量每时每刻至多被一个线程占用。
    让线程也拥有资源，不用去共享进程中的资源。如： 使用threadlocal可以为每个线程的维护一个私有的本地变量。

什么是单例模式？
    单例模式指在整个系统生命周期里，保证一个类只能产生一个实例，确保该类的唯一性。
    
单例模式分类
    单例模式可以分为懒汉式和饿汉式，两者之间的区别在于创建实例的时间不同：
    懒汉式：指系统运行中，实例并不存在，只有当需要使用该实例时，才会去创建并使用实例。（这种方式要考虑线程安全）
    饿汉式：指系统一运行，就初始化创建实例，当需要时，直接调用即可。（本身就线程安全，没有多线程的问题）

单例类特点
    构造函数和析构函数为private类型，目的禁止外部构造和析构
    拷贝构造和赋值构造函数为private类型，目的是禁止外部拷贝和赋值，确保实例的唯一性
    类里有个获取实例的静态函数，可以全局访问


### cppbase day03：
[C++字符串-string] 
```cpp
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void test0()
{
    string str1;             // 无参构造
    string str2("hello");    // C风格字符串构造
    string str3 = "hello";   // 隐式构造（本质是创建匿名对象后拷贝构造）
    string str4("world", 3); // 前3个字符构造，结果为"wor"
    string str5(str2);       // 拷贝构造
    string str6(str2, 1, 3); // 从位置1开始复制3个字符，结果为"ell"
    string str7(5, 'a');     // 生成"aaaaa"
}
void test1()
{
    char arr[] = "hello";
    string s1(arr, arr + 4); //[0,4)
    cout << s1 << endl;

    auto it = s1.begin(); // string::iterator
    auto it2 = s1.end();  // string::iterator
    cout << *it << endl;

    string s2(it, --it2); // [0,3)
    cout << s2 << endl;
}
void test2()
{
    string s1 = "hello";
    string s2 = "world";
    string s3 = s1 + "," + s2 + "!"; // 加号操作涉及3次内存操作（创建临时对象+拷贝构造+销毁临时对象）
    cout << s3 << endl;
}
void test3()
{
    string s1 = "hello ";
    cout << s1.size() << endl;

    s1.push_back('x');
    cout << s1 << endl;

    s1.append(" world"); // append仅1次内存操作（直接修改原对象）
    cout << s1 << endl;
}
void test4()
{
    string s1 = "hello world";
    // 通过下标遍历
    for (size_t i = 0; i < s1.size(); ++i)
    {
        cout << s1[i] << " ";
    }
    cout << endl;
    // 增强for循环遍历 
    for (auto &ch : s1) // & 代表操作的是元素本身，如果没有，则操作的是元素副本
    {
        cout << ch << " ";
    }
    cout << endl;
    // 迭代器方式进行遍历
    auto it = s1.begin();
    while (it != s1.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}
int main()
{
    test0();
    cout << "#-------------------------#" << endl;
    test1();
    cout << "#-------------------------#" << endl;
    test2();
    cout << "#-------------------------#" << endl;
    test3();
    cout << "#-------------------------#" << endl;
    test4();
    return 0;
}
```

[std::vector] --> 动态数组，支持随机访问，元素可以是任意类型，支持迭代器。
1. vector对象是由三个指针组成：
    _start指向当前数组中第一个元素存放的位置
    _finish指向当前数组中最后一个元素的下一个位置
    _end_of_storage指向当前数组能够存放元素的最后一个空间的下一个位置

    size():      _finish - _start
    capacity():  _end_of_storage - start

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <fmt/format.h>

using std::cout;
using std::endl;
using std::vector;

void test0()
{
    // vector常用的几种构造形式
    vector<int> v1;
    vector<int> v2(10);
    vector<int> v3(10, 20);
    vector<int> v4{1, 2, 3, 4, 5};
    vector<int> v5(v4.begin(), v4.end() - 2); //[0,3)

    v2.push_back(30);
    v2.push_back(40);
    v2.pop_back();
    fmt::print("v2 size: {}\n", v2.size());
    fmt::print("v2 capacity: {}\n", v2.capacity()); // 扩容到原来的 1.5倍 或 2倍

    // v2.shrink_to_fit();  //释放多余空间
    // v2.clear();          //清空元素但不释放空间

    for (auto &ele : v2)
    {
        cout << ele << " ";
    }
    cout << endl;

    fmt::print("vector对象的大小: {}\n", sizeof(v3));
    /*
    #-------------------------#
    v2 size: 11
    v2 capacity: 20
    0 0 0 0 0 0 0 0 0 0 30 
    vector对象的大小: 24
    #-------------------------#
    */
}

int main()
{
    cout << "#-------------------------#" << endl;
    test0();
    cout << "#-------------------------#" << endl;

    return 0;
}
```

```cpp
{
    vector<int> row = {1, 2, 3, 4, 5};
    vector<int> row1 = {6, 7, 8, 9};
    vector<int> row2 = {10, 11, 12, 13, 14, 15};

    vector<vector<int>> matrix{row, row1, row2};

    for (auto &row : matrix)
    {
        for (auto &item : row)
        {
            cout << item << " ";
        }
        cout << endl;
    }
    /*
    #-------------------------#
    1 2 3 4 5 
    6 7 8 9 
    10 11 12 13 14 15 
    #-------------------------#
    */
}
```

### cppbase day04：

[C++输入输出流]

1. 流的四种状态：--> 只要badbit/failbit/eofbit任一被置位，流即不可用
    goodbit：流处于有效工作状态（唯一可正常操作的状态） --> 等价于!fail() && !bad() && !eof()
    failbit：可恢复错误（如期望读取int却输入字符串）
    badbit： 系统级不可恢复错误（如硬件读写故障）
    eofbit： 到达流结尾（如文件读取完毕）

2. 标准输入输出流具有缓冲机制，缓冲区是内存预留的存储空间，用于临时存放IO数据。
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <fmt/format.h>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::istream;

void print_stream_status(istream &is)
{
    fmt::print("stream status is good ? {}\n", is.good());
    fmt::print("stream status is eof ? {}\n", is.eof());
    fmt::print("stream status is fail? {}\n", is.fail());
    fmt::print("stream status is bad ? {}\n", is.bad());
    if (!cin.good())
    {
        cin.clear();            // 恢复状态
        cin.ignore(1000, '\n'); // 清空缓冲区 必须包含<limits>头文件 --> ignore()第一个参数设置最大舍弃字符数 --> 第二个参数'\n'表示遇到换行符停止舍弃
        // 或使用：cin.ignore(numeric_limits<streamsize>::max(), '\n')
    }
}

void input_num(int &num)
{
    while (1)
    {
        cout << "请输入一个整数: ";
        if (cin >> num)
        { // 检查输入是否成功
            cout << "你输入的是: " << num << endl;
            break;
        }
        else
        {
            cout << "输入错误,请重试" << endl;

            // 清除错误状态,准备下次输入
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
void test0()
{
    int num = 0;
    input_num(num);
}
int main()
{
    cout << "#-------------------------#" << endl;
    test0();
    return 0;
    /*
    #-------------------------#
    请输入一个整数: g
    输入错误,请重试
    请输入一个整数: p
    输入错误,请重试
    请输入一个整数: 666
    你输入的是: 666
    */
}
```

3. 缓冲机制分为三种类型：全缓冲、行缓冲和不带缓冲。
    全缓冲：
        刷新条件：缓冲区满时才执行实际I/O操作
        典型应用：磁盘文件读写操作
        补充说明：即使行缓冲流在缓冲区满时也会强制刷新
    行缓冲：
        刷新条件：遇到换行符时执行I/O操作
        典型代表：标准输入cin，需按回车键才会刷新
        特殊情形：缓冲区满时同样会触发刷新
    不带缓冲：
        特点：数据即时刷新，无缓冲过程
        设计目的：确保关键信息立即输出
        典型应用：标准错误输出cerr，用于紧急错误提示
        优势说明：避免缓冲延迟，使错误信息能第一时间显示

4. 文件输入输出流： 
```cpp
ifstream();
explicit ifstream(const char* filename, openmode mode = ios_base::in);
explicit ifstream(const string & filename, openmode mode = ios_base::in);

ofstream();
explicit ofstream(const char* filename, openmode mode = ios_base::out);
explicit ofstream(const string & filename, openmode mode = ios_base::out);

fstream();
explicit fstream(const char* filename, openmode mode = ios_base::in|out);
explicit fstream(const string & filename, openmode mode = ios_base::in|out);
```

ifstream（文件输入流） 文件 → 文件输入流对象的缓冲区 → 程序中的数据结构
```cpp
    void test2()
{
    ifstream ifs("test2.cc",std::ios::ate);//ate表示打开文件后将游标放在文件尾后

    if (!ifs)
    {
        cerr << "ifs open file fail!";
        return;
    }

    long length = ifs.tellg();   // 获取尾后下标，实际就是总的字符数
    print("文件大小为：{}\n", length);

    char *pdata = new char[length + 1]();
    ifs.seekg(0, std::ios::beg); // std::ios::beg 表示文件开头
    ifs.read(pdata, length);

    // content包含了文件的所有内容，包括空格、换行
    string content(pdata);
    cout << "content:" << endl;
    cout << content << endl;
    /* cout << pdata << endl; */
    ifs.close();
}
```
ofstream（文件输出流）
```cpp
void test3()
{
    // 文件输出流绑定的文件对象如果不存在就创建
    ofstream ofs("output.txt",std::ios::app);//使用默认std::ios::out模式会清空原有内容，指定std::ios::app可在文件末尾追加内容

    if (!ofs)
    {
        cerr << "ofs open file fail!";
        return;
    }

    string line("guopeng\n");
    ofs << line;
    ofs.close();
}
```
5. 字符串流：
```cpp
//myserver.conf
ip 192.168.0.0
port 8888
dir ~HaiBao/53th/day06
    
//readConf.cc
void readConfig(const string & filename){
    ifstream ifs(filename);
    if(!ifs.good()){
        cout << "open file fail!" << endl;
        return;
    }
    
    string line;
    string key, value;
    while(getline(ifs,line)){
        istringstream iss(line);
        iss >> key >> value;
        cout << key << " -----> " << value << endl; 
    }
}

void test0(){
    readConfig("myserver.conf");
}
```

### cppbase day05：

[日志系统] -->spdlog

[友元] --> 将其他类/函数设置为类的友元，那么友元类/函数就可以在前一个类的类定义之外访问其私有成员了。用friend关键字声明友元。
1. 友元不受类中访问权限的限制——可访问私有成员
2. 友元破坏了类的封装性
3. 不能滥用友元 ，友元的使用受到限制
4. 友元是单向的——A类是B类的友元类，则A类成员函数中可以访问B类私有成员；但并不代表B类是A类的友元类，如果A类中没有声明B类为友元类，此时B类的成员函数中并不能访问A类私有成员
5. 友元不具备传递性——A是B的友元类，B是C的友元类，无法推断出A是C的友元类
6. 友元不能被继承——因为友元破坏了类的封装性，为了降低影响，设计层面上友元不能被继承

[运算符重载]
规则：
1. 其操作数类型必须要有自定义类类型或枚举类型
2. 其优先级和结合性还是固定不变的
3. 操作符的操作数个数是保持不变的
4. 运算符重载时 ，不能设置默认参数

[+、++、<<、>>运算符重载]
```cpp
#include <iostream>
#include "logger.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

void input_int_num(istream &is, int &num)
{
    while (1)
    {
        cout << "请输入一个整数: ";
        if (cin >> num)
        {
            break;
        }
        else
        {
            cout << "输入错误,请重试" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

class Complex
{
public:
    Complex(double real, double imag) : _real(real), _imag(imag) {}
    Complex operator+(const Complex &other) const
    {
        LOG_INFO("+号运算符重载");
        return Complex(_real + other._real, _imag + other._imag);
    }
    Complex &operator++()
    {
        LOG_INFO("前置++ 运算符重载");

        ++_real;
        ++_imag;
        return *this;
    }
    Complex operator++(int)
    {
        LOG_INFO("后置++ 运算符重载");

        Complex temp = *this;
        ++_real;
        ++_imag;
        return temp;
    }

    void print() const
    {
        LOG_INFO("Complex number: {} + {}i", _real, _imag);
    }

    friend ostream &operator<<(ostream &os, const Complex &rhs);
    friend istream &operator>>(istream &is, Complex &rhs);

private:
    int _real;
    int _imag;
};

ostream &operator<<(ostream &os, const Complex &rhs)
{
    // LOG_INFO("输出运算符<< 重载");
    os << rhs._real << "+" << rhs._imag << "i";
    return os;
}
istream &operator>>(istream &is, Complex &rhs)
{
    // LOG_INFO("输入运算符>> 重载");
    // is >> rhs._real;
    input_int_num(is, rhs._real);
    // is >> rhs._imag;
    input_int_num(is, rhs._imag);

    return is;
}

void test1()
{
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex c3 = c1 + c2;
    cout << "c3 = " << c3 << endl; // operator<<(cout, c3); /*本质*/

    ++c3; // c3.operator++();    /*本质*/
    c3++; // c3.operator++(int); /*本质*/

    cout << "After ++, c3 = " << c3 << endl;

    Complex c4(0, 0);
    cin >> c4; // operator>>(cin, c4); /*本质*/
    cout << "c4 = " << c4 << endl;
}

int main()
{
    LOG_INIT();
    // LOG_INIT_APPEND();
    test1();

    return 0;
    LOG_CLEANUP();
}

```

[std::string的底层实现]
基本上有三种方式：
- Eager Copy(深拷贝) --> 在不需要改变字符串内容时，对字符串进行频繁复制，效率比较低下
- COW（Copy-On-Write 写时复制）
- SSO(Short String Optimization 短字符串优化)
    目前std::string是根据SSO的思想实现的，
    当字符串的字符数小于等于15时，buffer直接存放整个字符串；
    当字符串的字符数大于15时buffer 存放的就是一个指针，指向堆空间的区域。
    这样做的好处是，当字符串较小时，直接拷贝字符串，放在 string内部，不用获取堆空间，开销小。