
#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H


#include <QObject>


class ClientInterface : public QObject
{
    Q_OBJECT
public:
    explicit ClientInterface(QObject *parent = nullptr);

signals:

};

#endif // CLIENTINTERFACE_H
