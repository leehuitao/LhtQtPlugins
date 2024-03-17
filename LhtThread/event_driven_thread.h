#ifndef EVENT_DRIVEN_THREAD_H
#define EVENT_DRIVEN_THREAD_H

#include <QThread>
#include <QMutex>
#include <QString>
#include <QWaitCondition>
#include <QDebug>
#include <tuple>
#include <QQueue>

/**
 * @date 2024-02-29
 * @warning "如果你要继承这个类请不要在类中添加 Q_OBJECT 宏，这将会导致无法编译"
 * " 或者使用更简单的 data_pool.h"
 * 一个简单的事件驱动线程基类，继承后实现handleData来处理数据即可，他可以满足任何类型的参数调用，示例在lht_examples.h中可以查看
 * @author leehuitao
 */

template<typename... Args>
class EventDrivenPool : public QThread
{
public:

    QQueue<std::tuple<Args...>> qqArgs; // 存储输入参数

    EventDrivenPool(QObject *parent=0):QThread(parent)
    {
        containerLen = 1000;
        stopped = true;
        qqArgs.clear();
    }

    ~EventDrivenPool(){
        stopped = true;
        queueWait.wakeOne();

        quit();
        wait(100);
        stopped = true;
    }

    bool recv(Args... args){
        bool ret = true;
        QMutexLocker locker(&mutex); // 锁定队列对象，禁止同时操作
        if(qqArgs.size() > containerLen)
        { // 当队列大于限定值时，
            ret = false;
        }
        else
        {
            qqArgs.enqueue(std::make_tuple(args...)); // 存储输入参数
            queueWait.wakeOne(); // 唤醒睡着中的线程
        }
        return ret;
    }// 接收数据并缓存

    virtual void stop()
    {
        stopped = true;
        queueWait.wakeOne();

        quit();
        wait(100);
    } //线程停止
    virtual void init(){
        if(stopped){
            start();
        }
    }

    void setPoolLen(unsigned int nLen){containerLen = nLen;}
    int currentSize() {return qqArgs.length();}

    void clearDataBuf(){
        QMutexLocker locker(&mutex);
        qqArgs.clear();
    }

protected:
    void run()
    {
        //qqArgs.clear();
        stopped = false;
        while(1) {

            QMutexLocker locker(&mutex);
            if(qqArgs.isEmpty())
            {
                queueWait.wait(&mutex);
            }
            else
            {
                auto args = qqArgs.takeFirst();
                locker.unlock();
                handleData(args);

            }

            if (stopped)
            {
                break;
            }
        }
    }
    // 线程

    virtual void handleData(std::tuple<Args...> &args) = 0; // 处理队列中数据数据

private:
    QMutex mutex;
    QWaitCondition queueWait;


    unsigned int containerLen;

    volatile bool stopped;

};

#endif // EVENT_DRIVEN_THREAD_H
