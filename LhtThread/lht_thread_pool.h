#ifndef LHTTHREADPOOL_H
#define LHTTHREADPOOL_H

#include <QObject>
#include <QThreadPool>
#include <QRunnable>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include "LhtLog/QsLog/QsLog.h"

class LhtThreadPool : public QObject
{
    Q_OBJECT
public:

    static LhtThreadPool* instance(){
        return m_instance;
    }

    explicit LhtThreadPool(QObject *parent = nullptr);

    ~LhtThreadPool();

    void addWorker(QRunnable * work);

    bool deleteWorker(QRunnable * work);
signals:

private:
    int                     m_threadMaxCount;
    QThreadPool             m_pool;
    static LhtThreadPool *  m_instance;
};

class LhtThreadWorker : public QObject, public QRunnable
{
    QQueue<QByteArray> qqByteArr;  // 队列数组

    LhtThreadWorker(QObject * parent = 0)
    {
        containerLen = 1000;
        stopped = true;
        qqByteArr.clear();
    }

    ~LhtThreadWorker(){
        stopped = true;
        queueWait.wakeOne();
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
        LhtThreadPool::instance()->deleteWorker(this);
    } //线程停止
    virtual void init(){
        LhtThreadPool::instance()->addWorker(this);
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

class Move2ThBasicWorker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Move2ThBasicWorker()
    {
        m_workerThread = new QThread;
    }

    virtual ~Move2ThBasicWorker()
    {
        if (m_workerThread != nullptr)
        {
            delete m_workerThread;
        }
    }

    virtual QString name() = 0;
    QString lastError() {return m_lastError;}

protected:
    QString m_lastError;
    QThread *m_workerThread = nullptr;

public Q_SLOTS:
    virtual bool Init()
    {
        if (m_workerThread != nullptr)
        {
            this->moveToThread(m_workerThread);
             LhtThreadPool::instance()->addWorker(this);
//            m_workerThread->start();
        }

        return true;
    }

    virtual bool UnInit()
    {

        if (m_workerThread != nullptr && m_workerThread->isRunning())
        {
            m_workerThread->quit();
            m_workerThread->wait();
        }

        if (m_workerThread != nullptr)
        {
            delete m_workerThread;
            m_workerThread = nullptr;
        }
        LhtThreadPool::instance()->deleteWorker(this);
        return true;
    }


};


#endif // LHTTHREADPOOL_H
