#include "file_map_write.h"

LhtFileMapWrite::LhtFileMapWrite(QObject *parent)
    : QObject{parent}, mappedData(nullptr), currentIndex(0),currentTotalSize(0),buffer(nullptr)
{

}

LhtFileMapWrite::~LhtFileMapWrite()
{
    file.close();
    if(buffer != nullptr){
        delete []buffer;
    }
}

bool LhtFileMapWrite::openFile(const QString &fileName, qint64 initFileSize)
{
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning() << "Failed to open file";
        return false;
    }

    // 预分配文件大小
    if (!file.resize(initFileSize)) {
        qWarning() << "Failed to resize file";
        return false;
    }
    buffer = new char[initFileSize];
    bufferSize = initFileSize;
    mappedData = file.map(0, bufferSize);
    if (!mappedData) {
        qWarning() << "Failed to map file";
        return false;
    }

    return true;
}

bool LhtFileMapWrite::extendFileSize(qint64 newSize)
{
    if (!file.resize(newSize)) {
        qWarning() << "Failed to resize file";
        return false;
    }

    // 解除旧的映射
    if (!file.unmap(mappedData)) {
        qWarning() << "Failed to unmap file";
        return false;
    }
    currentIndex = 0;
    mappedData = file.map(currentTotalSize, bufferSize);
    if (!mappedData) {
        qWarning() << "Failed to map file";
        return false;
    }

    return true;
}

bool LhtFileMapWrite::writeData(const char *data, int dataSize)
{
    std::memcpy(buffer + currentIndex, data, dataSize);
    currentIndex += dataSize;
    currentTotalSize += dataSize;
    if (currentIndex >= bufferSize) {
        memcpy(mappedData, buffer, bufferSize);
        extendFileSize(currentTotalSize + bufferSize);
    }

    return true;
}

void LhtFileMapWrite::closeFile()
{
    if (mappedData) {
        file.unmap(mappedData);
        mappedData = nullptr;
    }
    file.resize(currentIndex);
    file.close();
}
