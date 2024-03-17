
#include "handle_interface.h"

HandleInterface::HandleInterface(QObject *parent)
{

}

void HandleInterface::handleData(std::pair<GrpcRequestBufferPtr , QString>data)
{
    GrpcRequestHandler handler = GrpcMsgHandlerRepository<GrpcRequestHandler>::instance().handler(data.first.order_id());

    if (handler== nullptr) {
        handler = GrpcMsgHandlerRepository<GrpcRequestHandler>::instance().handler(1);

    }
    else {
        handler(data.first,data.second);
    }
}
