#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QCustomPlot/qcustomplot.h"
#include <QTimer>
struct xyData{
    double x;
    double y;
};
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initCustomPlot();

public slots:
    void slotTimeout();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QCustomPlot * m_plot;

    QTimer *timer;

    xyData * m_data;

    QVector<QCPGraphData> *m_coreData;
};
#endif // MAINWINDOW_H
