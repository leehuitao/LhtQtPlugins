#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <QFile>
#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include "define.h"
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
    int         m_port=80802;
    QString     m_targetIp;
    int         m_targetPort;
    QString     m_selfIp;
    int         m_selfPort;
    QString     m_file;
    bool        m_stop = 0;
    bool        m_prase = 0;
    QUdpSocket  *m_socket = nullptr;
    QFile       *m_fileFd = nullptr;
    FileInfo    m_fileInfo;
};

#endif // UDPTHREAD_H
