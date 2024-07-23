#include "lockless_thread_pool.h"
#include <LhtLog/QsLog/QsLog.h>
LocklessDataCache::LocklessDataCache() {

}

void LocklessDataCache::recv(char *data, uint32_t len)
{
    if(m_currentSize > poolSize)//来不及的话跳过
        return;
    // 存储数据包到缓存
    LhtBufferCache* p_pkt_bufferNow = (new LhtBufferCache);
    p_pkt_bufferNow->len = len;
    p_pkt_bufferNow->pkt_data = new char[len];
    memcpy(p_pkt_bufferNow->pkt_data, data, len);//复制数据包
    p_pkt_bufferNow->next = NULL;

    if (m_buffer_wr == NULL)//如果写入指针是空的
        m_buffer_rd = p_pkt_bufferNow;//读指针
    else
        m_buffer_wr->next = p_pkt_bufferNow;//如果不是空的next指针赋值
    m_buffer_wr = p_pkt_bufferNow;//移动指针指向当前包，用于下一次写入数据的时候用
    m_currentSize ++;
}

bool LocklessDataCache::readData(char *buffer, uint32_t& nbyte)
{
    if (m_buffer_rd == m_buffer_wr)//等待数据写入
    {
        return false;
    }

    memcpy(buffer,m_buffer_rd->pkt_data,m_buffer_rd->len);
    nbyte = m_buffer_rd->len;
    // 读指针移动到下一个包
    auto *p_pkt_now = m_buffer_rd;
    m_buffer_rd = p_pkt_now->next;
    m_currentSize --;
    // 清当前包缓存
    delete []p_pkt_now->pkt_data;
    delete p_pkt_now;
    p_pkt_now = nullptr;//清除
    return true;
}

bool LocklessDataCache::readDataZeroCopy(LhtBufferCache ** ret)
{
    if (m_buffer_rd == m_buffer_wr)//等待数据写入
    {
        return false;
    }
    *ret = m_buffer_rd;
    // 读指针移动到下一个包
    m_buffer_rd = m_buffer_rd->next;
    m_currentSize--;
    return true;
}

void LocklessDataCache::clearBuffer()
{
    while(m_buffer_rd != m_buffer_wr){
        // 读指针移动到下一个包
        auto *p_pkt_now = m_buffer_rd;
        m_buffer_rd = p_pkt_now->next;
        // 清当前包缓存
        delete []p_pkt_now->pkt_data;
        delete p_pkt_now;
        p_pkt_now = nullptr;//清除
    }
    m_currentSize =0;
}

void LocklessDataCache::setPoolLen(uint32_t nLen)
{
    poolSize = nLen;
}

LhtLocklessThreadPool::LhtLocklessThreadPool(QObject *parent)
{
    m_threadMaxCount = QThread::idealThreadCount();
    m_pool.setMaxThreadCount(m_threadMaxCount);
    QLOG_INFO()<< "thread pool max count : "<<m_threadMaxCount;
}

LhtLocklessThreadPool::~LhtLocklessThreadPool()
{
    m_pool.waitForDone(); // 等待所有任务完成
    m_pool.clear(); // 获取正在运行的任务
}

void LhtLocklessThreadPool::addWorker(QRunnable *work)
{
    m_pool.start(work);
}

bool LhtLocklessThreadPool::deleteWorker(QRunnable *work)
{
    auto ret = m_pool.tryTake(work);
    return  ret;
}
