#ifndef LHT_EXAMPLES_H
#define LHT_EXAMPLES_H

#include <QWidget>
#include <QTimer>
#include "LhtLog/QsLog/QsLog.h"
#include "LhtThread/event_driven_thread.h"
#include "LhtGui/Progress/progress_of_the_barrel.h"
#include "LhtGui/Progress/spinning_round.h"
using namespace QsLogging;
namespace Ui {
class LhtExamples;
}

class LhtExamples : public QWidget ,
        public EventDrivenPool<int, double, QString>
{
    Q_OBJECT

public:
    explicit LhtExamples(QWidget *parent = nullptr);
    ~LhtExamples();

    void initQsLog(QsLogging::Level level, const QString &logPath, long long maxSizeBytes, int maxOldLogCount);

    void initSql();

    void initCamera();

    void initBoostTcpServer();

    void initGrpc();

    void initProgress();

    void initTableView();
protected:
    void handleData(std::tuple<int, double, QString> &args) override;
    //private slots:
    //    void qsLogFunc(const QString& message, QsLogging::Level level);
private:
    Ui::LhtExamples *ui;

};

#endif // LHT_EXAMPLES_H
