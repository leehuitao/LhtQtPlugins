#ifndef THREADPOOLBASIC_H
#define THREADPOOLBASIC_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QQueue>
#include <QWaitCondition>
#include "../NetIO/server/handleRepository/RegisterHandler.h"
#define DEFAULT_POOL_SIZE 1000
/*
    使用方法示例：
    网络数据传入客户端，需要按照指令分发指令，指令中包含耗时操作使用此方法很方便
    ，startRun后由recv接收数据即可
*/

class ThreadPoolBasic:public QThread
{
    Q_OBJECT
public:
    ThreadPoolBasic(QObject * parent = 0,int type = 0);

    ~ThreadPoolBasic();

    bool recvData(GrpcRequestBufferPtr data , QString);

    void startRun();

    void setPoolSize(unsigned size);

    void stopRun();

    void setParseType(int);
protected:

    void run() override;
    //子类重新实现一下自己需要的处理方法
    virtual void handleData( std::pair<GrpcRequestBufferPtr,QString>) = 0;
private:
    //线程锁
    QMutex                  m_dataMutex;
    //无数据时暂停线程，新数据进入时唤醒线程
    QWaitCondition          m_waitCondition;
    //数据队列最大长度
    unsigned                m_poolSize;
    //数据队列
    QQueue<std::pair<GrpcRequestBufferPtr,QString>>      m_dataQueue;

    volatile bool           m_stoped;
    // 0表示解析 1表示数据库
    int                     m_type;
    int                     m_parseType;
};

#endif // THREADPOOLBASIC_H
