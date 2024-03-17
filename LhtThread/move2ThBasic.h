#ifndef MOVE2THBASIC_H
#define MOVE2THBASIC_H
#include <QThread>
#include <QObject>

class Move2ThBasic : public QObject
{
    Q_OBJECT
public:
    Move2ThBasic()
    {
        m_workerThread = new QThread;
    }

    virtual ~Move2ThBasic()
    {
        if (m_workerThread != nullptr)
        {
            delete m_workerThread;
        }
    }

    virtual QString name() = 0;
    QString lastError() {return m_lastError;}

protected:
    QString m_lastError;
    QThread *m_workerThread = nullptr;

public Q_SLOTS:
    virtual bool Init()
    {
        if (m_workerThread != nullptr)
        {
            this->moveToThread(m_workerThread);
            m_workerThread->start();
        }

        return true;
    }

    virtual bool UnInit()
    {

        if (m_workerThread != nullptr && m_workerThread->isRunning())
        {
            m_workerThread->quit();
            m_workerThread->wait();
        }

        if (m_workerThread != nullptr)
        {
            delete m_workerThread;
            m_workerThread = nullptr;
        }

        return true;
    }


};


#endif // MOVE2THBASIC_H
