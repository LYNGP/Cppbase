#include "cplusplus.hpp"

using std::cout;
using std::endl;

int main(int argc, const char* argv[]); // 函数声明

// 全局变量 - 存储在全局/静态区（数据段）
int globalVar = 100;

// 静态全局变量 - 存储在全局/静态区（数据段）
static int staticGlobalVar = 200;

// 常量字符串 - 存储在文字常量区（只读段）
const char* globalStr = "Hello, World!";

void test0(){
    // 局部变量 - 存储在栈区
    int localVar = 300;
    
    // 静态局部变量 - 存储在全局/静态区（数据段）
    static int staticLocalVar = 400;
    
    // 字符串常量 - 存储在文字常量区（只读段）
    const char* localStr = "Local String";
    
    // 动态分配内存 - 存储在堆区
    int* heapVar = new int(500);
    
    // 打印各种变量的地址来观察内存布局
    cout << "=== 内存布局演示 ===" << endl;
    cout << "栈区变量地址：" << endl;
    cout << "  localVar address:     " << &localVar << endl;
    
    cout << "\n堆区变量地址：" << endl;
    cout << "  heapVar points to:    " << heapVar << endl;
    
    cout << "\n全局/静态区变量地址：" << endl;
    cout << "  globalVar address:    " << &globalVar << endl;
    cout << "  staticGlobalVar addr: " << &staticGlobalVar << endl;
    cout << "  staticLocalVar addr:  " << &staticLocalVar << endl;
    
    cout << "\n文字常量区地址：" << endl;
    cout << "  globalStr points to:  " << (void*)globalStr << endl;
    cout << "  localStr points to:   " << (void*)localStr << endl;
    
    cout << "\n程序代码区地址：" << endl;
    cout << "  test0 function addr:  " << (void*)test0 << endl;
    cout << "  main function addr:   " << (void*)main << endl;
    
    // 记得释放动态分配的内存
    delete heapVar;
}

int main(int argc, const char* argv[]) {
    cout << "命令行参数地址(栈区): " << argv << endl;
    test0();
    return 0;
}
