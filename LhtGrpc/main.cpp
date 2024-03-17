
//#include "mainwindow.h"

//#include <QApplication>

//#include <QDebug>

//void RunClient() {
//    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
//    std::unique_ptr<ServiceNetIO::UserServiceInterface::Stub> stub = ServiceNetIO::UserServiceInterface::NewStub(channel);

//    grpc::ClientContext context;
//    std::shared_ptr<grpc::ClientReaderWriter<ServiceNetIO::NewMessageRequest, ServiceNetIO::ServiceMessageResponse>> stream(
//        stub->NewNotify(&context));

//    // 发送请求
//    ServiceNetIO::NewMessageRequest request;
//    request.set_header("testttttttttttttt");
//    request.set_server_name("Server 1");
//    request.set_order_id(1);
//    request.set_encode_type("UTF-8");
//    request.set_body("Hello, server!");

//    stream->Write(request);
//    stream->WritesDone();

//    // 接收响应
//    ServiceNetIO::ServiceMessageResponse response;
//    while (stream->Read(&response)) {
//        // 处理接收到的响应
//        // ...
//    }

//     grpc::Status status = stream->Finish();
//    if (status.ok()) {
//        qDebug() << "RPC succeeded." ;
//    } else {
//        qDebug() << "RPC failed with error code: " << status.error_code() ;
//        qDebug() << "Error message: " << status.error_message().c_str() ;
//    }
//}
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    //RunClient();
//    MainWindow w;
//    w.show();
//    return a.exec();
//}
