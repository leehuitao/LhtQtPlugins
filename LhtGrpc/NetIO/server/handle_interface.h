
#ifndef HANDLEINTERFACE_H
#define HANDLEINTERFACE_H


#include <QObject>
#include "../QtWaitConditionThread/thread_pool_basic.h"

class HandleInterface : public ThreadPoolBasic
{
    Q_OBJECT
public:
    explicit HandleInterface(QObject *parent = nullptr);

signals:


    // ThreadPoolBasic interface
protected:
    void handleData(std::pair<GrpcRequestBufferPtr,QString>);
};

#endif // HANDLEINTERFACE_H
