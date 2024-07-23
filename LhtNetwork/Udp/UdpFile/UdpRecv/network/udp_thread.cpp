#include "udp_thread.h"
#include "define.h"

#define FILE_PACKET_SIZE 88
#define FILE_BLOCK_SIZE 1024

UdpThread::UdpThread(QObject *parent)
{

}

void UdpThread::run()
{
    m_prase = 0;
    m_stop = 0;
    if(m_socket != nullptr){
        m_socket->close();
        delete m_socket;
    }
    m_socket = new QUdpSocket();
    m_socket->bind(QHostAddress(m_selfIp),m_selfPort);
    if(m_stop)
        return;

    m_fileFd = new QFile;
    QByteArray receivedData; // 保存已接收的数据段
    QByteArray readFileData;
    if(!m_prase){
        //----------------------开始传输数据--------------------------
        while(1)
        {
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
                    // 检查是否接收完整的数据段
                    if(!m_prase){
                        if (receivedData.size() >= fileInfo.packSize) {
                            FileInfo info(receivedData);
                            if(info.cmd == FILE_CMD_DATA)
                            {
                                if(info.currentPointSeek + info.packSize - FILE_PACKET_SIZE < info.fileSize)
                                {
                                    m_fileFd->seek(info.currentPointSeek);
                                    auto recvSize = m_fileFd->write(info.data,info.packSize - FILE_PACKET_SIZE);
                                    //返回包
                                    if(m_fileFd->size()!= info.currentPointSeek + info.packSize - FILE_PACKET_SIZE){
                                        qDebug()<<"";
                                    }
                                    FileInfo fileInfo1(FILE_CMD_DATA,0,info.fileSize,info.currentPointSeek + info.packSize - FILE_PACKET_SIZE,info.fileName);
                                    m_socket->writeDatagram(fileInfo1.toByteArray(),QHostAddress(m_targetIp),m_targetPort);
                                    signNewProgress(float((info.currentPointSeek + info.packSize - FILE_PACKET_SIZE))/info.fileSize);
                                }
                                else//结束
                                {
                                    m_fileFd->seek(info.currentPointSeek);
                                    auto recvSize = m_fileFd->write(info.data,info.packSize - FILE_PACKET_SIZE);
                                    m_fileFd->close();
                                    signNewProgress(1);
                                    //返回包
                                    FileInfo fileInfo1(FILE_CMD_CANCEL,0,info.fileSize,info.currentPointSeek + info.packSize - FILE_PACKET_SIZE,info.fileName);
                                    m_socket->writeDatagram(fileInfo1.toByteArray(),QHostAddress(m_targetIp),m_targetPort);
                                }
                            }
                            else if(info.cmd == FILE_CMD_START)
                            {
                                //打开文件
                                QString fileName = info.fileName;
                                m_fileFd->setFileName(m_file + "/" + fileName);

                                if(!m_fileFd->open(QIODevice::WriteOnly/*|QIODevice::Append*/))
                                {
                                    qDebug()<<"open file faild file path = "<<fileName;
                                    return;
                                }
                                //返回包
                                FileInfo fileInfo1(FILE_CMD_START,0,0,0,"");
                                m_socket->writeDatagram(fileInfo1.toByteArray(),QHostAddress(m_targetIp),m_targetPort);
                            }
                            // 移除已处理的数据段
                            receivedData.remove(0, info.packSize);
                        } else {
                            // 数据段不完整，等待下一个数据包到达
                            break;
                        }
                    }else{
                        msleep(1000);
                    }
                          if(m_stop)
                        break;
                }
                  }
        }
        //----------------------传输数据结束--------------------------
    }else{
        msleep(1000);
    }
}

