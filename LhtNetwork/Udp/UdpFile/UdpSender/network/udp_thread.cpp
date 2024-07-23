#include "udp_thread.h"
#include <QDebug>
#define FILE_PACKET_SIZE 88
#define FILE_BLOCK_SIZE 8192

UdpThread::UdpThread(QObject *parent)
{

}

void UdpThread::run()
{
    m_prase = 0;
    m_stop = 0;
    qint64 currentSeek = 0;
    bool isSendEnd = false;
    if(m_socket != nullptr){
        m_socket->close();
        delete m_socket;
    }
    m_socket = new QUdpSocket();
    m_socket->bind(QHostAddress(m_selfIp),m_selfPort);

    if(m_fileFd != nullptr){
        m_fileFd->close();
        delete m_fileFd;
    }
    m_fileFd = new QFile(m_file);

    if(!m_fileFd->open(QIODevice::ReadOnly)){
        qDebug()<<"open file faild file path ="<<m_file;
        return;
    }
    QByteArray receivedData; // 保存已接收的数据段
    QByteArray readFileData;
    while (1) {
        if(!m_prase){
            //----------------------开始传输包头--------------------------
            FileInfo fileInfo(FILE_CMD_START,0,m_fileFd->size(),0,m_file.split("/").last());
            m_socket->writeDatagram(fileInfo.toByteArray(),QHostAddress(m_targetIp),m_targetPort);
            if(!m_socket->waitForReadyRead(300000)){
                qDebug()<<"socket error ";
                return;
            }else{
                while (m_socket->hasPendingDatagrams()) {
                    QByteArray datagram;
                    datagram.resize(m_socket->pendingDatagramSize());
                    m_socket->readDatagram(datagram.data(), datagram.size());
                    receivedData.append(datagram);
                }
                FileInfo fileInfo(receivedData);
                receivedData.clear();
                if(fileInfo.cmd != FILE_CMD_START){
                    return;
                }else{
                    m_fileFd->seek(0);
                    readFileData.resize(FILE_BLOCK_SIZE);
                    auto actualSize = m_fileFd->read(readFileData.data(),FILE_BLOCK_SIZE);

                    FileInfo fileInfoData(FILE_CMD_DATA,actualSize,m_fileFd->size(),0,m_file,readFileData);
                    m_fileInfo = fileInfoData;
                    m_socket->writeDatagram(fileInfoData.toByteArray(),QHostAddress(m_targetIp),m_targetPort);
                }
            }
            //----------------------包头对接结束--------------------------

            //----------------------开始传输数据--------------------------

            while(!isSendEnd){
                if(m_socket->hasPendingDatagrams()){
                    QByteArray datagram;
                    datagram.resize(m_socket->pendingDatagramSize());
                    // 读取数据包
                    m_socket->readDatagram(datagram.data(), datagram.size());
                    // 拼接数据段
                    receivedData.append(datagram);
                    // 处理完整的数据段
                    while (receivedData.size() >= FILE_PACKET_SIZE) {
                        FileInfo fileInfo;
                        QDataStream stream(&receivedData, QIODevice::ReadOnly);
                        stream.setByteOrder(QDataStream::LittleEndian);
                        stream >> fileInfo.cmd >> fileInfo.packSize;
                        if (receivedData.size() >= fileInfo.packSize) {
                            FileInfo info(receivedData);
                            receivedData = receivedData.mid(info.packSize);
                            if(info.cmd == FILE_CMD_CANCEL){
                                signNewProgress(1.0);
                                return;
                            }else if(info.cmd == FILE_CMD_DATA){
                                signNewProgress((float(info.currentPointSeek) / info.fileSize));
                                currentSeek = info.currentPointSeek;
                            }

                            m_fileFd->seek(info.currentPointSeek);
                            readFileData.resize(FILE_BLOCK_SIZE);
                            auto actualSize = m_fileFd->read(readFileData.data(),FILE_BLOCK_SIZE);

                            FileInfo fileInfoData(FILE_CMD_DATA,actualSize,m_fileFd->size(),currentSeek,m_file,readFileData);
                            m_fileInfo = fileInfoData;
                            m_socket->writeDatagram(fileInfoData.toByteArray(),QHostAddress(m_targetIp),m_targetPort);
                        }
                    }
                }



//                if(!m_socket->waitForReadyRead(100)){//100ms没接收到数据就重发一次
//                    m_socket->writeDatagram(m_fileInfo.toByteArray(), QHostAddress(m_targetIp), m_targetPort);
//                    qDebug()<<"socket error ";
//                    return;
//                }else{
//                    while (m_socket->hasPendingDatagrams()) {
//                        QByteArray datagram;
//                        datagram.resize(m_socket->pendingDatagramSize());
//                        m_socket->readDatagram(datagram.data(), datagram.size());
//                        receivedData.append(datagram);
//                    }
//                    FileInfo fileInfo(receivedData);
//                    receivedData.clear();

//                }
            }
            //----------------------传输数据结束--------------------------

        }else{
            msleep(1000);
        }

        if(m_stop)
            break;
    }
}
