// 线程不安全版本
#include <iostream>
#include <mutex>
using std::mutex;
using std::unique_lock;
class Singleton{
public:
    static Singleton *getInstance() {
        if(m_instance == nullptr) {
            m_instance = new Singleton();
        }
        return m_instance;
    }
    Singleton();
private:
    // Singleton();
    Singleton(const Singleton& other);
    Singleton& operator=(const Singleton &other);
    static Singleton* m_instance; 
};
// 线程不安全原因：
// m_instance = new Singleton(); 
// 1. 分配了一个Singleton类型对象所需要的内存
// 2. 在分配的内存处构造Singleton类型的对象
// 3. 把分配的内存的地址交给m_instance
// 这三个步骤是按照顺序执行的，但实际上只能确定步骤一是最先执行的，步骤23不一定
// 即某个线程A，在调用了1，3，2的顺序，那么刚刚执行完步骤3给Singleton类型分配到了线程B （此时 m_instance已经不是nullptr了）
// 所以线程B会直接执行return m_instance得到一个对象，而此时对象并没有被构造


// 加锁保证线程安全
mutex mu;
static Singleton* m_instance;
static Singleton *getInstance_with_lock() {
    if(m_instance == nullptr) {
            unique_lock<mutex> locker(mu);
            m_instance = new Singleton();
        }
        return m_instance;
}
// ps: 第二次判断m_instance是否为空的原因：防止线程A执行到加锁之前，切换到线程B完成了单例的构造
//     正常获得锁之后，保证不二次重新构造该对象，一面构造中其他线程对该资源的访问

// 借助static的优美实现
static Singleton& getInstance_with_static() {
    static Singleton m_instance; // 局部静态变量
    return m_instance;
}
// 局部静态变量不仅只会初始化一次，而且还是线程安全

//借助once_call实现
static Singleton* getInstance_with_oncecall() {
    static std::once_flag flag;
    std::call_once(flag, [] {
        m_instance = new Singleton();
    });
    return m_instance;
}
// once_call保证多个线程对函数只调用一次