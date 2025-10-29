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
int main()
{
    test0();
    cout << "#-------------------------#" << endl;
    test1();
    cout << "#-------------------------#" << endl;
    test2();
    cout << "#-------------------------#" << endl;
    test3();
    return 0;
}