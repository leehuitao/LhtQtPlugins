#include "lht_openssl_encode.h"
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
LhtOpenSSLEncode::LhtOpenSSLEncode(QObject *parent) : QObject(parent)
{

}

void LhtOpenSSLEncode::aesEncryptDecrypt(const unsigned char* input, int input_len, unsigned char* key, unsigned char* iv, unsigned char* output, bool encrypt) {

    // 创建并初始化加密上下文
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        std::cerr << "Cannot create cipher context" << std::endl;
        return;
    }

    if(encrypt) {
        // 初始化加密操作
        if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv)) {
            std::cerr << "EncryptInit error" << std::endl;
        }

        // 执行加密
        int len;
        if (1 != EVP_EncryptUpdate(ctx, output, &len, input, input_len)) {
            std::cerr << "EncryptUpdate error" << std::endl;
        }
        int ciphertext_len = len;

        // 结束加密操作
        if (1 != EVP_EncryptFinal_ex(ctx, output + len, &len)) {
            std::cerr << "EncryptFinal error" << std::endl;
        }
        ciphertext_len += len;

    } else {
        // 初始化解密操作
        if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv)) {
            std::cerr << "DecryptInit error" << std::endl;
        }

        // 执行解密
        int len;
        if (1 != EVP_DecryptUpdate(ctx, output, &len, input, input_len)) {
            std::cerr << "DecryptUpdate error" << std::endl;
        }
        int plaintext_len = len;

        // 结束解密操作
        if (1 != EVP_DecryptFinal_ex(ctx, output + len, &len)) {
            std::cerr << "DecryptFinal error" << std::endl;
        }
        plaintext_len += len;
    }

    // 清理加密上下文
    EVP_CIPHER_CTX_free(ctx);
}
// 将二进制哈希值转换为十六进制字符串
std::string toHex(const unsigned char* hash, std::size_t length) {
    std::stringstream ss;
    for (std::size_t i = 0; i < length; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

// MD5 哈希计算
std::string LhtOpenSSLEncode::md5(const std::string& data) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);
    return toHex(hash, MD5_DIGEST_LENGTH);
}

// SHA1 哈希计算
std::string LhtOpenSSLEncode::sha1(const std::string& data) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);
    return toHex(hash, SHA_DIGEST_LENGTH);
}

// SHA256 哈希计算
std::string LhtOpenSSLEncode::sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);
    return toHex(hash, SHA256_DIGEST_LENGTH);
}

// SHA512 哈希计算
std::string LhtOpenSSLEncode::sha512(const std::string& data) {
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);
    return toHex(hash, SHA512_DIGEST_LENGTH);
}
//调用示例
//int main() {
//    // 示例密钥和IV。实际使用时应生成安全的随机值
//    unsigned char key[AES_BLOCK_SIZE]; // AES_BLOCK_SIZE = 16
//    unsigned char iv[AES_BLOCK_SIZE];
//    RAND_bytes(key, sizeof(key));
//    RAND_bytes(iv, sizeof(iv));

//    const char* message = "This is a secret message";
//    unsigned char encrypted[128];
//    unsigned char decrypted[128];

//    // 加密
//    aes_encrypt_decrypt(reinterpret_cast<const unsigned char*>(message), strlen(message), key, iv, encrypted, true);
//    std::cout << "Encrypted message" << std::endl;

//    // 解密
//    aes_encrypt_decrypt(encrypted, sizeof(encrypted), key, iv, decrypted, false);
//    std::cout << "Decrypted message: " << decrypted << std::endl;

//    return 0;
//}
