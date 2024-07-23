#ifndef LOCKLESS_THREAD_POOL_H
#define LOCKLESS_THREAD_POOL_H
#include <QThreadPool>
#include <Windows.h>

/**
 * @brief 无锁线程基类，消息处理器仓库，管理线程
 * @param Handler 具体的操作
 */

//如果需要取数据包头的话用这个
struct pkt_bufferCache
{
    struct pcap_pkthdr *header;//数据包信息
    uint32_t len;
    char *pkt_data;//数据包内容
    struct pkt_bufferCache *next;//下一个缓存
};

struct LhtBufferCache
{
    uint32_t len;
    char *pkt_data = nullptr;//解包后的数据包内容
    LhtBufferCache* next;//下一个缓存
};

class LhtLocklessThreadPool : public QObject
{
    Q_OBJECT
public:

    static LhtLocklessThreadPool* instance(){
        return m_instance;
    }

    explicit LhtLocklessThreadPool(QObject *parent = nullptr);

    ~LhtLocklessThreadPool();

    void addWorker(QRunnable * work);

    bool deleteWorker(QRunnable * work);
signals:

private:
    int                     m_threadMaxCount;
    QThreadPool             m_pool;
    static LhtLocklessThreadPool *  m_instance;
};

class LocklessDataCache
{
public:
    LocklessDataCache();

    void recv(char *data,uint32_t len);
    //缓存在函数内释放，需预先申请指针空间
    bool readData(char *buffer, uint32_t &nbyte);
    //缓存由调用方释放无拷贝过程
    bool readDataZeroCopy(LhtBufferCache**);

    void clearBuffer();

    void setPoolLen(uint32_t nLen);

    int getCurrentSize(){
        return m_currentSize;
    }
protected:

private:
    //清空数据的时候用
    uint32_t poolSize = 1000;
    std::atomic_int m_currentSize = 0;
    LhtBufferCache* m_buffer_rd;//数据包链表，写盘进程读指针
    LhtBufferCache* m_buffer_wr;//数据包链表，收到的包，网卡接收写指针
};

/**
 * @class LocklessThread
 * @brief 无锁线程基类，高效的事件驱动线程。
 *
 * 该类使用两个指针一个用于接收数据时的写入m_buffer_wr指针位于链表最后一位
 * m_buffer_rd指针位于未处理的数据第一位用处handleData处理数据
 *
 * @note 内部存在两种数据处理的方法  开关为m_useZeroCopy是否启用0拷贝
 *
 * @version 1.0
 * @date 2024-07-15
 *
 * @author leehuitao
 */

class LocklessThread : public QObject, public QRunnable
{
public:
    LocklessThread(QObject *parent=0):QObject(parent)
    {
        containerLen = 1000;
        packLen = 1296;
        stopped = true;
    }

    ~LocklessThread(){
        stopped = true;
    }

    void recv(char* buf,int len){
        m_lhtBufferCache.recv(buf,len);
    } // 接收数据并缓存

    virtual void stop()
    {
        stopped = true;
        LhtLocklessThreadPool::instance()->deleteWorker(this);
    } //线程停止
    __declspec(deprecated("需要预先设置pack len否则无法启动读线程"))
    virtual void init(){
        if(stopped){
            LhtLocklessThreadPool::instance()->addWorker(this);
        }
    }

    //缓存的最大链表个数
    void setPoolLen(unsigned int nLen){
        containerLen = nLen;
        m_lhtBufferCache.setPoolLen(nLen);}
    //设置每个包大小
    void setPackLen(unsigned int nLen){packLen = nLen;}
    //设置每个包大小
    void setUseZeroCopy(bool use){m_useZeroCopy = use;}

    int currentSize() {return m_lhtBufferCache.getCurrentSize();}

    void clearDataBuf(){
        m_lhtBufferCache.clearBuffer();
    }

protected:
    void run()
    {
        if(packLen == -1 && (m_useZeroCopy == false)){
            return;
        }
        char *data;
        if(m_useZeroCopy == false){
            data = new char[packLen];
        }
        uint32_t len;
        LhtBufferCache* p_pkt_bufferNow = new LhtBufferCache;
        stopped = false;
        while(1) {
            if(m_useZeroCopy){
                if(!m_lhtBufferCache.readDataZeroCopy(&p_pkt_bufferNow)){
                    Sleep(1);
                }else{
                    handleData(p_pkt_bufferNow->pkt_data,p_pkt_bufferNow->len);
                    delete []p_pkt_bufferNow->pkt_data;
                    p_pkt_bufferNow->pkt_data = nullptr;
                    delete p_pkt_bufferNow;
                }
            }else{
                if(!m_lhtBufferCache.readData(data,len)){
                    Sleep(1);
                }else{
                    handleData(data,len);
                }
            }

            if (stopped)
            {
                break;
            }
        }
    }
    // 线程

    virtual bool handleData(char* buf,int len)=0; // 处理队列中数据数据

private:
    LocklessDataCache m_lhtBufferCache;

    unsigned int containerLen;

    unsigned int packLen;

    volatile bool stopped;

    bool m_useZeroCopy = 1;

};


#endif // LOCKLESS_THREAD_POOL_H
