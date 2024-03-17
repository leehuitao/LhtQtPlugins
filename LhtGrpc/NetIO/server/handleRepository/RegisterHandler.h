#pragma once
#include "ServiceProto.grpc.pb.h"
#include "ServiceProto.pb.h"
#include <grpcpp/grpcpp.h>
#include "msghandler_repository.h"
#include <mutex>
#include <functional>
#include <shared_mutex>
#include <QString>

typedef std::unique_lock<std::mutex> GrpcLock;

typedef ServiceNetIO::NewMessageRequest GrpcRequestBufferPtr;
typedef std::shared_ptr<grpc::ClientReaderWriter<ServiceNetIO::NewMessageRequest, ServiceNetIO::ServiceMessageResponse>> grpcStream;
typedef std::function<void(GrpcRequestBufferPtr,QString)> GrpcRequestHandler;

class GrpcRegisterHandler
{

public:
    static GrpcRegisterHandler Instance() {
        static std::mutex mutex;
        GrpcLock locker(mutex);
        static GrpcRegisterHandler instance_;
        return instance_;
    }
    bool InitHandler(unsigned short cmd,  GrpcRequestHandler handler){
        return GrpcMsgHandlerRepository<GrpcRequestHandler>::instance().registerHandler(cmd, handler);
    }
private:
    //    static GrpcRegisterHandler* instance_;
};

