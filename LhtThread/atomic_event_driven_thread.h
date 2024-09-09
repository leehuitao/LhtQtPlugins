#ifndef ATOMIC_EVENT_DRIVEN_THREAD_H
#define ATOMIC_EVENT_DRIVEN_THREAD_H

#include <QThread>
#include <QMutex>
#include <QString>
#include <QWaitCondition>
#include <QDebug>
#include <tuple>
#include <QQueue>

/**
 * @date 2024-09-09
 * @warning "如果你要继承这个类请不要在类中添加 Q_OBJECT 宏，这将会导致无法编译"
 * " 或者使用更简单的 data_pool.h"
 * 依靠于C++20的原子智能指针优化原先的锁同步
 * 一个简单的事件驱动线程基类，继承后实现handleData来处理数据即可，他可以满足任何类型的参数调用，示例在lht_examples.h中可以查看
 * @author leehuitao
 */

template<typename... Args>
class AtomicEventDrivenPool : public QThread
{
public:
    // 使用原子智能指针存储任务队列
    std::atomic<std::shared_ptr<std::vector<std::tuple<Args...>>>> atomicQueue;

    AtomicEventDrivenPool(QObject *parent = nullptr) : QThread(parent)
    {
        containerLen = 1000;
        stopped = true;
        atomicQueue = std::make_shared<std::vector<std::tuple<Args...>>>(); // 初始化
    }

    ~AtomicEventDrivenPool(){
        stopped = true;
        queueWait.wakeOne();
        quit();
        wait(100);
    }

    bool recv(Args... args){
        auto newQueue = std::make_shared<std::vector<std::tuple<Args...>>>();
        auto oldQueue = atomicQueue.load();

        if (oldQueue->size() > containerLen) {
            return false;  // 队列超限，拒绝添加
        }

        *newQueue = *oldQueue;  // 拷贝现有队列
        newQueue->emplace_back(std::make_tuple(args...));  // 添加新任务

        // 原子替换队列指针
        while (!atomicQueue.compare_exchange_weak(oldQueue, newQueue)) {
            newQueue->clear();
            *newQueue = *oldQueue;
            newQueue->emplace_back(std::make_tuple(args...));
        }

        queueWait.wakeOne();  // 唤醒等待的线程
        return true;
    }

    virtual void stop()
    {
        stopped = true;
        queueWait.wakeOne();
        quit();
        wait(100);
    }

    virtual void init(){
        if(stopped){
            start();
        }
    }

    void setPoolLen(unsigned int nLen) { containerLen = nLen; }
    int currentSize() { return atomicQueue.load()->size(); }

protected:
    void run()
    {
        stopped = false;

        while (!stopped) {
            std::shared_ptr<std::vector<std::tuple<Args...>>> localQueue;

            // 等待任务到达
            {
                localQueue = atomicQueue.load();
                if (localQueue->empty()) {
                    sleep(100);
                    continue;  // 队列为空时继续等待
                }
            }

            // 处理任务队列
            while (!localQueue->empty()) {
                auto args = localQueue->front();
                handleData(args);
                localQueue->erase(localQueue->begin());  // 从队列中移除任务

                if (stopped) break;  // 若线程停止，立即退出
            }
        }
    }

    virtual void handleData(std::tuple<Args...> &args) = 0;  // 子类实现处理数据的逻辑

private:
    QWaitCondition queueWait;

    unsigned int containerLen;
    volatile bool stopped;
};


#endif // ATOMIC_EVENT_DRIVEN_THREAD_H
