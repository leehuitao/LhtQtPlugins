#ifndef LHTFILEMAPWRITE_H
#define LHTFILEMAPWRITE_H

#include <QObject>
#include <QFile>
#include <QFileDevice>
#include <QDebug>
#include <memory>
/**
 * @class LhtFileMapWrite
 * @brief 利用内存映射技术进行高效文件写入的类。
 *
 * 该类提供了通过内存映射进行高效文件写入的方法。它支持动态扩展文件大小，
 * 并能在写入一定数量的数据后自动刷新到磁盘。
 *
 * @note 确保输入的dataSize大小可以被初始化时设置的映射大小整除。
 *
 * @version 1.0
 * @date 2024-07-15
 *
 * @author leehuitao
 */
class LhtFileMapWrite : public QObject,public std::enable_shared_from_this<LhtFileMapWrite>
{
    Q_OBJECT
public:
    /**
     * @brief LhtFileMapWrite 构造函数，初始化类对象。
     * @param parent 父对象，默认为 nullptr。
     */
    explicit LhtFileMapWrite(QObject *parent = nullptr);

    ~LhtFileMapWrite();

    static std::shared_ptr<LhtFileMapWrite> create(QObject *parent = nullptr) {
        return std::shared_ptr<LhtFileMapWrite>(new LhtFileMapWrite(parent));
    }

    /**
     * @brief 打开文件并进行初始的文件映射。
     * @param fileName 文件名。
     * @param initFileSize 初始化时的文件映射大小。
     * @return 成功返回 true，否则返回 false。
     */
    bool openFile(const QString &fileName, qint64 initFileSize);

    /**
     * @brief 将数据写入文件。确保输入的 dataSize 大小可以被初始化时设置的映射大小整除！
     * @param data 要写入的数据。
     * @param dataSize 数据大小。
     * @return 成功返回 true，否则返回 false。
     */
        bool writeData(const char *data, int dataSize);

    /**
     * @brief 更新文件的大小并重新映射文件。
     * @param newSize 新的文件大小。
     * @return 成功返回 true，否则返回 false。
     */
    bool extendFileSize(qint64 newSize);

    /**
     * @brief 关闭文件，并释放资源。
     */
    void closeFile();

signals:

private:
    QFile file;            ///< 文件对象
    uchar *mappedData;     ///< 内存映射的数据指针
    qint64 currentIndex;   ///< 当前写入的位置索引
    qint64 currentTotalSize; ///< 当前文件总大小
    char* buffer;          ///< 临时缓冲区
    int writeCount;        ///< 写入计数
    int bufferSize;        ///< 缓冲区大小，比如1000次16384字节的写入
};

#endif // LHTFILEMAPWRITE_H
