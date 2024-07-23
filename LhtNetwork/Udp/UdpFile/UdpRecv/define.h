#ifndef DEFINE_H
#define DEFINE_H
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QUdpSocket>
#include <QByteArray>
#include <QSharedPointer>
#include <QDataStream>

//第一个包
#define FILE_CMD_START          101
//数据包
#define FILE_CMD_DATA           102
//结束包
#define FILE_CMD_CANCEL         103
//断点续传
#define FILE_BREAKPOINT_RESUME  104

struct FileInfo
{
    FileInfo(){}
    FileInfo(QByteArray byteArray){
        QDataStream stream(&byteArray, QIODevice::ReadOnly);
        stream.setByteOrder(QDataStream::LittleEndian); // 设置字节序，根据需要设置
        stream >> this->cmd >> this->packSize >> this->fileSize
               >> this->currentPointSeek;
        stream.readRawData(this->fileName,64);
        char * temp = new char[this->packSize - 88];
        memcpy(temp,byteArray.data()+88,this->packSize - 88);
        this->data = QByteArray(temp,this->packSize - 88);
        delete []temp;
    }
    FileInfo(int cmd,int dataSize,qint64 fileSize,qint64 seek,QString fileName,QByteArray data = QByteArray()){
        this->cmd = cmd;
        this->packSize = dataSize+88;
        this->fileSize =fileSize;
        this->currentPointSeek = seek;
        memcpy(this->fileName,fileName.toLocal8Bit().data(),fileName.size());
        this->data = data;
        data.resize(dataSize);
    }
    qint32              cmd;//指令
    qint32              packSize;//当前包大小
    qint64              fileSize;//文件总大小
    qint64              currentPointSeek;//当前文件指针偏移
    char                fileName[64];
    QByteArray          data;
    QByteArray toByteArray(){
        QByteArray buffer;
        QDataStream stream(&buffer, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::LittleEndian); // 设置字节序，根据需要设置
        int size;
        stream << this->cmd << this->packSize << this->fileSize << this->currentPointSeek;
        stream.writeRawData(this->fileName, 64);
        if(this->packSize > 88){
            stream .writeRawData(this->data.data(), this->packSize - 88);
        }
        buffer.resize(this->packSize);
        return buffer;
    }
};

#endif // DEFINE_H
