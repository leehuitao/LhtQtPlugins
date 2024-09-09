#ifndef CICULAR_BUFFER_DATA_POOL_H
#define CICULAR_BUFFER_DATA_POOL_H
#include <QThread>
#include <QMutex>
#include <QString>
#include <QDebug>
#include <QQueue>


/**
 * @date 2024-02-29
 * @brief 一个简单的事件驱动线程基类，继承后实现handleData来处理数据即可，类型不同的话修改他的recv  和  handleData 即可
 * @author leehuitao
 */

class CicularBufferDataPool : public QThread
{
public:
    CicularBufferDataPool(QObject* parent = nullptr)
        : QThread(parent), containerLen(1e5), readIndex(0), writeIndex(0), stopped(true)
    {
        buffer.resize(containerLen);
    }

    ~CicularBufferDataPool()
    {
        stop();
    }

    bool recv(const QByteArray& bt)
    {
        if (isBufferFull())
        {
            return false;  // 缓冲区满时拒绝新数据
        }

        buffer[writeIndex % containerLen] = bt;  // 写入数据到环形缓冲区
        writeIndex.fetch_add(1, std::memory_order_release);  // 更新写入指针
        return true;
    }

    bool recv(unsigned char* buf, int len)
    {
        if (isBufferFull())
        {
            return false;  // 缓冲区满时拒绝新数据
        }

        QByteArray bt(reinterpret_cast<char*>(buf), len);
        buffer[writeIndex % containerLen] = bt;  // 写入数据
        writeIndex.fetch_add(1, std::memory_order_release);  // 更新写入指针
        return true;
    }

    virtual void stop()
    {
        stopped = true;
        quit();
        wait(100);
    }

    virtual void init()
    {
        if (stopped)
        {
            stopped = false;
            start();
        }
    }

    void setPoolLen(unsigned int nLen)
    {
        containerLen = nLen;
        buffer.resize(containerLen);
    }

    int currentSize()
    {
        return writeIndex.load(std::memory_order_acquire) - readIndex.load(std::memory_order_acquire);
    }

    void clearDataBuf()
    {
        readIndex.store(0, std::memory_order_release);
        writeIndex.store(0, std::memory_order_release);
    }

protected:
    void run()
    {
        while (!stopped)
        {
            if (isBufferEmpty())
            {
                sleep(100);
                continue;
            }

            QByteArray byteArrFirst = buffer[readIndex % containerLen];
            readIndex.fetch_add(1, std::memory_order_release);  // 更新读取指针

            handleData(reinterpret_cast<unsigned char*>(byteArrFirst.data()), byteArrFirst.size());
        }
    }

    virtual bool handleData(unsigned char* buf, int len) = 0;  // 处理数据

private:
    std::vector<QByteArray> buffer;  // 环形缓冲区
    unsigned int containerLen;  // 缓冲区大小
    std::atomic<size_t> readIndex;  // 环形缓冲区的读取指针
    std::atomic<size_t> writeIndex;  // 环形缓冲区的写入指针
    volatile bool stopped;

    bool isBufferFull() const
    {
        return (writeIndex.load(std::memory_order_acquire) - readIndex.load(std::memory_order_acquire)) >= containerLen;
    }

    bool isBufferEmpty() const
    {
        return writeIndex.load(std::memory_order_acquire) == readIndex.load(std::memory_order_acquire);
    }
};
#endif // DATA_POOL_H
