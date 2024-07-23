#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./network/udp_thread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectFile_clicked();

    void on_send_clicked();

    void on_stopListen_clicked();

private:
    UdpThread * m_udpThread = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
