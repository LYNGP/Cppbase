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

## cppbase day03：
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
    // 增强for循环遍历 **
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