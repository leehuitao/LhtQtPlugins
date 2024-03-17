#ifndef LHTOPENSSLENCODE_H
#define LHTOPENSSLENCODE_H

#include <QObject>

class LhtOpenSSLEncode : public QObject
{
    Q_OBJECT
public:
    explicit LhtOpenSSLEncode(QObject *parent = nullptr);
    void aesEncryptDecrypt(const unsigned char *input, int input_len, unsigned char *key, unsigned char *iv, unsigned char *output, bool encrypt);

    std::string md5(const std::string &data);
    std::string sha1(const std::string &data);
    std::string sha256(const std::string &data);
    std::string sha512(const std::string &data);
signals:

};

#endif // LHTOPENSSLENCODE_H
