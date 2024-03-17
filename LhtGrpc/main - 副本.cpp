
#include "mainwindow.h"

#include <QApplication>
#include "ServiceProto.grpc.pb.h"
#include "ServiceProto.pb.h"
#include <grpcpp/grpcpp.h>
#include <QDebug>
class UserServiceImpl final : public ServiceNetIO::UserServiceInterface::Service {
public:
    grpc::Status NewNotify(grpc::ServerContext* context,
                           grpc::ServerReaderWriter<ServiceNetIO::ServiceMessageResponse,
                                                    ServiceNetIO::NewMessageRequest>* stream) override {
        ServiceNetIO::NewMessageRequest request;
        while (stream->Read(&request)) {
            // 处理接收到的请求
            // ...
            qDebug()<<"body "<<request.body()<<"header "<<request.header()<<"server_name "<<request.server_name();
            // 创建并发送响应
            ServiceNetIO::ServiceMessageResponse response;
            response.set_send_status(200);
            response.set_send_user_id(123);
            response.set_send_user_name("John Doe");
            response.set_send_order_id(456);
            stream->Write(response);
        }
        return grpc::Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    UserServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

void RunClient() {
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    std::unique_ptr<ServiceNetIO::UserServiceInterface::Stub> stub = ServiceNetIO::UserServiceInterface::NewStub(channel);

    grpc::ClientContext context;
    std::shared_ptr<grpc::ClientReaderWriter<ServiceNetIO::NewMessageRequest, ServiceNetIO::ServiceMessageResponse>> stream(
        stub->NewNotify(&context));

    // 发送请求
    ServiceNetIO::NewMessageRequest request;
    request.set_header("testttttttttttttt");
    request.set_server_name("Server 1");
    request.set_order_id(12345);
    request.set_encode_type("UTF-8");
    request.set_body("Hello, server!");

    stream->Write(request);
    stream->WritesDone();

    // 接收响应
    ServiceNetIO::ServiceMessageResponse response;
    while (stream->Read(&response)) {
        // 处理接收到的响应
        // ...
    }

    grpc::Status status = stream->Finish();
    if (status.ok()) {
        qDebug() << "RPC succeeded." ;
    } else {
        qDebug() << "RPC failed with error code: " << status.error_code() ;
        qDebug() << "Error message: " << status.error_message() ;
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::thread server_thread(RunServer);

    RunClient();
    MainWindow w;
    w.show();
    return a.exec();
}
