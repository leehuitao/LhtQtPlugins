#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <QFile>
#include <QObject>
#include <QThread>
#include <QUdpSocket>
class UdpThread : public QThread
{
    Q_OBJECT
public:
    explicit UdpThread(QObject *parent = nullptr);

    void init(QString tartgetIp , int targetPort,QString selfIp , int selfPort){
        m_targetIp = tartgetIp;
        m_targetPort = targetPort;
        m_selfIp =      selfIp;
        m_selfPort =    selfPort;
    }

    void setFilePath(QString file){
        m_file = file;
    }

    void setStop(){
        m_stop = 1;
    }
    void setPrase(){
        m_prase = 1;
    }
    void setContinue(){
        m_prase = 0;
    }
protected:
    void run();
signals:
    void signNewProgress(float);
private:
    int         m_port = 80801;
    QString     m_selfIp;
    int         m_selfPort;
    QString     m_targetIp;
    int         m_targetPort;
    QString     m_file;
    bool        m_stop = 0;
    bool        m_prase = 0;
    QUdpSocket  *m_socket = nullptr;
    QFile       *m_fileFd = nullptr;
};

#endif // UDPTHREAD_H

//-------------------------tips--------------------------------
//pendingDatagramSize 获取当前数据包大小
//hasPendingDatagrams 用于检查是否有待处理的UDP数据报
//readDatagram 用于读取数据包  调用readDatagram函数可能会导致阻塞。因此，在调用readDatagram之前，建议先使用hasPendingDatagrams函数进行检查，以避免不必要的阻塞。
