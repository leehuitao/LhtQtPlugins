
#ifndef NETGRPCINTERFACE_H
#define NETGRPCINTERFACE_H


#include <QObject>

class NetGrpcInterface : public QObject
{
    Q_OBJECT
public:
    explicit NetGrpcInterface(QObject *parent = nullptr);

signals:

};

#endif // NETGRPCINTERFACE_H
