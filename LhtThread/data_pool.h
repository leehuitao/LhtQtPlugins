#ifndef DATA_POOL_H
#define DATA_POOL_H
#include <QThread>
#include <QMutex>
#include <QString>
#include <QWaitCondition>
#include <QDebug>
#include <tuple>
#include <QQueue>


/**
 * @date 2024-02-29
 * @brief 一个简单的事件驱动线程基类，继承后实现handleData来处理数据即可，类型不同的话修改他的recv  和  handleData 即可
 * @author leehuitao
 */

class DataPool : public QThread
{
public:

    QQueue<QByteArray> qqByteArr;  // 队列数组

    DataPool(QObject *parent=0):QThread(parent)
    {
        containerLen = 1000;
        stopped = true;
        qqByteArr.clear();
    }

    ~DataPool(){
        stopped = true;
        queueWait.wakeOne();

        quit();
        wait(100);
        stopped = true;
    }

    bool recv(const QByteArray bt){

        bool ret = true;
        QMutexLocker locker(&mutex); // 锁定队列对象，禁止同时操作
        if(qqByteArr.size() >containerLen)
        { // 当队列大于限定值时，
    //		qqByteArr.removeFirst();
            ret = false;
        }
        else
        {
            qqByteArr.enqueue(bt); // 插入指针到队列尾部
            queueWait.wakeOne(); // 唤醒睡着中的线程
        }
        return ret;
    }// 接收数据并缓存

    bool recv(unsigned char* buf,int len){

        bool ret = true;
        QMutexLocker locker(&mutex); // 锁定队列对象，禁止同时操作
        if(qqByteArr.size() >containerLen)
        { // 当队列大于限定值时，
            qqByteArr.removeFirst();
            qDebug()<<__FUNCTION__<<__LINE__;
            ret = false;
        }
        else
        {
            QByteArray bt((char*)buf,len);

            qqByteArr.append(bt); // 插入指针到队列尾部
            queueWait.wakeOne(); // 唤醒睡着中的线程
        }
        return ret;
    } // 接收数据并缓存

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
    int currentSize() {return qqByteArr.length();}

    void clearDataBuf(){
        QMutexLocker locker(&mutex);
        qqByteArr.clear();
    }

protected:
    void run()
    {
        //qqByteArr.clear();
        stopped = false;
        while(1) {

            QMutexLocker locker(&mutex);
            if(qqByteArr.isEmpty())
            {
                queueWait.wait(&mutex);
            }
            else
            {
                QByteArray byteArrFirst = qqByteArr.takeFirst();
                locker.unlock();
                handleData((unsigned char*)byteArrFirst.data(),byteArrFirst.size());

            }

            if (stopped)
            {
                break;
            }
        }
    }
 // 线程

    virtual bool handleData(unsigned char* buf,int len)=0; // 处理队列中数据数据

private:
    QMutex mutex;
    QWaitCondition queueWait;


    unsigned int containerLen;

    volatile bool stopped;

};


#endif // DATA_POOL_H
