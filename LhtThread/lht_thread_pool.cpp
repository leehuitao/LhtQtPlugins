#include "lht_thread_pool.h"

LhtThreadPool * LhtThreadPool::m_instance = new LhtThreadPool;

LhtThreadPool::LhtThreadPool(QObject *parent) : QObject(parent)
{
    m_threadMaxCount = QThread::idealThreadCount();
    m_pool.setMaxThreadCount(m_threadMaxCount);
    QLOG_INFO()<< "thread pool max count : "<<m_threadMaxCount;
}

LhtThreadPool::~LhtThreadPool()
{
    m_pool.waitForDone(); // 等待所有任务完成
    m_pool.clear(); // 获取正在运行的任务
}

void LhtThreadPool::addWorker(QRunnable *work)
{
    m_pool.start(work);
}

bool LhtThreadPool::deleteWorker(QRunnable *work)
{
    auto ret = m_pool.tryTake(work);
    return  ret;
}
