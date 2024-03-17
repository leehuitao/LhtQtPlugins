
#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H


#include <QObject>
#include <QThread>
#include "ServiceProto.grpc.pb.h"
#include "ServiceProto.pb.h"
#include <grpcpp/grpcpp.h>
#include <QDebug>
#include "handleRepository/RegisterHandler.h"
#include <functional>
#include "HandleTest1.h"
#include "handle_interface.h"




class UserServiceImpl final : public ServiceNetIO::UserServiceInterface::Service {

public:

    void init(QString stream){
        m_stream = stream;
        m_handleInterface.startRun();
    }
    grpc::Status NewNotify(grpc::ServerContext* context,
                           grpc::ServerReaderWriter<ServiceNetIO::ServiceMessageResponse,
                                                    ServiceNetIO::NewMessageRequest>* stream) override {
        ServiceNetIO::NewMessageRequest request;
        while (stream->Read(&request)) {
            m_handleInterface.recvData(request,m_stream);
        }
        return grpc::Status::OK;
    }

private:
    QString m_stream;
    HandleInterface m_handleInterface;
};

class ServerInterface : public QThread
{
    Q_OBJECT
public:
    explicit ServerInterface(QObject *parent = nullptr);

    void initParameter(QString addr,QString targetServer);

    void initRepository();

    void setStart();

    void setStop();

    void test();

    void connectTo();
signals:


    // QThread interface
protected:
    void run();

private:
    bool m_pause;
    bool m_stop;
    QString m_targetServer;
    QString m_addr;
    std::unique_ptr<grpc::Server> m_server;
    QString m_stream;
    UserServiceImpl service;
};

#endif // SERVERINTERFACE_H
