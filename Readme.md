### Cppbase

#### 1. fmt/format.h
格式化输出库，可以格式化输出各种类型的数据，包括字符串、数字、指针、结构体、类等。
但是不能格式化输出一个非 void 指针
```log
输出指针指向的值（解引用）：fmt::print("指针指向的值: {}\n", *ptr);    // 输出 ptr 指向的值
输出指针地址：fmt::print("指针地址: {}\n",static_cast<void*>(ptr));  // 输出 ptr 的地址
```


#### 2. 命名空间
命名空间就是一个可以由用户自己定义的作用域，在不同的作用域中可以定义相同名字的变量，互不干扰，系统能够区分它们。
使用方法：
```C++
using namespace std; //using编译指令

using std::cout;
using std::endl;
```
需要哪个实体的时候就引入到程序中，不需要的实体就不引入，可以尽可能减小犯错误的概率。

#### 3. const常量 - 必须初始化
[const常量和宏定义常量的区别]
1. 发生的时机不同：
C语言中的宏定义发生时机在预处理时，做字符串的替换；
const常量是在编译时（const常量本质还是一个变量，只是用const关键字限定之后，赋予只读属性，使用时依然是以变量的形式去使用）
2. 类型和安全检查不同：
宏定义没有类型，不做任何类型检查；
const常量有具体的类型，在编译期会执行类型检查。

[修饰指针类型*]

```C++
int number1 = 10;
int number2 = 20;

const int * p1 = &number1;//常量指针
*p1 = 100;//error 通过p1指针无法修改其所指内容的值
p1 = &numbers;//ok 可以改变p1指针的指向
int const * p2 = &number1; //常量指针的第二种写法

int * const p3 = &number1;//指针常量
*p3 = 100;//ok 通过p3指针可以修改其所指内容的值
p3 = &number2;//error 不可以改变p1指针的指向
const int * const p4 = &number1;//两者皆不能进行修改
```

#### 4. C/C++申请、释放堆空间的方式对比

```bash
# vim ~/.bashrc
# source ~/.bashrc 
# alias memcheck='valgrind --tool=memcheck --leak-check=full --show-reachable=yes'

valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./bin/4_malloc
memcheck ./bin/4_malloc 
```

```log
==816204== Memcheck, a memory error detector
==816204== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==816204== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==816204== Command: ./bin/4_malloc
==816204== 
10
20
==816204== 
==816204== HEAP SUMMARY:
==816204==     in use at exit: 4 bytes in 1 blocks
==816204==   total heap usage: 4 allocs, 3 frees, 73,736 bytes allocated
==816204== 
==816204== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==816204==    at 0x48657B8: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==816204==    by 0x108B03: test1() (4_malloc.cc:15)
==816204==    by 0x108B5F: main (4_malloc.cc:23)
==816204== 
==816204== LEAK SUMMARY:
==816204==    definitely lost: 4 bytes in 1 blocks
==816204==    indirectly lost: 0 bytes in 0 blocks
==816204==      possibly lost: 0 bytes in 0 blocks
==816204==    still reachable: 0 bytes in 0 blocks
==816204==         suppressed: 0 bytes in 0 blocks
==816204== 
==816204== For lists of detected and suppressed errors, rerun with: -s
==816204== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

[malloc/free和new/delete的区别]
1. malloc/free是库函数；new/delete是表达式，后两者使用时不是函数的写法；
2. new表达式的返回值是相应类型的指针，malloc返回值是void*；
3. malloc申请的空间不会进行初始化，获取到的空间是有脏数据的，但new表达式申请空间时可以直接初始化；
4. malloc的参数是字节数，new表达式不需要传递字节数，会根据相应类型自动获取空间大小。

C++11之后使用nullptr表示空指针
```C++
int* p = nullptr;
```