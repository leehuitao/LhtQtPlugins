#include "HandleTest1.h"


void GrpcTestMethod::HandleMessage(GrpcRequestBufferPtr msg,QString stream)
{
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(stream.toStdString(), grpc::InsecureChannelCredentials());
    std::unique_ptr<ServiceNetIO::UserServiceInterface::Stub> stub = ServiceNetIO::UserServiceInterface::NewStub(channel);

    grpc::ClientContext context;

    auto sstream = stub->NewNotify(&context);
    qDebug()<<"body "<<msg.body().c_str()<<"header "<<msg.header().c_str()<<"server_name "<<msg.server_name().c_str();
    // 创建并发送响应
    ServiceNetIO::NewMessageRequest request;
    request.set_header("testttttttttttttt");
    request.set_server_name("Server 1");
    request.set_order_id(1);
    request.set_encode_type("UTF-8");
    request.set_body("Hello, server!");
    //测试回包  这里因为方法都是一样的  所以会引起递归  暂时注释 项目中需要使用时打开
//    sstream->Write(request);
//    sstream->WritesDone();
}

