#include "qfile_examples.h"
#include <QDebug>
#include <QDir>

QFileExamples::QFileExamples()
{

}

bool QFileExamples::copyFile(const QString &sourceFilePath, const QString &destinationFilePath)
{
    if (QFile::copy(sourceFilePath, destinationFilePath)) {
        qDebug() << "File copied successfully.";
        return 1;
    } else {
        qDebug() << "Failed to copy file.";
        return false;
    }
}

bool QFileExamples::copyFile1(const QString &sourceFilePath, const QString &destinationFilePath)
{
    QFile sourceFile(sourceFilePath);
    if (!sourceFile.exists()) {
        qDebug() << "Source file does not exist.";
        return false;
    }

    QDir destinationDir(QFileInfo(destinationFilePath).absoluteDir());
    if (!destinationDir.exists()) {
        // 创建目标文件夹
        if (!destinationDir.mkpath(destinationDir.absolutePath())) {
            qDebug() << "Failed to create destination directory.";
            return false;
        }
    }

    if (!sourceFile.copy(destinationFilePath)) {
        qDebug() << "Failed to copy file.";
        return false;
    }

    qDebug() << "File copied successfully.";
    return true;
}

bool QFileExamples::readFileStartWithSeek(const QString &fileName, int seek, int len, QByteArray &data)
{
    if(m_readFile == nullptr){
        m_readFileName = fileName;
        m_readFile = new QFile(fileName);
    }

    if(m_readFileName != fileName){
        m_readFileName = fileName;
        m_readFile->close();
        m_readFile->setFileName(fileName);
    }
    if(!m_readFile->isOpen()){
        if (!m_readFile->open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open file for reading:" << m_readFile->errorString();
            return false;
        }
    }

    if (!m_readFile->seek(seek)) {
        qDebug() << "Failed to seek in file:" << m_readFile->errorString();
        m_readFile->close();
        return false;
    }

    data = m_readFile->read(len);
    if (data.size() == 0) {
        qDebug() << "Failed to read expected number of bytes.";
        m_readFile->close();
        return false;
    }
    return true;
}

bool QFileExamples::writeTextToFile(const QString &fileName, const QString &text)
{

    if (m_writeTextFile == nullptr) {
        m_writeTextFileName = fileName;
        m_writeTextFile = new QFile(fileName);
    }
    if(m_writeTextFileName != fileName){
        m_writeTextFileName = fileName;
        m_writeTextFile->close();
        m_writeTextFile->setFileName(fileName);
    }
    if(!m_writeTextFile->isOpen()){
        if (!m_writeTextFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to open text file for writing:" << m_writeTextFile->errorString();
            return false;
        }
    }
    QTextStream out(m_writeTextFile);
    out << text;

    return true;

}

bool QFileExamples::writeDataToFile(const QString &fileName, const QByteArray &data)
{

    if (m_writeDataFile == nullptr) {
        m_writeDataFileName = fileName;
        m_writeDataFile = new QFile(fileName);
    }
    if(m_writeDataFileName != fileName){
        m_writeDataFileName = fileName;
        m_writeDataFile->close();
        m_writeDataFile->setFileName(fileName);
    }
    if(!m_writeDataFile->isOpen()){
        if (!m_writeDataFile->open(QIODevice::WriteOnly)) {
            qDebug() << "Failed to open data file for writing:" << m_writeDataFile->errorString();
            return false;
        }
    }
    qint64 bytesWritten = m_writeDataFile->write(data);
    if (bytesWritten != data.size()) {
        qDebug() << "Failed to write all data to file.";
        m_writeDataFile->close();
        return false;
    }
    return true;

}
