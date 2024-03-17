
#ifndef HANDLETEST1_H
#define HANDLETEST1_H


#include "handleRepository/RegisterHandler.h"
#include <QDebug>
class GrpcTestMethod
{
public:
    virtual void HandleMessage(GrpcRequestBufferPtr msg, QString);

};

#endif // HANDLETEST1_H
