
#include "server_interface.h"

class GrpcHandlerManager
{
public:
    static GrpcHandlerManager& Instance(){
        static GrpcHandlerManager g_instance;
        return g_instance;
    }


    template<class Handler>
    const bool InitHandler(const unsigned short cmd){
        GrpcRegisterHandler::Instance().InitHandler(cmd, std::bind(&GrpcHandlerManager::NotifyHandler<Handler>, this, std::placeholders::_1,std::placeholders::_2));
        return 1;
    }
private:

    template<class Handler>
    void NotifyHandler(GrpcRequestBufferPtr msg,QString stream){
        Handler handler;
        handler.HandleMessage(msg,stream);
    }

};




ServerInterface::ServerInterface(QObject *parent)
    : QThread{parent}
{

}

void ServerInterface::initParameter(QString addr, QString targetServer)
{
    m_addr = addr;
    m_targetServer = targetServer;
}

void ServerInterface::initRepository()
{
    GrpcHandlerManager::Instance().InitHandler<GrpcTestMethod>(1);
}

void ServerInterface::setStart()
{
    start();
}

void ServerInterface::setStop()
{
    m_server.release();
    quit();
    wait(100);
}

void ServerInterface::test()
{
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(m_targetServer.toStdString(), grpc::InsecureChannelCredentials());
    std::unique_ptr<ServiceNetIO::UserServiceInterface::Stub> stub = ServiceNetIO::UserServiceInterface::NewStub(channel);

    grpc::ClientContext context;

    auto stream = stub->NewNotify(&context);
        // 发送请求
    ServiceNetIO::NewMessageRequest request;
    request.set_header("testttttttttttttt");
    request.set_server_name("Server 1");
    request.set_order_id(1);
    request.set_encode_type("UTF-8");
    request.set_body("Hello, server!");

    stream->Write(request);
    //stream->WritesDone();

}

void ServerInterface::connectTo()
{
    service.init(m_targetServer);
}

void ServerInterface::run()
{
    m_pause = false;
    m_stop = false;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(m_addr.toStdString(), grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    m_server = builder.BuildAndStart();
    qDebug()<< "Server listening on " << m_addr;

    m_server->Wait();


}


