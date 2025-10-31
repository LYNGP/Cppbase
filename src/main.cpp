#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

using namespace std;

class CoffeeShop {
private:
    // 🔒 私有构造函数 - "店面设计图只有老板知道"
    CoffeeShop() {
        cout << "☕ 咖啡店开业了！地址：" << this << endl;
    }
    
    // 🚫 禁止拷贝和赋值 - "不能克隆咖啡店"
    CoffeeShop(const CoffeeShop&) = delete;
    CoffeeShop& operator=(const CoffeeShop&) = delete;

public:
    // 🏪 获取唯一实例的入口
    static shared_ptr<CoffeeShop> getInstance() {
        // 🔐 线程安全的懒汉式单例（C++11的magic static）
        static shared_ptr<CoffeeShop> instance(nullptr);
        static once_flag created;
        
        call_once(created, []() {
            // 🎯 使用私有构造函数的技巧
            instance = shared_ptr<CoffeeShop>(new CoffeeShop());
        });
        
        return instance;
    }
    
    // 🍰 咖啡店的业务功能
    void serveCoffee(const string& customer) {
        cout << "🍰 为 " << customer << " 制作咖啡..." << endl;
    }
    
    void showInfo() {
        cout << "📍 咖啡店地址：" << this << endl;
    }
    
    // 📢 析构函数 - "咖啡店关门清理"
    ~CoffeeShop() {
        cout << "🚪 咖啡店关门了，自动清理完成！" << endl;
    }
};


void testSingleton() {
    cout << "\n=== 🧪 单例模式测试 ===" << endl;
    
    // 🏪 第一个客户获取咖啡店
    auto shop1 = CoffeeShop::getInstance();
    shop1->serveCoffee("小明");
    shop1->showInfo();
    
    // 🏪 第二个客户获取咖啡店
    auto shop2 = CoffeeShop::getInstance();
    shop2->serveCoffee("小红");
    shop2->showInfo();
    
    // 🎯 验证是否是同一家店
    if (shop1 == shop2) {
        cout << "✅ 确认：全世界只有一家咖啡店！" << endl;
    }
    
    cout << "引用计数：" << shop1.use_count() << endl;
}

void testMultiThread() {
    cout << "\n=== 🧵 多线程安全测试 ===" << endl;
    
    auto worker = []() {
        auto shop = CoffeeShop::getInstance();
        shop->serveCoffee("线程客户");
        shop->showInfo();
    };
    
    thread t1(worker);
    thread t2(worker);
    thread t3(worker);
    
    t1.join();
    t2.join();
    t3.join();
}

int main() {
    testSingleton();
    testMultiThread();
    
    cout << "\n🎯 程序结束，观察智能指针自动回收..." << endl;
    return 0;
    // 💫 程序结束时，shared_ptr自动释放，调用析构函数
}
