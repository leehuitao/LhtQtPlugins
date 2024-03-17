#include "lht_qt_encode.h"

LhtQtEncode::LhtQtEncode(QObject *parent) : QObject(parent)
{

}

QString LhtQtEncode::lhtQtEncode(const QString &data, QCryptographicHash::Algorithm algorithm)
{
    // 将QString转换为QByteArray
    QByteArray byteArray = data.toUtf8();

    // 创建QCryptographicHash对象
    QCryptographicHash hash(algorithm);

    // 添加数据到散列对象
    hash.addData(byteArray);

    // 生成并获取散列值，以十六进制字符串格式返回
    return hash.result().toHex();
}
