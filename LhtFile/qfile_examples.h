#ifndef QFILEEXAMPLES_H
#define QFILEEXAMPLES_H

/**
 * @date 2024-02-29
 * @brief 一些比较常用的QFile的使用示例
 * @author leehuitao
 */

#include <QObject>
#include <QFile>
#include <QTextStream>

class QFileExamples
{
public:
    QFileExamples();

    bool copyFile(const QString &sourceFilePath, const QString &destinationFilePath);
    //假设目标文件夹不存在则创建
    bool copyFile1(const QString &sourceFilePath, const QString &destinationFilePath);
    //读取一段长度的数据从seek开始
    bool readFileStartWithSeek(const QString &fileName,int seek,int len,QByteArray & data);
    //写入一段text
    bool writeTextToFile(const QString &fileName, const QString &text);
    //写入一段数据
    bool writeDataToFile(const QString &fileName, const QByteArray &data);

private:
    QFile * m_readFile = nullptr;
    QFile * m_writeTextFile = nullptr;
    QFile * m_writeDataFile = nullptr;

    QString m_readFileName;
    QString m_writeTextFileName;
    QString m_writeDataFileName;
};

#endif // QFILEEXAMPLES_H
