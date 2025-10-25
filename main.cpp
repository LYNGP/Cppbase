#include "cplusplus.hpp"
#include "computer.hpp"
#include "log.hpp"  // 新增日志系统

using std::cout;
using std::endl;

void test0()
{
    // 获取日志实例
    auto& logger = ModernLogger::getInstance();
    
    logger.info("开始测试 Computer 类");
    
    Computer pc("xiaomi", 10000);
    pc.print();
    logger.info("创建了第一个 Computer 对象：xiaomi");
    
    Computer pc2(pc);
    pc2.print();
    logger.info("通过拷贝构造创建了第二个 Computer 对象");
    
    Computer pc3 = pc;
    pc3.print();
    logger.info("通过拷贝赋值创建了第三个 Computer 对象");
    
    logger.info("Computer 类测试完成");
}

class E
{
    double _e;
    char _eArr[20];
    int _e2;
    double _e1;
};

int main()
{
    // 在程序开始时记录启动信息
    auto& logger = ModernLogger::getInstance();
    logger.info("程序启动");
    
    try {
        test0();
        
        // 你可以在任何地方使用日志
        logger.info("sizeof(E) = " + std::to_string(sizeof(E)));
        
    } catch (const std::exception& e) {
        logger.error("程序异常：" + std::string(e.what()));
    }
    
    logger.info("程序正常结束");
    return 0;
}
