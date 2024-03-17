#include "thread_pool_basic.h"
#include <QDebug>
ThreadPoolBasic::ThreadPoolBasic(QObject *parent, int type):QThread(parent),m_type(type)
{
    m_poolSize = DEFAULT_POOL_SIZE;
    m_stoped = true;
    m_dataQueue.clear();
}

ThreadPoolBasic::~ThreadPoolBasic()
{
    m_stoped = true;
    m_waitCondition.wakeOne();
    quit();
    wait();
    m_stoped = true;
}

bool ThreadPoolBasic::recvData(GrpcRequestBufferPtr data, QString stream)
{
    QMutexLocker lock(&m_dataMutex);
    if(static_cast<unsigned>(m_dataQueue.size()) > m_poolSize){
        //QLOG_ERROR()<<"Queue out of size ";
        return false;
    }else{
        m_dataQueue.append(std::make_pair(data,stream));
        m_waitCondition.wakeOne();
        return true;
    }
}


void ThreadPoolBasic::startRun()
{
    if(m_stoped)
        start();
}

void ThreadPoolBasic::setPoolSize(unsigned size)
{
    m_poolSize = size;
}

void ThreadPoolBasic::stopRun()
{
    m_stoped = true;
    m_waitCondition.wakeOne();

    quit();
    wait();
}

void ThreadPoolBasic::setParseType(int type)
{
    QMutexLocker lock(&m_dataMutex);
    m_parseType =   type;
}

void ThreadPoolBasic::run()
{
    m_dataQueue.clear();
    m_stoped = false;

    while(1){
        QMutexLocker lock(&m_dataMutex);
        if(m_dataQueue.isEmpty())
            m_waitCondition.wait(&m_dataMutex);
        else{
            auto data = m_dataQueue.takeFirst();
            lock.unlock();
            handleData(data);
        }

        if(m_stoped){
            break;
        }
    }


}
