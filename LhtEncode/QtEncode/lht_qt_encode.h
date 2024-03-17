#ifndef LHTQTENCODE_H
#define LHTQTENCODE_H

#include <QObject>
#include <QCryptographicHash>

class LhtQtEncode : public QObject
{
    Q_OBJECT
public:
    explicit LhtQtEncode(QObject *parent = nullptr);
    //支持MD5  SHA 等  QT 版本
    QString lhtQtEncode(const QString &data, QCryptographicHash::Algorithm algorithm = QCryptographicHash::Md5 );
signals:

};

#endif // LHTQTENCODE_H
